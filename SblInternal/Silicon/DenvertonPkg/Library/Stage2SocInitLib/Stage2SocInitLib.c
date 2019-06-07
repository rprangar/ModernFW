/** @file
  The platform hook library.

@copyright
  Copyright (c) 2013 - 2015, Intel Corporation. All rights reserved
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
#include <Base.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PciLib.h>
#include <Library/PcdLib.h>
#include <RegAccess.h>
#include <GlobalNvsArea.h>

/**
  Get size of global nvs area.

  @param[in] none

  @retval    UINT32     Size of global nvs area.

**/
UINT32
EFIAPI
GetAcpiGnvsSize (
  VOID
)
{
  return sizeof(EFI_GLOBAL_NVS_AREA);
}

/**
 Update GPIO address and length to global NVS data.

 @param [in] GnvsIn Pointer to Global NVS data.
 **/
VOID
EFIAPI
SocUpdateAcpiGnvs (
  IN VOID  *GnvsIn
)
{
  // EFI_GLOBAL_NVS_AREA  *Gnvs;

  // Gnvs = (EFI_GLOBAL_NVS_AREA *)GnvsIn;

}
