/** @file

  Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php.

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef _REG_ACCESS_H_

#include <Library/IoLib.h>
#include <Library/PciLib.h>
#include <PlatformBase.h>
#include <BlCommon.h>
#include <PchLimits.h>
#include <Register/PchRegsGpio.h>
#include <Register/PchRegsLpc.h>
#include <Register/PchRegsPcr.h>
#include <Register/PchRegsSerialIo.h>
#include <Register/PchRegsPmc.h>
#include <Register/PchRegsP2sb.h>
#include <Register/PchRegsScc.h>
#include <Register/PchRegsSpi.h>
#include <IndustryStandard/Pci.h>

#define DEFAULT_PCI_BUS_NUMBER_PCH  0

#define MsgBus32Read     (PortId, Register)  \
        MmioRead32  (SOC_SIDE_BAND_BASE + ((PortId) << 16) + Register)

#define MsgBus32Write    (PortId, Register, Data)  \
        MmioWrite32 (SOC_SIDE_BAND_BASE + ((PortId) << 16) + Register, Data)
#define MsgBus32AndThenOr(PortId, Register, AndData, OrData ) \
        MmioAndThenOr32 (SOC_SIDE_BAND_BASE + ((PortId) << 16) + Register, AndData, OrData) 

#define MmPciBase(Bus, Device, Function) \
  ( (UINTN)PcdGet64(PcdPciExpressBaseAddress) + \
    (UINTN)(Bus << 20) +    \
    (UINTN)(Device << 15) + \
    (UINTN)(Function << 12) \
  )
  
#endif