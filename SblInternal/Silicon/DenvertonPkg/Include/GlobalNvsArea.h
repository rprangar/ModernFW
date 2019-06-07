/** @file

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2016 Intel Corporation.

  The source code contained or described herein and all documents related to the
  source code ("Material") are owned by Intel Corporation or its suppliers or
  licensors. Title to the Material remains with Intel Corporation or its suppliers
  and licensors. The Material may contain trade secrets and proprietary and
  confidential information of Intel Corporation and its suppliers and licensors,
  and is protected by worldwide copyright and trade secret laws and treaty
  provisions. No part of the Material may be used, copied, reproduced, modified,
  published, uploaded, posted, transmitted, distributed, or disclosed in any way
  without Intel's prior express written permission.

  No license under any patent, copyright, trade secret or other intellectual
  property right is granted to or conferred upon you by disclosure or delivery
  of the Materials, either expressly, by implication, inducement, estoppel or
  otherwise. Any license under such intellectual property rights must be
  express and approved by Intel in writing.

  Unless otherwise agreed by Intel in writing, you may not remove or alter
  this notice or any other notice embedded in Materials by Intel or
  Intel's suppliers or licensors in any way.

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/


#ifndef _GLOBAL_NVS_AREA_H_
#define _GLOBAL_NVS_AREA_H_

//
// Includes
//
#define GLOBAL_NVS_DEVICE_ENABLE 1
#define GLOBAL_NVS_DEVICE_DISABLE 0

//
// Global NVS Area Protocol GUID
//
#define EFI_GLOBAL_NVS_AREA_PROTOCOL_GUID \
{ 0x74e1e48, 0x8132, 0x47a1, 0x8c, 0x2c, 0x3f, 0x14, 0xad, 0x9a, 0x66, 0xdc }
//
// Revision id - Added TPM related fields
//
#define GLOBAL_NVS_AREA_RIVISION_1       1
//
// Extern the GUID for protocol users.
//
//extern EFI_GUID gEfiGlobalNvsAreaProtocolGuid;

///
/// Global NVS Area definition
///
#pragma pack (1)
/**
  Miscellaneous Dynamic Values, the definitions below need to be matched
  GNVS definitions in DSDT.ASL
**/
typedef struct {
    UINT16  OSYS;	 //   (00) Operating System
    UINT8   SMIF;	 //   (02) SMI Function Call (ASL to SMI via I/O Trap)
    UINT8   PRM0;	 //   (03) SMIF - Parameter 0
    UINT8   PRM1;	 //   (04) SMIF - Parameter 1
    UINT8   SCIF;	 //   (05) SCI Function Call (SMI to ASL via _L00)
    UINT8   PRM2;	 //   (06) SCIF - Parameter 0
    UINT8   PRM3;	 //   (07) SCIF - Parameter 1
    UINT8   LCKF;	 //   (08) Global Lock Function Call (EC Communication)
    UINT8   PRM4;	 //   (09) LCKF - Parameter 0
    UINT8   PRM5;	 //   (10) LCKF - Parameter 1
    UINT32  P80D;	 //   (11) Port 80 Debug Port Value
    UINT8   LIDS;	 //   (15) Lid State (Lid Open = 1)
    UINT8   PWRS;	 //   (16) Power State (AC Mode = 1)
    UINT8   DBGS;	 //   (17) Debug State
    UINT8   APIC;	 //   (18) APIC Enabled by SBIOS (APIC Enabled = 1)
    UINT8   MPEN;	 //   (19) Number of Logical Processors if MP Enabled != 0
    UINT8   PCP0;	 //   (20) PDC Settings, Processor 0
    UINT8   PCP1;	 //   (21) PDC Settings, Processor 1
    UINT8   PPCM;	 //   (22) Maximum PPC state
    UINT32  PPMF;	 //   (23) PPM Flags (Same as CFGD)
    UINT8   MORD;	 //   (27) Memory Overwrite Request Data
    UINT8   TCGP;	 //   (28) Used for save the Mor and/or physical presence paramter
    UINT32  PPRP;	 //   (29) Physical Presence request operation response
    UINT8   PPRQ;	 //   (33) Physical Presence request operation
    UINT8   LPPR;	 //   (34) Last Physical Presence request operation
    UINT8   OSCC;	 //   (35) PCIE OSC Control
    UINT8   NEXP;	 //   (36) Native PCIE Setup Value
    UINT8   DSEN;	 //   (37) _DOS Display Support Flag.
    UINT8   ECON;	 //   (38) Embedded Controller Availability Flag.
    UINT8   GPIC;	 //   (39) Global IOAPIC/8259 Interrupt Mode Flag.
    UINT8   AOAC;  	 //   (40) AOAC Configuration
    UINT8   XHCI;    //   (41) xHCI controller mode
    UINT8   PMEN;  	 //   (42) PMIC enable/disable
    UINT8   PCNT;	 //   (43) Processor Count
    //
    // Lpss controllers 
    //
    UINT32  PCIB;
    UINT32  PCIT;
    UINT32	D10A;	//DMA1 
    UINT32	D10L;
    UINT32	D11A;
    UINT32	D11L;         
    UINT32	P10A;	//  PWM1
    UINT32	P10L;  
    UINT32	P11A;  
    UINT32	P11L;  
    UINT32	P20A;	//  PWM2
    UINT32	P20L;  
    UINT32	P21A;  
    UINT32	P21L; 
    UINT32	SP0A;  	// SPI  
    UINT32	SP0L;      
    UINT32	SP1A;  
    UINT32	SP1L;       

    UINT32	D20A;	//DMA2 
    UINT32	D20L; 
    UINT32	D21A;  
    UINT32	D21L; 
    //
    // Scc controllers 
    //
    UINT32	eM0A;  	//  EMMC
    UINT32	eM0L;  
    UINT32	eM1A;  
    UINT32	eM1L;  
    UINT32	SI0A;	//  SDIO
    UINT32	SI0L;
    UINT32	SI1A;  
    UINT32	SI1L;
    UINT32	SD0A;	//  SDCard  
    UINT32	SD0L;
    UINT32	SD1A;   
    UINT32	SD1L;           
    UINT8 	PCIM;   //LPSS SIO devices PCI mode enable. 1: PCI mode enalbe; 0: ACPI mode enable
    UINT8 	SCCM;   //SCC devices PCI mode enable. 1: PCI mode enalbe; 0: ACPI mode enable
}EFI_GLOBAL_NVS_AREA;
#pragma pack ()

///
/// Global NVS Area Protocol
///
typedef struct _EFI_GLOBAL_NVS_AREA_PROTOCOL {
  EFI_GLOBAL_NVS_AREA     *Area;
} EFI_GLOBAL_NVS_AREA_PROTOCOL;

#endif
