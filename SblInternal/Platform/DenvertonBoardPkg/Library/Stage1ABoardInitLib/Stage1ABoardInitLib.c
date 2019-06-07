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
#include <Library/BoardInitLib.h>
#include <Library/SerialPortLib.h>
#include <Library/PlatformHookLib.h>
#include <FsptUpd.h>

const
FSPT_UPD TempRamInitParams = {
  .FspUpdHeader = {
    .Signature = FSPT_UPD_SIGNATURE,
    .Revision  = 1,
    .Reserved  = {0},
  },
  .FsptCoreUpd = {
    .MicrocodeRegionBase   = 0,
    .MicrocodeRegionLength = 0,
    .CodeRegionBase        = 0xFF800000,
    .CodeRegionLength      = 0x00800000,
    .Reserved1             = {0},
  },
  .FsptConfig = {
    .PcdFsptPort80RouteDisable = 0,
    .ReservedTempRamInitUpd = {0},
  },
  .UnusedUpdSpace0 = {0},
  .UpdTerminator = 0x55AA,
};


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
  switch (InitPhase) {
  case PostTempRamInit:
    DisableWatchDogTimer ();
    PlatformHookSerialPortInitialize ();
    SerialPortInitialize ();
    break;
  default:
    break;
  }
}

/**
  Get size of Platform Specific Data

  @param[in] none

  @retval    UINT32     Size of Platform Specific Data

**/
UINT32
EFIAPI
GetPlatformDataSize (
  IN  VOID
  )
{
  return 0;
}
