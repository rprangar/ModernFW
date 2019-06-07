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

Scope(\_SB) {

//RTC
  Device(RTC)    // RTC
	{
		Name(_HID,EISAID("PNP0B00"))

		Name(_CRS,ResourceTemplate()
	  {
      IO(Decode16,0x70,0x70,0x01,0x08)
		})
	}
//RTC
		
  Device(HPET)	// High Performance Event Timer
  {
    Name (_HID, EisaId ("PNP0103"))
    Name (_UID, 0x00)
    Method (_STA, 0, NotSerialized)
    {
      Return (0x0F)
    }

    Method (_CRS, 0, Serialized)
    {
      Name (RBUF, ResourceTemplate ()
      {
         Memory32Fixed (ReadWrite,
                        0xFED00000,         // Address Base
                        0x00000400,         // Address Length
                        )
        //Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive, ,, )
        //{
        //  0x00000008,   //0xB HPET-2
        //}
     })
     Return (RBUF)
   }
 }
//HPET

  Name(AR00, Package(){
	
		Package(){0x0004FFFF, 0, 0, 16 },  // GLMREG

		Package(){0x0005FFFF, 0, 0, 23 },  // RCEC
		Package(){0x0006FFFF, 0, 0, 18 },  // VRP2

		Package(){0x0009FFFF, 0, 0, 16 },  // PEX0
		Package(){0x000AFFFF, 1, 0, 17 },  // PEX1
		Package(){0x000BFFFF, 2, 0, 18 },  // PEX2
		Package(){0x000CFFFF, 3, 0, 19 },  // PEX3
		Package(){0x000EFFFF, 0, 0, 20 },  // PEX4
		Package(){0x000FFFFF, 1, 0, 21 },  // PEX5
		Package(){0x0010FFFF, 2, 0, 22 },  // PEX6
		Package(){0x0011FFFF, 3, 0, 23 },  // PEX7

		Package(){0x0012FFFF, 0, 0, 16 },  // SMB1

		Package(){0x0013FFFF, 0, 0, 20 },  // SAT0
		Package(){0x0014FFFF, 0, 0, 21 },  // SAT1

		Package(){0x0015FFFF, 0, 0, 19 },  // XHC0

		Package(){0x0016FFFF, 0, 0, 16 },  // VRP0
		Package(){0x0017FFFF, 0, 0, 17 },  // VRP1

		Package(){0x0018FFFF, 0, 0, 16 },  // ME HEC1
		Package(){0x0018FFFF, 1, 0, 17 },  // ME HEC2
		Package(){0x0018FFFF, 2, 0, 18 },  // MEKT
		Package(){0x0018FFFF, 3, 0, 19 },  // ME HECI3

		Package(){0x001AFFFF, 0, 0, 16 },  // UAR0
		Package(){0x001AFFFF, 1, 0, 17 },  // UAR1
		Package(){0x001AFFFF, 2, 0, 18 },  // UAR2

		Package(){0x001BFFFF, 0, 0, 16 },  // IE HECI1
		Package(){0x001BFFFF, 1, 0, 17 },  // IE HECI2
		Package(){0x001BFFFF, 2, 0, 18 },  // IEKT
		Package(){0x001BFFFF, 3, 0, 19 },  // IE HECI3

		Package(){0x001CFFFF, 0, 0, 16 },  // eMMC

		Package(){0x001FFFFF, 0, 0, 23 },  // SMB0, NPK0, P2SB  
  })

  Name(PR00, Package(){
	
		Package(){0x0004FFFF, 0, LNKA, 0 },  // GLMREG

		Package(){0x0005FFFF, 0, LNKH, 0 },  // RCEC
		Package(){0x0006FFFF, 0, LNKC, 0 },  // VRP2

		Package(){0x0009FFFF, 0, LNKA, 0 },  // PEX0
		Package(){0x000AFFFF, 1, LNKB, 0 },  // PEX1
		Package(){0x000BFFFF, 2, LNKC, 0 },  // PEX2
		Package(){0x000CFFFF, 3, LNKD, 0 },  // PEX3
		Package(){0x000EFFFF, 0, LNKE, 0 },  // PEX4
		Package(){0x000FFFFF, 1, LNKF, 0 },  // PEX5
		Package(){0x0010FFFF, 2, LNKG, 0 },  // PEX6
		Package(){0x0011FFFF, 3, LNKH, 0 },  // PEX7

		Package(){0x0012FFFF, 0, LNKA, 0 },  // SMB1

		Package(){0x0013FFFF, 0, LNKE, 0 },  // SAT0
		Package(){0x0014FFFF, 0, LNKF, 0 },  // SAT1

		Package(){0x0015FFFF, 0, LNKD, 0 },  // XHC0

		Package(){0x0016FFFF, 0, LNKA, 0 },  // VRP0
		Package(){0x0017FFFF, 0, LNKB, 0 },  // VRP1

		Package(){0x0018FFFF, 0, LNKA, 0 },  // ME HECI1
		Package(){0x0018FFFF, 1, LNKB, 0 },  // ME HEC2
		Package(){0x0018FFFF, 2, LNKC, 0 },  // MEKT
		Package(){0x0018FFFF, 3, LNKD, 0 },  // ME HECI3

		Package(){0x001AFFFF, 0, LNKA, 0 },  // UAR0
		Package(){0x001AFFFF, 1, LNKB, 0 },  // UAR1
		Package(){0x001AFFFF, 2, LNKC, 0 },  // UAR2

		Package(){0x001BFFFF, 0, LNKA, 0 },  // IE HECI1
		Package(){0x001BFFFF, 1, LNKB, 0 },  // IE HECI2
		Package(){0x001BFFFF, 2, LNKC, 0 },  // IEKT
		Package(){0x001BFFFF, 3, LNKD, 0 },  // IE HECI3

		Package(){0x001CFFFF, 0, LNKA, 0 },  // eMMC

		Package(){0x001FFFFF, 0, LNKH, 0 },  // SMB0
  })

  Name(PR01, Package(){
    Package(){0x0000FFFF, 0, LNKC, 0}, // IQAT
  }) 

  Name(AR01, Package(){
    Package(){0x0000FFFF, 0, 0, 18}, // IQAT
  })

  Name(PR02, Package(){
// PCIE Port #0 Slot
    Package(){0x0000FFFF, 0, LNKA, 0 },
    Package(){0x0000FFFF, 1, LNKB, 0 },
    Package(){0x0000FFFF, 2, LNKC, 0 },
    Package(){0x0000FFFF, 3, LNKD, 0 },
  })

  Name(AR02, Package(){
// PCIE Port #0 Slot
    Package(){0x0000FFFF, 0, 0, 16 },
    Package(){0x0000FFFF, 1, 0, 17 },
    Package(){0x0000FFFF, 2, 0, 18 },
    Package(){0x0000FFFF, 3, 0, 19 },
  })

  Name(PR03, Package(){
// PCIE Port #1 Slot
    Package(){0x0000FFFF, 0, LNKB, 0 },
    Package(){0x0000FFFF, 1, LNKC, 0 },
    Package(){0x0000FFFF, 2, LNKD, 0 },
    Package(){0x0000FFFF, 3, LNKA, 0 },
  })

  Name(AR03, Package(){
// PCIE Port #1 Slot
    Package(){0x0000FFFF, 0, 0, 17 },
    Package(){0x0000FFFF, 1, 0, 18 },
    Package(){0x0000FFFF, 2, 0, 19 },
    Package(){0x0000FFFF, 3, 0, 16 },
  })

  
  Name(PR04, Package(){
// PCIE Port #2 Slot
    Package(){0x0000FFFF, 0, LNKC, 0 },
    Package(){0x0000FFFF, 1, LNKD, 0 },
    Package(){0x0000FFFF, 2, LNKA, 0 },
    Package(){0x0000FFFF, 3, LNKB, 0 },
  })

  Name(AR04, Package(){
// PCIE Port #2 Slot
    Package(){0x0000FFFF, 0, 0, 18 },
    Package(){0x0000FFFF, 1, 0, 19 },
    Package(){0x0000FFFF, 2, 0, 16 },
    Package(){0x0000FFFF, 3, 0, 17 },
  })
   
  Name(PR05, Package(){
// PCIE Port #3 Slot
    Package(){0x0000FFFF, 0, LNKD, 0 },
    Package(){0x0000FFFF, 1, LNKA, 0 },
    Package(){0x0000FFFF, 2, LNKB, 0 },
    Package(){0x0000FFFF, 3, LNKC, 0 },
  }) 
  
  Name(AR05, Package(){
// PCIE Port #3 Slot
    Package(){0x0000FFFF, 0, 0, 19 },
    Package(){0x0000FFFF, 1, 0, 16 },
    Package(){0x0000FFFF, 2, 0, 17 },
    Package(){0x0000FFFF, 3, 0, 18 },
  })
  
  Name(PR06, Package(){
// PCIE Port #4 Slot
    Package(){0x0000FFFF, 0, LNKE, 0 },
    Package(){0x0000FFFF, 1, LNKF, 0 },
    Package(){0x0000FFFF, 2, LNKG, 0 },
    Package(){0x0000FFFF, 3, LNKH, 0 },
  }) 
  
  Name(AR06, Package(){
// PCIE Port #4 Slot
    Package(){0x0000FFFF, 0, 0, 20 },
    Package(){0x0000FFFF, 1, 0, 21 },
    Package(){0x0000FFFF, 2, 0, 22 },
    Package(){0x0000FFFF, 3, 0, 23 },
  })

  Name(PR07, Package(){
// PCIE Port #5 Slot
    Package(){0x0000FFFF, 0, LNKF, 0 },
    Package(){0x0000FFFF, 1, LNKG, 0 },
    Package(){0x0000FFFF, 2, LNKH, 0 },
    Package(){0x0000FFFF, 3, LNKE, 0 },
  })    
  
  Name(AR07, Package(){
// PCIE Port #5 Slot
    Package(){0x0000FFFF, 0, 0, 21 },
    Package(){0x0000FFFF, 1, 0, 22 },
    Package(){0x0000FFFF, 2, 0, 23 },
    Package(){0x0000FFFF, 3, 0, 20 },
  })

  Name(PR08, Package(){
// PCIE Port #6 Slot
    Package(){0x0000FFFF, 0, LNKG, 0 },
    Package(){0x0000FFFF, 1, LNKH, 0 },
    Package(){0x0000FFFF, 2, LNKE, 0 },
    Package(){0x0000FFFF, 3, LNKF, 0 },
  })    
  
  Name(AR08, Package(){
// PCIE Port #6 Slot
    Package(){0x0000FFFF, 0, 0, 22 },
    Package(){0x0000FFFF, 1, 0, 23 },
    Package(){0x0000FFFF, 2, 0, 20 },
    Package(){0x0000FFFF, 3, 0, 21 },
  })

  Name(PR09, Package(){
// PCIE Port #7 Slot
    Package(){0x0000FFFF, 0, LNKH, 0 },
    Package(){0x0000FFFF, 1, LNKE, 0 },
    Package(){0x0000FFFF, 2, LNKF, 0 },
    Package(){0x0000FFFF, 3, LNKG, 0 },
  })    
  
  Name(AR09, Package(){
// PCIE Port #7 Slot
    Package(){0x0000FFFF, 0, 0, 23 },
    Package(){0x0000FFFF, 1, 0, 20 },
    Package(){0x0000FFFF, 2, 0, 21 },
    Package(){0x0000FFFF, 3, 0, 22 },
  })

  Name(PR0A, Package(){
// NIC0, NIC1
    Package(){0x0000FFFF, 0, LNKA, 0 },
    Package(){0x0000FFFF, 1, LNKA, 0 },
  })    
  
  Name(AR0A, Package(){
// NIC0, NIC1
    Package(){0x0000FFFF, 0, 0, 16 },
    Package(){0x0000FFFF, 1, 0, 17 },
  })

  Name(PR0B, Package(){
// NIC2, NIC3
    Package(){0x0000FFFF, 0, LNKB, 0 },
    Package(){0x0000FFFF, 1, LNKB, 0 },
  })    
  
  Name(AR0B, Package(){
// NIC2, NIC3
    Package(){0x0000FFFF, 0, 0, 17 },
    Package(){0x0000FFFF, 1, 0, 17 },
  })


//---------------------------------------------------------------------------
// List of IRQ resource buffers compatible with _PRS return format.
//---------------------------------------------------------------------------
// Naming legend:
// RSxy, PRSy - name of the IRQ resource buffer to be returned by _PRS, "xy" - last two characters of IRQ Link name.
// Note. PRSy name is generated if IRQ Link name starts from "LNK".
// HLxy , LLxy - reference names, can be used to access bit mask of available IRQs. HL and LL stand for active High(Low) Level triggered Irq model.
//---------------------------------------------------------------------------
  Name(PRSA, ResourceTemplate(){	// Link name: LNKA
    IRQ(Level, ActiveLow, Shared) {6,7,10,11,12,14,15}
  })
  Alias(PRSA,PRSB)	// Link name: LNKB
  Alias(PRSA,PRSC)	// Link name: LNKC
  Alias(PRSA,PRSD)	// Link name: LNKD
  Alias(PRSA,PRSE)	// Link name: LNKE
  Alias(PRSA,PRSF)	// Link name: LNKF
  Alias(PRSA,PRSG)	// Link name: LNKG
  Alias(PRSA,PRSH)	// Link name: LNKH
//---------------------------------------------------------------------------
// Begin PCI tree object scope
//---------------------------------------------------------------------------

  Device(PCI0) { // PCI Bridge "Host Bridge"
    Name(_HID, EISAID("PNP0A08"))	// Indicates PCI Express/PCI-X Mode2 host hierarchy
    Name(_CID, EISAID("PNP0A03"))	// To support legacy OS that doesn't understand the new HID
    Name(_ADR, 0x00000000)
    Method(^BN00, 0){ return(0x0000) }	// Returns default Bus number for Peer PCI busses. Name can be overriden with control method placed directly under Device scope
    Method(_BBN, 0){ return(BN00()) }	// Bus number, optional for the Root PCI Bus
    Name(_UID, 0x0000)	// Unique Bus ID, optional

    Method(_PRT,0) {
      If(PICM) {Return(AR00)} // APIC mode
      Return (PR00) // PIC Mode
    } // end _PRT    

	#include "HostBus.asl"

	Device(APIC)
	{
		Name(_HID,EISAID("PNP0003"))

		Name(_CRS,ResourceTemplate()
				{
					Memory32Fixed(ReadOnly,0xFEC00000,0x1000) // IOAPIC
				}		
		)
	}	

	// Global Registers
        Device (GREG) {
            Name   (_ADR, 0x00040000)
        }

        // Root Complex Event Collector
        Device (RCEC) {
            Name   (_ADR, 0x00050000)
        }

        // Virtual root port 2
        Device (VRP2) {
            Name   (_ADR, 0x00060000)
            Method (_PRT, 0) {
                If (LEqual(PICM, Zero)) {
                    Return (PR01)
                }
                Return (AR01)
            }

            // Iqat
            Device (IQAT) {
                Name   (_ADR, 0x00000000)
            }
        }


        // PCI Express Port 0
        Device (PEX0) {
            Name   (_ADR, 0x00090000)
            Method (_PRW, 0) {
                Return (Package (0x02) {0x09, 0x04})
            }
            Method (_PRT, 0) {
                If (LEqual(PICM, Zero)) {
                    Return (PR02)
                }
                Return (AR02)
            }

            // PCI Express Slot 0
            Device (SLT0) {
                Name   (_ADR, 0x00000000)
            }
        }

        // PCI Express Port 1
        Device (PEX1) {
            Name   (_ADR, 0x000A0000)
            Method (_PRW, 0) {
                Return (Package (0x02) {0x09, 0x04})
            }
            Method (_PRT, 0) {
                If (LEqual(PICM, Zero)) {
                    Return (PR03)
                }
                Return (AR03)
            }
        }

	// PCI Express Port 2
        Device (PEX2) {
            Name   (_ADR, 0x000B0000)
            Method (_PRW, 0) {
                Return (Package (0x02) {0x09, 0x04})
            }
            Method (_PRT, 0) {
                If (LEqual(PICM, Zero)) {
                    Return (PR04)
                }
                Return (AR04)
            }
        }

	// PCI Express Port 3
        Device (PEX3) {
            Name   (_ADR, 0x000C0000)
            Method (_PRW, 0) {
                Return (Package (0x02) {0x09, 0x04})
            }
            Method (_PRT, 0) {
                If (LEqual(PICM, Zero)) {
                    Return (PR05)
                }
                Return (AR05)
            }
        }

	// PCI Express Port 4
        Device (PEX4) {
            Name   (_ADR, 0x000E0000)
            Method (_PRW, 0) {
                Return (Package (0x02) {0x09, 0x04})
            }
            Method (_PRT, 0) {
                If (LEqual(PICM, Zero)) {
                    Return (PR06)
                }
                Return (AR06)
            }
        }

        // PCI Express Port 5
        Device (PEX5) {
            Name   (_ADR, 0x000F0000)
            Method (_PRW, 0) {
                Return (Package (0x02) {0x09, 0x04})
            }
            Method (_PRT, 0) {
                If (LEqual(PICM, Zero)) {
                    Return (PR07)
                }
                Return (AR07)
            }
        }

        // PCI Express Port 6
        Device (PEX6) {
            Name   (_ADR, 0x00100000)
            Method (_PRW, 0) {
                Return (Package (0x02) {0x09, 0x04})
            }
            Method (_PRT, 0) {
                If (LEqual(PICM, Zero)) {
                    Return (PR08)
                }
                Return (AR08)
            }
        }

        // PCI Express Port 7
        Device (PEX7) {
            Name   (_ADR, 0x00110000)
            Method (_PRW, 0) {
                Return (Package (0x02) {0x09, 0x04})
            }
            Method (_PRT, 0) {
                If (LEqual(PICM, Zero)) {
                    Return (PR09)
                }
                Return (AR09)
            }
        }

        // SMBus controller
        Device (SMB1) {
            Name   (_ADR, 0x00120000)
        }

        // SATA controller 0
        Device (SAT0) {
            Name   (_ADR, 0x00130000)
        }

        // SATA controller 1
        Device (SAT1) {
            Name   (_ADR, 0x00140000)
        }

        // XHCI USB controller
        Device (XHC1) {
            Name   (_ADR, 0x00150000)
            Method (_PRW, 0) {
                Return (Package (0x02) {0x0D, 0x05})
            }
        }

	// Virtual root port 0
        Device (VRP0) {
            Name   (_ADR, 0x00160000)
            Method (_PRT, 0) {
                If (LEqual(PICM, Zero)) {
                    Return (PR0A)
                }
                Return (AR0A)
            }

            // NIC0
            Device (LAN0) {
                Name   (_ADR, 0x00000000)
                Method (_PRW, 0) {
                    Return (Package (0x02) {0x70, 0x05})
                }
            }

            // NIC1
            Device (LAN1) {
                Name   (_ADR, 0x00000001)
                Method (_PRW, 0) {
                    Return (Package (0x02) {0x70, 0x05})
                }
            }
        }

        // Virtual root port 1
        Device (VRP1) {
            Name   (_ADR, 0x00170000)
            Method (_PRT, 0) {
                If (LEqual(PICM, Zero)) {
                    Return (PR0B)
                }
                Return (AR0B)
            }

            // NIC2
            Device (LAN2) {
                Name   (_ADR, 0x00000000)
                Method (_PRW, 0) {
                    Return (Package (0x02) {0x70, 0x05})
                }
            }

            // NIC3
            Device (LAN3) {
                Name   (_ADR, 0x00000001)
                Method (_PRW, 0) {
                    Return (Package (0x02) {0x70, 0x05})
                }
            }
        }

	// ME HECI
        Device (HECI) {
            Name   (_ADR, 0x00180000)
        }

        // ME HECI2
        Device (HEC2) {
            Name   (_ADR, 0x00180001)
        }

        // MEKT on PCH
        Device (MEKT) {
            Name   (_ADR, 0x00180003)
        }

        // ME HECI3
        Device (HEC3) {
            Name   (_ADR, 0x00180004)
        }

        // UART 0
        Device (UAR0) {
            Name   (_ADR, 0x001A0000)
        }

        // UART 1
        Device (UAR1) {
            Name   (_ADR, 0x001A0001)
        }

        // UART 2
        Device (UAR2) {
            Name   (_ADR, 0x001A0002)
        }

        // IE HECI1
        Device (IEH1) {
            Name   (_ADR, 0x001B0000)
        }

        // IE HECI2
        Device (IEH2) {
            Name   (_ADR, 0x001B0001)
        }

        // IEKT
        Device (IEKT) {
            Name   (_ADR, 0x001B0003)
        }

        // IE HECI3
        Device (IEH3) {
            Name   (_ADR, 0x001B0004)
        }

        // eMMC
        Device (EMMC) {
            Name   (_ADR, 0x001C0000)

            //#include "EMMC.asi"
	    Device (EMMD)
	    {
		Name(_ADR, 0x08)
		Method(_RMV,0,NotSerialized)
		{
			Return(Zero)
		}
	    }

        }

        // ISA Bridge on ICH
        Device (LPC0) {
            Name   (_ADR, 0x001F0000)

		// Add Mother.asi and SIO.asi from BIOS
            //#include "IchLpc.asi"
        }

        // Primary to sideband bridge
        Device (P2SB) {
            Name   (_ADR, 0x001F0001)

            //#include "P2SB.asi"
	    OperationRegion(SBRB,PCI_Config,0x10,0x08)
	    Field(SBRB,AnyAcc,NoLock,Preserve)
	    {
		SBRL, 32,
		SBRH, 32
	    }
        }

        // PMC Device
        Device (PMC0) {
            Name   (_ADR, 0x001F0002)

		// Add PMC.asi form BIOS
            //#include "PMC.asi"
        }

        // SMBus controller
        Device (SMB0) {
            Name   (_ADR, 0x001F0004)
        }

        // SPI controller
        Device (SPI0) {
            Name   (_ADR, 0x001F0005)
        }

        // Northpeak DFX
        Device (NPK0) {
            Name   (_ADR, 0x001F0007)
        }

	Device(LPCB) { // LPC Bridge
		Name(_ADR, 0x001F0000)
		#include "LpcB.asl"
	} // end "LPC Bridge"
		
  } // end PCI0 Bridge "Host Bridge"
} // end _SB scope
