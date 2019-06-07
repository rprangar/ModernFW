/*++
  This file contains an 'Intel Peripheral Driver' and uniquely  
  identified as "Intel Reference Module" and is                 
  licensed for Intel CPUs and chipsets under the terms of your  
  license agreement with Intel or your vendor.  This file may   
  be modified by the user, subject to additional terms of the   
  license agreement                                             
--*/

/*++

Copyright (c)  1999 - 2010 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.


Module Name:

  HostBus.asl

---*/
    
//
// BUS, I/O, and MMIO resources
//
Method(_CRS,0,Serialized) {        
  Return(RES0)       
}
      
Name( RES0,ResourceTemplate() {
  WORDBusNumber (          // Bus number resource (0); the bridge produces bus numbers for its subsequent buses
          ResourceProducer,      // bit 0 of general flags is 1
          MinFixed,              // Range is fixed
          MaxFixed,              // Range is fixed
          PosDecode,             // PosDecode
          0x0000,                // Granularity
          0x0000,                // Min
          0x00FF,                // Max
          0x0000,                // Translation
          0x0100                 // Range Length = Max-Min+1
          )

  WORDIO (                 // Consumed-and-produced resource 
          ResourceProducer,      // bit 0 of general flags is 0
          MinFixed,              // Range is fixed
          MaxFixed,              // Range is fixed
          PosDecode,
          EntireRange,
          0x0000,                // Granularity
          0x0000,                // Min
          0x0CF7,                // Max
          0x0000,                // Translation
          0x0CF8                 // Range Length
          )

  IO (Decode16, 0xCF8, 0xCF8, 0x01, 0x08)       //Consumed resource (0xCF8-0xCFF)

  WORDIO (                 // Consumed-and-produced resource (all I/O above CFF)
          ResourceProducer,      // bit 0 of general flags is 0
          MinFixed,              // Range is fixed
          MaxFixed,              // Range is fixed
          PosDecode,
          EntireRange,
          0x0000,                // Granularity
          0x0D00,                // Min
          0xFFFF,                // Max
          0x0000,                // Translation
          0xF300                 // Range Length
          )

  DWORDMEMORY (            // Descriptor for legacy VGA video RAM
          ResourceProducer,      // bit 0 of general flags is 0
          PosDecode,
          MinFixed,              // Range is fixed
          MaxFixed,              // Range is fixed
          Cacheable,
          ReadWrite,
          0x00000000,            // Granularity
          0x000A0000,            // Min
          0x000BFFFF,            // Max
          0x00000000,            // Translation
          0x00020000             // Range Length
          )

  DWORDMEMORY (            // Descriptor for legacy OptionRom
          ResourceProducer,      // bit 0 of general flags is 0
          PosDecode,
          MinFixed,              // Range is fixed
          MaxFixed,              // Range is fixed
          Cacheable,
          ReadWrite,
          0x00000000,            // Granularity
          0x000C0000,            // Min
          0x000DFFFF,            // Max
          0x00000000,            // Translation
          0x00020000             // Range Length
          )

  DWORDMEMORY (            // Descriptor for BIOS Area
          ResourceProducer,      // bit 0 of general flags is 0
          PosDecode,
          MinFixed,              // Range is fixed
          MaxFixed,              // Range is fixed
          Cacheable,
          ReadWrite,
          0x00000000,            // Granularity
          0x000E0000,            // Min
          0x000FFFFF,            // Max
          0x00000000,            // Translation
          0x00020000             // Range Length
          )

  DWORDMEMORY (            // Descriptor for PCI MMIO
          ResourceProducer,      // bit 0 of general flags is 0
          PosDecode,
          MinFixed,              // Range is fixed
          MaxFixed,              // Range is fixed
          NonCacheable,
          ReadWrite,
          0x00000000,            // Granularity
          0x80000000,            // Min
          0xDFFFFFFF,            // Max
          0x00000000,            // Translation
          0x60000000             // Range Length
          ,,,
          PM01
          )

  DWORDMEMORY (            // Descriptor for TPM
          ResourceProducer,      // bit 0 of general flags is 0
          PosDecode,
          MinFixed,              // Range is fixed
          MaxFixed,              // Range is fixed
          Cacheable,
          ReadWrite,
          0x00000000,            // Granularity
          0xFED40000,            // Min
          0xFED40FFF,            // Max
          0x00000000,            // Translation
          0x1000             // Range Length
	        ,,,
	        TPMR
          )
  
})

// Modify the _OSC method according to osc.asi from BIOS

Method (_OSC, 4)
{
	/* Check for proper GUID */
	If (LEqual (Arg0, ToUUID ("33DB4D5B-1FF7-401C-9657-7441C03DD766")))
	{
		/* Let OS control everything */
		Return (Arg3)
	}
	Else
	{
		/* Unrecognized UUID */
		CreateDWordField (Arg3, 0, CDW1)
		Or (CDW1, 4, CDW1)
		Return (Arg3)
	}
}

