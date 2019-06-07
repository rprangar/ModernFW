/**************************************************************************;
;*                                                                        *;
;*    Intel Confidential                                                  *;
;*                                                                        *;
;*    Intel Corporation - ACPI Reference Code for the Valleyview          *;
;*    Family of Customer Reference Boards.                                *;
;*                                                                        *;
;*                                                                        *;
;*    Copyright (c)  1999 - 2013 Intel Corporation. All rights reserved   *;
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

Name(PICM, 0)	// Global Name, returns current Interrupt controller mode; updated from _PIC control method

// The _PIC Control Method is optional for ACPI design.  It allows the
// OS to inform the ASL code which interrupt controller is being used,
// the 8259 or APIC.  The reference code in this document will address
// PCI IRQ Routing and resource allocation for both cases.
//
// The values passed into _PIC are:
//	 0 = 8259
//	 1 = IOAPIC

Method(\_PIC,1)
{
  Store(Arg0,GPIC)
  Store(Arg0,PICM)
}

  // Define a Global region of ACPI NVS Region that may be used for any
  // type of implementation.  The starting offset and size will be fixed
  // up by the System BIOS during POST.  Note that the Size must be a word
  // in size to be fixed up correctly.

  OperationRegion(GNVS,SystemMemory,0x12345678,0x2000)
  Field(GNVS,AnyAcc,Lock,Preserve)
  {
    Offset(0),	 // Miscellaneous Dynamic Registers:
    OSYS,	16,	 //   (00) Operating System
    SMIF,	8,	 //   (02) SMI Function Call (ASL to SMI via I/O Trap)
    PRM0,	8,	 //   (03) SMIF - Parameter 0
    PRM1,	8,	 //   (04) SMIF - Parameter 1
    SCIF,	8,	 //   (05) SCI Function Call (SMI to ASL via _L00)
    PRM2,	8,	 //   (06) SCIF - Parameter 0
    PRM3,	8,	 //   (07) SCIF - Parameter 1
    LCKF,	8,	 //   (08) Global Lock Function Call (EC Communication)
    PRM4,	8,	 //   (09) LCKF - Parameter 0
    PRM5,	8,	 //   (10) LCKF - Parameter 1
    P80D,	32,	 //   (11) Port 80 Debug Port Value
    LIDS,	8,	 //   (15) Lid State (Lid Open = 1)
    PWRS,	8,	 //   (16) Power State (AC Mode = 1)
    DBGS,	8,	 //   (17) Debug State
    APIC,	8,	 //   (18) APIC Enabled by SBIOS (APIC Enabled = 1)
    MPEN,	8,	 //   (19) Number of Logical Processors if MP Enabled != 0
    PCP0,	8,	 //   (20) PDC Settings, Processor 0
    PCP1,	8,	 //   (21) PDC Settings, Processor 1
    PPCM,	8,	 //   (22) Maximum PPC state
    PPMF,	32,	 //   (23) PPM Flags (Same as CFGD)
    MORD,   	8,	 //   (27) Memory Overwrite Request Data
    TCGP,   	8,	 //   (28) Used for save the Mor and/or physical presence paramter
    PPRP,   	32,	 //   (29) Physical Presence request operation response
    PPRQ,   	8,	 //   (33) Physical Presence request operation
    LPPR,   	8,	 //   (34) Last Physical Presence request operation
    OSCC,	8,	 //   (35) PCIE OSC Control
    NEXP,	8,	 //   (36) Native PCIE Setup Value
    DSEN,	8,	 //   (37) _DOS Display Support Flag.
    ECON,	8,	 //   (38) Embedded Controller Availability Flag.
    GPIC,	8,	 //   (39) Global IOAPIC/8259 Interrupt Mode Flag.
    AOAC,   	8,   	 //   (40) AOAC Configuration
    XHCI,   	8,   	 //   (41) xHCI controller mode
    PMEN,   	8,   	 //   (42) PMIC enable/disable
    PCNT,	8,	 //   (43) Processor Count
    // Add more going ahead

    // Device NVS
    Offset(0x1000), 
    //
    // Lpss controllers 
    //
    PCIB,     	32,
    PCIT,     	32,
    D10A,     	32,  //DMA1 
    D10L,     	32, 
    D11A,     	32,  
    D11L,     	32,         
    P10A,     	32,  //  PWM1
    P10L,     	32,  
    P11A,     	32,  
    P11L,     	32,  
    P20A,     	32,  //  PWM2
    P20L,     	32,  
    P21A,     	32,  
    P21L,     	32, 
    SP0A,     	32,  // SPI  
    SP0L,     	32,      
    SP1A,     	32,  
    SP1L,     	32,       

    D20A,     	32,  //DMA2 
    D20L,     	32, 
    D21A,     	32,  
    D21L,     	32, 
    //
    // Scc controllers 
    //
    eM0A,     	32,  //  EMMC
    eM0L,     	32,  
    eM1A,     	32,  
    eM1L,     	32,  
    SI0A,     	32,  //  SDIO
    SI0L,     	32,
    SI1A,     	32,  
    SI1L,     	32,
    SD0A,     	32,  //  SDCard  
    SD0L,     	32,
    SD1A,     	32,   
    SD1L,     	32,           
    PCIM,     	1,   //LPSS SIO devices PCI mode enable. 1: PCI mode enalbe; 0: ACPI mode enable           
	      	,7,
    SCCM,     	1,   //SCC devices PCI mode enable. 1: PCI mode enalbe; 0: ACPI mode enable           
	      	,7,

    // Add I2C, UART going ahead
  }

