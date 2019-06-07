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
  Enables the execution by writing to the MSR.
**/
VOID
EnableCodeExecution (
  VOID
)
{
  AsmWriteMsr32 (0x120, 0x100);
}
