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

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <IndustryStandard/Pci.h>
#include <RegAccess.h>

RETURN_STATUS
EFIAPI
PlatformHookSerialPortInitialize (
  VOID
  )
{
	//
	// Set CFIO pin mux for UART0:
	//
	MsgBus32AndThenOr (0xC5, 0x4B8, BITS_(12,10), 1 << 10); // South, UART0_RXD
	MsgBus32AndThenOr (0xC5, 0x4C0, BITS_(12,10), 1 << 10); // South, UART0_TXD

  //
	// Program and enable console UART base address.
	//
	PciWrite32 (PCI_LIB_ADDRESS(0, 26, 0, PCI_BASE_ADDRESSREG_OFFSET), SOC_UART_IO_BASE);  
	PciWrite8  (PCI_LIB_ADDRESS(0, 26, 0, PCI_COMMAND_OFFSET), EFI_PCI_COMMAND_IO_SPACE);	
	
  return RETURN_SUCCESS;
}
