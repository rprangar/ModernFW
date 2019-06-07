/** @file
  The platform hook library.

@copyright
  Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.
  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor. This file may be modified by the user, subject to
  the additional terms of the license agreement.
**/

#include <PiPei.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/PciLib.h>
#include <RegAccess.h>

/**
  Disable watch dog timer (Halt TCO timer).
**/
VOID
DisableWatchDogTimer (
  VOID
)
{
  //
  // Program and enable TCO base address.
  //
  PciWrite32 (PCI_LIB_ADDRESS(0, 31, 4, 0x50), TCO_BASE_ADDRESS);
  PciWrite32 (PCI_LIB_ADDRESS(0, 31, 4, 0x54), BIT_(8));

  //
  // Halt the TCO timer.
  //
  IoOr16 (TCO_BASE_ADDRESS + 0x8, BIT_(11));
}

/**
  Enables the execution by writing to the MSR.
**/
VOID
EnableCodeExecution (
  VOID
)
{
  AsmWriteMsr32 (0x120, 0x100);
}

/**
  Get cpu tsc frequency.

  @retval   cpu TSC frequency
**/
UINT32
EFIAPI
GetCpuTscFreqency (
  VOID
)
{
  return ((AsmReadMsr64(0xCE) >> 8) & 0xFF) * 100000;
}
