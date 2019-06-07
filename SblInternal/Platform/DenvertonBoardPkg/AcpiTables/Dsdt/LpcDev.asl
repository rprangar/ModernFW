/**************************************************************************;
;*                                                                        *;
;*    Intel Confidential                                                  *;
;*                                                                        *;
;*    Intel Corporation - ACPI Reference Code for the Valleyview          *;
;*    Family of Customer Reference Boards.                                *;
;*                                                                        *;
;*                                                                        *;
;*    Copyright (c) 2012 - 2013 Intel Corporation. All rights reserved    *;
;*    This software and associated documentation (if any) is furnished    *;
;*    under a license and may only be used or copied in accordance        *;
;*    with the terms of the license. Except as permitted by such          *;
;*    license, no part of this software or documentation may be           *;
;*    reproduced, stored in a retrieval system, or transmitted in any     *;
;*    form or by any means without the express written consent of         *;
;*    Intel Corporation.                                                  *;
;*                                                                        *;
;*                                                                        *;
;**************************************************************************/
/*++
  This file contains a 'Sample Driver' and is licensed as such  
  under the terms of your license agreement with Intel or your  
  vendor.  This file may be modified by the user, subject to    
  the additional terms of the license agreement                 
--*/

//#define ACPI_BASE_ADDRESS	0x1800
			
Device(IPIC)	// 8259 PIC
{
	Name(_HID,EISAID("PNP0000"))

	Name(_CRS,ResourceTemplate()
	{
		IO(Decode16,0x20,0x20,0x01,0x02)
		IO(Decode16,0x24,0x24,0x01,0x02)
		IO(Decode16,0x28,0x28,0x01,0x02)
		IO(Decode16,0x2C,0x2C,0x01,0x02)
		IO(Decode16,0x30,0x30,0x01,0x02)
		IO(Decode16,0x34,0x34,0x01,0x02)
		IO(Decode16,0x38,0x38,0x01,0x02)
		IO(Decode16,0x3C,0x3C,0x01,0x02)
		IO(Decode16,0xA0,0xA0,0x01,0x02)
		IO(Decode16,0xA4,0xA4,0x01,0x02)
		IO(Decode16,0xA8,0xA8,0x01,0x02)
		IO(Decode16,0xAC,0xAC,0x01,0x02)
		IO(Decode16,0xB0,0xB0,0x01,0x02)
		IO(Decode16,0xB4,0xB4,0x01,0x02)
		IO(Decode16,0xB8,0xB8,0x01,0x02)
		IO(Decode16,0xBC,0xBC,0x01,0x02)
		IO(Decode16,0x4D0,0x4D0,0x01,0x02)
		IRQNoFlags() {2}
	})
}

Device(LDRC)	// LPC Device Resource Consumption
{
	Name(_HID,EISAID("PNP0C02"))        

	Name(_UID,2)

	Name(_CRS,ResourceTemplate()
	{
		IO(Decode16,0x2E,0x2E,0x1,0x02)		// WPCN381U SIO Config Index + Data.
		IO(Decode16,0x4E,0x4E,0x1,0x02)		// LPC Slot Access.
		IO(Decode16,0x61,0x61,0x1,0x1)		// NMI Status.
		IO(Decode16,0x63,0x63,0x1,0x1)		// Processor I/F.
		IO(Decode16,0x65,0x65,0x1,0x1)		// Processor I/F.
		IO(Decode16,0x67,0x67,0x1,0x1)		// Processor I/F.
		//IO(Decode16,0x70,0x70,0x1,0x1)		// NMI Enable.
		IO(Decode16,0x80,0x80,0x1,0x10)		// Postcode.
		IO(Decode16,0x92,0x92,0x1,0x1)		// Processor I/F.
		IO(Decode16,0xB2,0xB2,0x01,0x02)	// Software SMI.
                IO(Decode16,0x1800, 0x1800, 0x1, 0xff)  // ACPI BASE.
		//IO(Decode16,0x400,0x400,0x1,0x80)	// ACPI Base.
		//IO(Decode16,0x500,0x500,0x1,0xFF)	// GPIO Base.
	})
}

Device(TIMR)	// 8254 Timer
{
	Name(_HID,EISAID("PNP0100"))

	Name(_CRS,ResourceTemplate()
	{
		IO(Decode16,0x40,0x40,0x01,0x04)
		IO(Decode16,0x50,0x50,0x10,0x04)
		IRQNoFlags() {0}
	})
}
