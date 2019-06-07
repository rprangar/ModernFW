/**************************************************************************;
;*                                                                        *;
;*    Intel Confidential                                                  *;
;*                                                                        *;
;*    Intel Corporation - ACPI Reference Code for the Sandy Bridge        *;
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

DefinitionBlock (
    "DSDT.aml",
    "DSDT",
    0x05,  // DSDT revision.
        // A Revision field value greater than or equal to 2 signifies that integers
        // declared within the Definition Block are to be evaluated as 64-bit values
    "INTEL", // OEM ID (6 byte string)
    "HARRISONVILLE", // OEM table ID  (8 byte string)
    0x03 // OEM version of DSDT table (4 byte Integer)
    )

// BEGIN OF ASL SCOPE
{
//  Method(ADBG, 1, Serialized)
//  {
//    Return(0)
//  }

// Defined in Platform.asl
OperationRegion (DBG0, SystemIO, 0x80, 1)
Field (DBG0, ByteAcc, NoLock, Preserve)
{ IO80, 8 }

// Miscellaneous services enabled in Project
    #include "GlobalNvs.asl"
    #include "PciTree.asl"
//	TODO : Add the following for DNV going ahead
//    include ("Pch.asl")
//    include ("Platform.asl")
//    include ("PciDrc.asl")



Scope(\_PR)
{
	Processor (CPU0,0x01,0x1810,0x06)
	{
		Method (_STA,0)
		{
			Return (0x0F)
		}
	}


	Processor (CPU1,0x02,0x1810,0x06)
	{
		Method (_STA,0)
		{
			if (LGreater (PCNT,0x01))
			{
				Return (0x0F)
			}
			Return (0x0)
		}
	}

	Processor (CPU2,0x03,0x1810,0x06)
	{
		Method (_STA,0)
		{
			if (LGreater (PCNT,0x02))
			{
				Return (0x0F)
			}
			Return (0x0)
		}
	}

	Processor (CPU3,0x04,0x1810,0x06)
	{
		Method (_STA,0)
		{
			if (LGreater (PCNT,0x03))
			{
				Return (0x0F)
			}
			Return (0x0)
		}
	}

	Processor (CPU4,0x05,0x1810,0x06)
	{
		Method (_STA,0)
		{
			if (LGreater (PCNT,0x04))
			{
				Return (0x0F)
			}
			Return (0x0)
		}
	}

	Processor (CPU5,0x06,0x1810,0x06)
	{
		Method (_STA,0)
		{
			if (LGreater (PCNT,0x05))
			{
				Return (0x0F)
			}
			Return (0x0)
		}
	}

	Processor (CPU6,0x07,0x1810,0x06)
	{
		Method (_STA,0)
		{
			if (LGreater (PCNT,0x06))
			{
				Return (0x0F)
			}
			Return (0x0)
		}
	}

	Processor (CPU7,0x08,0x1810,0x06)
	{
		Method (_STA,0)
		{
			if (LGreater (PCNT,0x07))
			{
				Return (0x0F)
			}
			Return (0x0)
		}
	}

	Processor (CPU8,0x09,0x1810,0x06)
	{
		Method (_STA,0)
		{
			if (LGreater (PCNT,0x08))
			{
				Return (0x0F)
			}
			Return (0x0)
		}
	}

	Processor (CPU9,0x0A,0x1810,0x06)
	{
		Method (_STA,0)
		{
			if (LGreater (PCNT,0x09))
			{
				Return (0x0F)
			}
			Return (0x0)
		}
	}

	Processor (CPUA,0x0B,0x1810,0x06)
	{
		Method (_STA,0)
		{
			if (LGreater (PCNT,0x0A))
			{
				Return (0x0F)
			}
			Return (0x0)
		}
	}

	Processor (CPUB,0x0C,0x1810,0x06)
	{
		Method (_STA,0)
		{
			if (LGreater (PCNT,0x0B))
			{
				Return (0x0F)
			}
			Return (0x0)
		}
	}

	Processor (CPUC,0x0D,0x1810,0x06)
	{
		Method (_STA,0)
		{
			if (LGreater (PCNT,0x0C))
			{
				Return (0x0F)
			}
			Return (0x0)
		}
	}

	Processor (CPUD,0x0E,0x1810,0x06)
	{
		Method (_STA,0)
		{
			if (LGreater (PCNT,0x0D))
			{
				Return (0x0F)
			}
			Return (0x0)
		}
	}

	Processor (CPUE,0x0F,0x1810,0x06)
	{
		Method (_STA,0)
		{
			if (LGreater (PCNT,0x0E))
			{
				Return (0x0F)
			}
			Return (0x0)
		}
	}

	Processor (CPUF,0x10,0x1810,0x06)
	{
		Method (_STA,0)
		{
			if (LGreater (PCNT,0x0F))
			{
				Return (0x0F)
			}
			Return (0x0)
		}
	}

}


//
// Sleep states supported by Chipset/Board.
//----------------------------------------------------------------------
// SSx - BIOS setup controlled enabled _Sx Sleep state status
// Values to be written to SLP_TYPE register are provided by SBACPI.SDL (South Bridge ACPI ModulePart)
    Name(\_S0, Package(4){0x0,0x0,0,0}) // mandatory System state
//   Name(\_S3, Package(4){0x5,0x0,0,0})
    Name(\_S4, Package(4){0x6,0x0,0,0})
    Name(\_S5, Package(4){0x7,0x0,0,0}) // mandatory System state

    Method(PTS, 1) {        // METHOD CALLED FROM _PTS PRIOR TO ENTER ANY SLEEP STATE
        If(Arg0)            // entering any sleep state
        {
        }
    }
    Method(WAK, 1) {        // METHOD CALLED FROM _WAK RIGHT AFTER WAKE UP
    }
}// End of ASL File
