/**************************************************************************;
;*                                                                        *;
;*                                                                        *;
;*    Intel Corporation - ACPI Reference Code for the Sandy Bridge        *;
;*    Family of Customer Reference Boards.                                *;
;*                                                                        *;
;*                                                                        *;
;*    Copyright (c) 2012  - 2015, Intel Corporation. All rights reserved    *;
;
; This program and the accompanying materials are licensed and made available under
; the terms and conditions of the BSD License that accompanies this distribution.
; The full text of the license may be found at
; http://opensource.org/licenses/bsd-license.php.
;
; THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
; WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
;
;*                                                                        *;
;*                                                                        *;
;**************************************************************************/

DefinitionBlock (
  "DSDT.aml",
  "DSDT",
  0x02,  // DSDT revision.
  "OEMID", // OEM ID (6 byte string)
  "APL-SOC", // OEM table ID  (8 byte string)
  0x0 // OEM version of DSDT table (4 byte Integer)
)
{
  
  Name(\_S0, Package(4) {0x0,0x0,0,0}) // mandatory System state
  Name(\_S1, Package(4) {0x1,0x0,0,0})
  Name(\_S3, Package(4) {0x5,0x0,0,0})
  Name(\_S4, Package(4) {0x6,0x0,0,0})
  Name(\_S5, Package(4) {0x7,0x0,0,0}) // mandatory System state

  Method(PTS, 1)
  {    
  }
  
  Method(WAK, 1)
  {
  }
  
}
