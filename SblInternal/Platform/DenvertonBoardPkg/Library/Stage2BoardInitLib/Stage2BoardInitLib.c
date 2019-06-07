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
#include <Library/PcdLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/GpioLib.h>
#include <Library/SpiFlashLib.h>
#include <Library/SocInitLib.h>
#include <Library/BoardInitLib.h>
#include <Library/SerialPortLib.h>
#include <Library/HobLib.h>
#include <Library/BootloaderCoreLib.h>
#include <Guid/FrameBufferInfoGuid.h>
#include <Guid/SystemTableInfoGuid.h>
#include <Guid/SerialPortInfoGuid.h>
#include <FspsUpd.h>
#include <RegAccess.h>
#include <PlatformBase.h>
#include <GlobalNvsArea.h>
#include "GpioTbl.h"
SPI_INSTANCE mSpiInstance;

UINT8
GetSerialPortStrideSize (
  VOID
);

UINT32
GetSerialPortBase (
  VOID
  );

#define  FSP_S_CONFIG    FSPS_CONFIG

typedef enum {
    ME_FIA_MUX_LANE_DISCONNECTED,
    ME_FIA_MUX_LANE_PCIE,
    ME_FIA_MUX_LANE_SATA,
    ME_FIA_MUX_LANE_XHCI,
} ME_FIA_MUX_LANE_CONFIG;

#define FIA_LANE_CONFIG(Config, Lane) ( (UINT64) ( (UINT64)(Config) << ( (UINT64)(Lane) * (ME_FIA_MUX_LANE_MUX_SEL_WIDTH))))

#define FIA_LANE00   0
#define FIA_LANE01   1
#define FIA_LANE02   2
#define FIA_LANE03   3
#define FIA_LANE04   4
#define FIA_LANE05   5
#define FIA_LANE06   6
#define FIA_LANE07   7
#define FIA_LANE08   8
#define FIA_LANE09   9
#define FIA_LANE10  10
#define FIA_LANE11  11
#define FIA_LANE12  12
#define FIA_LANE13  13
#define FIA_LANE14  14
#define FIA_LANE15  15
#define FIA_LANE16  16
#define FIA_LANE17  17
#define FIA_LANE18  18
#define FIA_LANE19  19

#define ME_FIA_MUX_LANE_SATA0_BEGING FIA_LANE04
#define ME_FIA_MUX_LANE_SATA1_BEGING FIA_LANE12

#define ME_FIA_MUX_LANE_NUM_MAX    20
#define ME_FIA_MUX_LANE_MUX_SEL_WIDTH 2
#define ME_FIA_MUX_LANE_MUX_SEL_MASK    0x3
#define ME_FIA_MUX_LANE_XHCI_ONLY    0xFF00000000

#define	HCV_HSIO_CONFIG						\
	FIA_LANE_CONFIG(ME_FIA_MUX_LANE_PCIE, FIA_LANE00) |	\
	FIA_LANE_CONFIG(ME_FIA_MUX_LANE_PCIE, FIA_LANE01) |	\
	FIA_LANE_CONFIG(ME_FIA_MUX_LANE_PCIE, FIA_LANE02) |	\
	FIA_LANE_CONFIG(ME_FIA_MUX_LANE_PCIE, FIA_LANE03) |	\
	FIA_LANE_CONFIG(ME_FIA_MUX_LANE_PCIE, FIA_LANE04) |	\
	FIA_LANE_CONFIG(ME_FIA_MUX_LANE_PCIE, FIA_LANE05) |	\
	FIA_LANE_CONFIG(ME_FIA_MUX_LANE_PCIE, FIA_LANE06) |	\
	FIA_LANE_CONFIG(ME_FIA_MUX_LANE_PCIE, FIA_LANE07) |	\
	FIA_LANE_CONFIG(ME_FIA_MUX_LANE_PCIE, FIA_LANE08) |	\
	FIA_LANE_CONFIG(ME_FIA_MUX_LANE_PCIE, FIA_LANE09) |	\
	FIA_LANE_CONFIG(ME_FIA_MUX_LANE_PCIE, FIA_LANE10) |	\
	FIA_LANE_CONFIG(ME_FIA_MUX_LANE_PCIE, FIA_LANE11) |	\
	FIA_LANE_CONFIG(ME_FIA_MUX_LANE_PCIE, FIA_LANE12) |	\
	FIA_LANE_CONFIG(ME_FIA_MUX_LANE_PCIE, FIA_LANE13) |	\
	FIA_LANE_CONFIG(ME_FIA_MUX_LANE_PCIE, FIA_LANE14) |	\
	FIA_LANE_CONFIG(ME_FIA_MUX_LANE_PCIE, FIA_LANE15) |	\
	FIA_LANE_CONFIG(ME_FIA_MUX_LANE_SATA, FIA_LANE16) |	\
	FIA_LANE_CONFIG(ME_FIA_MUX_LANE_SATA, FIA_LANE17) |	\
	FIA_LANE_CONFIG(ME_FIA_MUX_LANE_SATA, FIA_LANE18) |	\
	FIA_LANE_CONFIG(ME_FIA_MUX_LANE_XHCI, FIA_LANE19)


VOID
eMMCDefaultDLLSet (
  VOID
  )
{
  UINTN             eMMCPciCfgBase;
  UINTN             eMMCPciMemBar;

  eMMCPciCfgBase  = MmPciBase(
                              PCI_BUS_NUMBER_PCH_SCC_EMMC,
                              PCI_DEVICE_NUMBER_PCH_SCC_EMMC,
                              PCI_FUNCTION_NUMBER_PCH_SCC_EMMC
                             );
  if (MmioRead16 (eMMCPciCfgBase) == 0xFFFF) {
    ASSERT (FALSE);
  }
  eMMCPciMemBar   = MmioRead32 (eMMCPciCfgBase + R_PCH_SCC_SDIO_BAR)& B_PCH_SCC_SDIO_BAR_BA;

  // Enable PCI COMMOND BME & MSE
  MmioOr16 (eMMCPciCfgBase + R_PCH_SCC_SDIO_STSCMD, (UINT16)(B_PCH_SCC_SDIO_STSCMD_BME | B_PCH_SCC_SDIO_STSCMD_MSE));
  // Set Tx CMD Delay Control Register value
  MmioWrite32 (eMMCPciMemBar + R_SCC_MEM_TX_CMD_DLL_CNTL,       0x00000508);
  // Set Tx Data Delay Control 1 Register value
  MmioWrite32 (eMMCPciMemBar + R_SCC_MEM_TX_DATA_DLL_CNTL1,     0x00000c11);
  // Set Tx Data Delay Control 2 Register value
  MmioWrite32 (eMMCPciMemBar + R_SCC_MEM_TX_DATA_DLL_CNTL2,     0x1c2a2a2a);
  // Set Rx CMD + Data Delay Control 1 Register value
  MmioWrite32 (eMMCPciMemBar + R_SCC_MEM_RX_CMD_DATA_DLL_CNTL1, 0x00191e27);
  // Set Rx Strobe Delay Control Register value
  MmioWrite32 (eMMCPciMemBar + R_SCC_MEM_RX_STROBE_DLL_CNTL,    0x0A0A);
  // Set Rx CMD + Data Delay Control 2 Register value
  MmioWrite32 (eMMCPciMemBar + R_SCC_MEM_RX_CMD_DATA_DLL_CNTL2, 0x00010013);
  // Set Master DLL software Ctrl Register value
  MmioWrite32 (eMMCPciMemBar + R_SCC_MEM_MASTER_DLL_SW_CNTL,    0x1);
  // Dump eMMC DLL registers
  DEBUG ((DEBUG_VERBOSE, "Dump eMMC DLL registers:\n"));
  DEBUG ((DEBUG_VERBOSE, " R_SCC_MEM_TX_CMD_DLL_CNTL, = 0x%08x\n",     *(UINT32 *)(eMMCPciMemBar+R_SCC_MEM_TX_CMD_DLL_CNTL)));
  DEBUG ((DEBUG_VERBOSE, " R_SCC_MEM_TX_DATA_DLL_CNTL1 = 0x%08x\n",    *(UINT32 *)(eMMCPciMemBar+R_SCC_MEM_TX_DATA_DLL_CNTL1)));
  DEBUG ((DEBUG_VERBOSE, " R_SCC_MEM_TX_DATA_DLL_CNTL2 = 0x%08x\n",    *(UINT32 *)(eMMCPciMemBar+R_SCC_MEM_TX_DATA_DLL_CNTL2)));
  DEBUG ((DEBUG_VERBOSE, " R_SCC_MEM_RX_CMD_DATA_DLL_CNTL1 = 0x%08x\n",*(UINT32 *)(eMMCPciMemBar+R_SCC_MEM_RX_CMD_DATA_DLL_CNTL1)));
  DEBUG ((DEBUG_VERBOSE, " R_SCC_MEM_RX_STROBE_DLL_CNTL = 0x%08x\n",   *(UINT32 *)(eMMCPciMemBar+R_SCC_MEM_RX_STROBE_DLL_CNTL)));
  DEBUG ((DEBUG_VERBOSE, " R_SCC_MEM_RX_CMD_DATA_DLL_CNTL2 = 0x%08x\n",*(UINT32 *)(eMMCPciMemBar+R_SCC_MEM_RX_CMD_DATA_DLL_CNTL2)));
  DEBUG ((DEBUG_VERBOSE, " R_SCC_MEM_MASTER_DLL_SW_CNTL = 0x%08x\n",   *(UINT32 *)(eMMCPciMemBar+R_SCC_MEM_MASTER_DLL_SW_CNTL)));
  // Disable memory space decoding in command register
  MmioAnd16 (eMMCPciCfgBase + R_PCH_SCC_SDIO_STSCMD, (UINT16) ~(B_PCH_SCC_SDIO_STSCMD_BME | B_PCH_SCC_SDIO_STSCMD_MSE));
}


VOID
EFIAPI
RemoveMemorymapAbove4Gb (
  VOID
  )
{
  RETURN_STATUS        Status;
  MEMORY_MAP_INFO     *MemoryMapInfo;
  UINT8                Index;
  UINT8                MaxSizeIndex;
  UINTN                Length;
  LOADER_GLOBAL_DATA  *LdrGlobal;

  Status        = RETURN_NOT_FOUND;
  Index         = 0;
  MemoryMapInfo = NULL;
  MaxSizeIndex  = 0;

  //
  // Get memory map information
  //
  LdrGlobal = GetLoaderGlobalDataPointer();
  MemoryMapInfo = (MEMORY_MAP_INFO *)GetGuidHobData (LdrGlobal->LdrHobList, &Length, &gLoaderMemoryMapInfoGuid);
  if (MemoryMapInfo == NULL) {
    return;
  }

  for (Index = 0; Index < MemoryMapInfo->Count; Index++) {
    if ((MemoryMapInfo->Entry[Index].Type == MEM_MAP_TYPE_RAM) \
        && (MemoryMapInfo->Entry[Index].Base >= 0x100000000UL)) {
      MemoryMapInfo->Entry[Index].Size = 0;
    }
  }

  return;
}

VOID
BoardInit (
  IN  BOARD_INIT_PHASE    InitPhase
)
{
  switch (InitPhase) {
  case PreSiliconInit:
    GpioPadConfigTable (sizeof (mGpioTableHarcuvar) / sizeof (GPIO_INIT_CONFIG), mGpioTableHarcuvar);
    break;
  case PostPciEnumeration:
    eMMCDefaultDLLSet();
    break;
  case EndOfStages:
    RemoveMemorymapAbove4Gb ();
  default:
    break;
  }
}

/**
  Update FSP-S UPD config data

  @param  FspsUpdPtr            The pointer to the FSP-S UPD to be updated.

  @retval None
**/
VOID
UpdateFspConfig (
  VOID     *FspsUpdPtr
)
{
  FSPS_UPD      *FspsUpd;
  FSP_S_CONFIG  *FspsConfig;

  FspsUpd    = (FSPS_UPD *)FspsUpdPtr;
  FspsConfig = &FspsUpd->FspsConfig;

  //FspsConfig->PcdFiaMuxConfigRequest   = HCV_HSIO_CONFIG;
	FspsConfig->PcdCpuMicrocodePatchBase = (UINT32)0;
	FspsConfig->PcdCpuMicrocodePatchSize = (UINT32)0;
}

/**
  Save MRC data onto the Flash region from NVS buffer.

  @param Buffer pointer to an NVS data
  @param Length Length of the NVS data(MRC)

  @retval EFI_SUCCESS
  @retval RETURN_ALREADY_STARTED
  @retval EFI_DEVICE_ERROR
  @retval EFI_INVALID_PARAMETER
 */
EFI_STATUS
EFIAPI
SaveNvsData (
  IN  VOID    *Buffer,
  IN  UINT32   Length
)
{
  EFI_STATUS  Status;
  UINT32      Address;
  UINT32      BaseAddress;
  UINT32      RegionSize;
  UINT32      FlashBase;

  Status = GetComponentInfo (FLASH_MAP_SIG_MRCDATA, &Address, NULL);
  if (EFI_ERROR(Status)) {
    return EFI_NOT_FOUND;
  }
  if (*(UINT32 *)Address == 0xFFFFFFFF) {
    Status  = SpiProtocolConstructor (&mSpiInstance);
    SpiProtocolGetRegionAddress (&mSpiInstance.SpiProtocol, FlashRegionBios,
                                 &BaseAddress,  &RegionSize);

    FlashBase = 0xFFFFFFFF - mSpiInstance.TotalFlashSize + 1;
    Address = Address - BaseAddress - FlashBase;

    if (!EFI_ERROR(Status)) {
      Status = SpiProtocolFlashErase (&mSpiInstance.SpiProtocol, FlashRegionBios, Address, (Length + KB_(4) - 1) & ~(KB_(4) - 1));
      if (!EFI_ERROR(Status)) {
        Status = SpiProtocolFlashWrite (&mSpiInstance.SpiProtocol, FlashRegionBios, Address, Length, Buffer);
      }
    }
  } else {
    Status = RETURN_ALREADY_STARTED;
  }

  return Status;
}

/**
 Update serial port information to global HOB data structure.

 @param SerialPortInfo  Pointer to global HOB data structure.
 **/
VOID
EFIAPI
UpdateSerialPortInfo (
  IN  SERIAL_PORT_INFO  *SerialPortInfo
)
{
  SerialPortInfo->Type     = 1;
  SerialPortInfo->BaseAddr = GetSerialPortBase();
  SerialPortInfo->RegWidth = GetSerialPortStrideSize();
}


/**
 Update the OS boot option

 @param OsBootOptionList pointer to boot option list.
 **/
VOID
EFIAPI
UpdateOsBootMediumInfo (
  OUT  OS_BOOT_OPTION_LIST  *OsBootOptionList
)
{
  OS_BOOT_OPTION    *BootOption;

  //The OS image information could come from config data later.

  BootOption = &OsBootOptionList->OsBootOption[0];


  // Boot ELK from SPI
  BootOption->DevType   = OsBootDeviceMemory;
  BootOption->BootFlags = 0;
  BootOption->FsType    = EnumFileSystemMax;
  BootOption->Image[0].LbaImage.SwPart  = 0;
  BootOption->Image[0].LbaImage.LbaAddr = 0;
  OsBootOptionList->OsBootOptionCount++;
  BootOption++;

  // Boot file image from USB
  BootOption->DevType   = OsBootDeviceUsb;
  BootOption->HwPart    = 0;
  BootOption->BootFlags = 0;
  BootOption->FsType    = EnumFileSystemTypeAuto;
  BootOption->SwPart    = 0;
  CopyMem (BootOption->Image[0].FileName, "iasimage.bin", sizeof ("iasimage.bin"));
  OsBootOptionList->OsBootOptionCount++;
  BootOption++;



  //ASSERT (OsBootOptionList->OsBootOptionCount <= PcdGet32 (PcdOsBootOptionNumber));
}

/**
 Update Hob Info with platform specific data

 @param  Guid          The GUID to tag the customized HOB.
 @param  HobInfo       The start address of GUID HOB data.
 **/
VOID
EFIAPI
PlatformUpdateHobInfo (
  IN CONST EFI_GUID              *Guid,
  OUT      VOID                  *HobInfo
)
{
  ASSERT (Guid != NULL);
  ASSERT (HobInfo != NULL);

  // Just compare Guid memory addresses which are in Stage2 data section instead of CompareGuid ()
  if (Guid == &gLoaderSerialPortInfoGuid) {
    UpdateSerialPortInfo (HobInfo);
  }  else if (Guid == &gOsBootOptionGuid) {
    UpdateOsBootMediumInfo (HobInfo);
  }
}

/**
  Update PCH NVS and SA NVS area address and size in ACPI table

  @param[in] Current       Pointer to ACPI description header
  @return    EFI_SUCCESS   Operation completed successfully.

**/
EFI_STATUS
EFIAPI
PlatformUpdateAcpiTable (
  IN UINT8                   *Current
)
{
  return EFI_SUCCESS;
}

/**
  Dynamic update of Global NVS data

  @param[in] GnvsIn       Pointer to global nvs region

**/
VOID
EFIAPI
PlatformUpdateAcpiGnvs (
  IN VOID  *GnvsIn
)
{
  EFI_GLOBAL_NVS_AREA  *Gnvs;

  Gnvs = (EFI_GLOBAL_NVS_AREA *)GnvsIn;
  SetMem (Gnvs, sizeof(EFI_GLOBAL_NVS_AREA), 0);

  SocUpdateAcpiGnvs ((VOID *)Gnvs);
}
