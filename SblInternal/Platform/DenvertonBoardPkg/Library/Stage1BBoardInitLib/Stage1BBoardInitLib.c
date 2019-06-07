/** @file

@copyright
  Copyright (c) 2008 - 2017 Intel Corporation. All rights reserved.
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.
  This file contains an 'Intel Pre-EFI Module' and is licensed
  for Intel CPUs and Chipsets under the terms of your license
  agreement with Intel or your vendor. This file may be
  modified by the user, subject to additional terms of the
  license agreement.
**/

#include <PiPei.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PciLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/GpioLib.h>
#include <Library/BoardInitLib.h>
#include <Library/ConfigDataLib.h>
#include <Library/BootloaderCoreLib.h>
#include <FspmUpd.h>
#include <BlCommon.h>

#include "GpioTbl.h"

#define  FSP_M_CONFIG    FSPM_CONFIG


// Scrub regions
const BL_MEMORY_SCRUB_SEGMENTS scrub_segments = {
    .NumberOfSegments = 1,
    .Reserved = 0,
    .ScrubSegment = {
        {
            .Start = 0,
            .End   = 0x800,
        },
        {
            .Start = 0x800-0x80,
            .End   = 0x800,
        },
        {
            .Start = 0,
            .End = 0,
        },
        {
            .Start = 0,
            .End = 0,
        },
        {
            .Start = 0,
            .End = 0,
        },
    },
};

/**
  Update FSP-M UPD config data

  @param  FspmUpdPtr            The pointer to the FSP-M UPD to be updated.

  @retval None
**/
VOID
UpdateFspConfig (
  VOID     *FspmUpdPtr
)
{
  FSPM_UPD     *FspmUpd;

  FspmUpd = (FSPM_UPD *)FspmUpdPtr;

  FspmUpd->FspmConfig.PcdFspDebugPrintErrorLevel = 0x00;
  FspmUpd->FspmConfig.PcdFastBoot                = 1;

  FspmUpd->FspmConfig.PcdSkipMemoryTest          = 1;
  FspmUpd->FspmConfig.PcdScrubSegmentPtr         = (void*)&scrub_segments;

  FspmUpd->FspmConfig.PcdMemoryDown              = 0;
  FspmUpd->FspmConfig.PcdMemoryDownConfigPtr     = 0;
  FspmUpd->FspmConfig.PcdSpdSmbusAddress_0_0     = 0xA0;
  FspmUpd->FspmConfig.PcdSpdSmbusAddress_0_1     = 0xA2;
  FspmUpd->FspmConfig.PcdSpdSmbusAddress_1_0     = 0xA4;
  FspmUpd->FspmConfig.PcdSpdSmbusAddress_1_1     = 0xA6;

	FspmUpd->FspmConfig.PcdIOxAPIC0_199 = 1;

}

#define CPUID_VIR_PHY_ADDRESS_SIZE      0x80000008
#define CPUID_EXTENDED_FUNCTION         0x80000000

//
// EFI_MEMORY_CACHE_TYPE
//
typedef INT32 EFI_MEMORY_CACHE_TYPE;

#define EFI_CACHE_UNCACHEABLE                 0
#define EFI_CACHE_WRITECOMBINING              1
#define EFI_CACHE_WRITETHROUGH                4
#define EFI_CACHE_WRITEPROTECTED              5
#define EFI_CACHE_WRITEBACK                   6

/**
  Programming MTRR according to Memory address, length, and type.

  @param[in] MtrrNumber           the variable MTRR index number
  @param[in] MemoryAddress        the address of target memory
  @param[in] MemoryLength         the length of target memory
  @param[in] MemoryCacheType      the cache type of target memory
  @param[in] ValidMtrrAddressMask the MTRR address mask

**/
VOID
EfiProgramMtrr (
  IN  UINTN                     MtrrNumber,
  IN  EFI_PHYSICAL_ADDRESS      MemoryAddress,
  IN  UINT64                    MemoryLength,
  IN  EFI_MEMORY_CACHE_TYPE     MemoryCacheType,
  IN  UINT64                    ValidMtrrAddressMask
  )
{
  UINT64                        TempQword;
  //UINT64                        OldMtrr;

  if (MemoryLength == 0) {
    return;
  }

  //
  // MTRR Physical Base
  //
  TempQword = ((UINT64)MemoryAddress & ValidMtrrAddressMask) | MemoryCacheType;
  AsmWriteMsr64 (MtrrNumber, TempQword);

  //
  // MTRR Physical Mask
  //
  TempQword = ~((UINT64)MemoryLength - 1);
  TempQword = (TempQword & ValidMtrrAddressMask) | BIT11;
  AsmWriteMsr64 (MtrrNumber + 1, TempQword);
}


/**
  Board specific hook points.

  Implement board specific initialization during the boot flow.

  @param[in] InitPhase             Current phase in the boot flow.

**/
VOID
BoardInit (
  IN  BOARD_INIT_PHASE  InitPhase
)
{
  UINT64                MemoryLength;
  EFI_PHYSICAL_ADDRESS  MemoryAddress;
  UINT64                ValidMtrrAddressMask;
  UINT32                Cpuid_RegEax;

  switch (InitPhase) {
  case PreMemoryInit:
    break;
  case PostMemoryInit:
    break;
  case PreTempRamExit:
    break;
  case PostTempRamExit:

    MemoryLength = 0x1000000;
    MemoryAddress = 0xFF000000;

    AsmCpuid (CPUID_EXTENDED_FUNCTION, &Cpuid_RegEax, NULL, NULL, NULL);
    if (Cpuid_RegEax >= CPUID_VIR_PHY_ADDRESS_SIZE) {
      AsmCpuid (CPUID_VIR_PHY_ADDRESS_SIZE, &Cpuid_RegEax, NULL, NULL, NULL);
      ValidMtrrAddressMask = (LShiftU64((UINT64) 1, (Cpuid_RegEax & 0xFF)) - 1) & (~(UINT64)0x0FFF);
    } else {
      ValidMtrrAddressMask = (LShiftU64((UINT64) 1, 36) - 1) & (~(UINT64)0x0FFF);
    }
    EfiProgramMtrr(0x212,
                   MemoryAddress,
                   MemoryLength,
                   EFI_CACHE_WRITEPROTECTED,
                   ValidMtrrAddressMask
                   );
    break;
  default:
    break;
  }

}

/**
  Search for the saved MrcParam to initialize Memory for fastboot

  @retval Found MrcParam or NULL
**/
VOID *
EFIAPI
FindNvsData (
  VOID
)
{
  UINT32    MrcData;
  EFI_STATUS    Status;

  Status = GetComponentInfo (FLASH_MAP_SIG_MRCDATA, &MrcData, NULL);
  if (EFI_ERROR(Status)) {
    return NULL;
  }

  if (*(UINT32 *)MrcData == 0xFFFFFFFF) {
    return NULL;
  } else {
    return (VOID *)MrcData;
  }
}

EFI_STATUS
EFIAPI
LoadExternalConfigData (
  IN UINT32  Dst,
  IN UINT32  Src,
  IN UINT32  Len
  )
{
  return EFI_NOT_FOUND;
}

/**
  Get the pointer to the Built-In Config Data

  @retval UINT8*    Pointer to the Built-In Config Data
**/
UINT8 *
GetBuiltInConfigData(
  IN  VOID
)
{
  return NULL;
}
