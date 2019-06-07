/** @file

  Copyright (c) 2014, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef _UFS_BLOCK_IO_LIB_INTERNAL_H_
#define _UFS_BLOCK_IO_LIB_INTERNAL_H_

#include <PiPei.h>

#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/IoLib.h>
#include <Library/TimerLib.h>
#include <IndustryStandard/Scsi.h>
#include <Library/UfsBlockIoLib.h>
#include <Ppi/BlockIo.h>

#include "UfsHci.h"
#include "UfsPciHc.h"
#include "UfsHcMem.h"

#define UFS_PEIM_HC_SIG             SIGNATURE_32 ('U', 'F', 'S', 'H')
#define UFS_PEIM_MAX_LUNS           8

typedef struct {
  ///
  /// A type of interface that the device being referenced by DeviceIndex is
  /// attached to. This field re-uses Messaging Device Path Node sub-type values
  /// as defined by Section 9.3.5 Messaging Device Path of UEFI Specification.
  /// When more than one sub-type is associated with the interface, sub-type with
  /// the smallest number must be used.
  ///
  UINT8                      InterfaceType;
  ///
  /// A flag that indicates if media is removable.
  ///
  BOOLEAN                    RemovableMedia;
  ///
  /// A flag that indicates if media is present. This flag is always set for
  /// non-removable media devices.
  ///
  BOOLEAN                    MediaPresent;
  ///
  /// A flag that indicates if media is read-only.
  ///
  BOOLEAN                    ReadOnly;
  ///
  /// The size of a logical block in bytes.
  ///
  UINT32                     BlockSize;
  ///
  /// The last logical block that the device supports.
  ///
  EFI_PEI_LBA                LastBlock;
} EFI_PEI_BLOCK_IO2_MEDIA;

typedef struct {
  UINT8    Lun[UFS_PEIM_MAX_LUNS];
  UINT16   BitMask: 12;             // Bit 0~7 is for common luns. Bit 8~11 is reserved for those well known luns
  UINT16   Rsvd: 4;
} UFS_PEIM_EXPOSED_LUNS;

typedef struct {
  ///
  /// The timeout, in 100 ns units, to use for the execution of this SCSI
  /// Request Packet. A Timeout value of 0 means that this function
  /// will wait indefinitely for the SCSI Request Packet to execute. If
  /// Timeout is greater than zero, then this function will return
  /// EFI_TIMEOUT if the time required to execute the SCSI
  /// Request Packet is greater than Timeout.
  ///
  UINT64 Timeout;
  ///
  /// A pointer to the data buffer to transfer between the SCSI
  /// controller and the SCSI device for read and bidirectional commands.
  ///
  VOID   *InDataBuffer;
  ///
  /// A pointer to the data buffer to transfer between the SCSI
  /// controller and the SCSI device for write or bidirectional commands.
  ///
  VOID   *OutDataBuffer;
  ///
  /// A pointer to the sense data that was generated by the execution of
  /// the SCSI Request Packet.
  ///
  VOID   *SenseData;
  ///
  /// A pointer to buffer that contains the Command Data Block to
  /// send to the SCSI device specified by Target and Lun.
  ///
  VOID   *Cdb;
  ///
  /// On Input, the size, in bytes, of InDataBuffer. On output, the
  /// number of bytes transferred between the SCSI controller and the SCSI device.
  ///
  UINT32 InTransferLength;
  ///
  /// On Input, the size, in bytes of OutDataBuffer. On Output, the
  /// Number of bytes transferred between SCSI Controller and the SCSI device.
  ///
  UINT32 OutTransferLength;
  ///
  /// The length, in bytes, of the buffer Cdb. The standard values are 6,
  /// 10, 12, and 16, but other values are possible if a variable length CDB is used.
  ///
  UINT8  CdbLength;
  ///
  /// The direction of the data transfer. 0 for reads, 1 for writes. A
  /// value of 2 is Reserved for Bi-Directional SCSI commands.
  ///
  UINT8  DataDirection;
  ///
  /// On input, the length in bytes of the SenseData buffer. On
  /// output, the number of bytes written to the SenseData buffer.
  ///
  UINT8  SenseDataLength;
} UFS_SCSI_REQUEST_PACKET;

typedef struct _UFS_PEIM_HC_PRIVATE_DATA {
  UINT32                            Signature;
  EFI_HANDLE                        Controller;

  UFS_PEIM_MEM_POOL                 *Pool;

  EFI_PEI_BLOCK_IO2_MEDIA           Media[UFS_PEIM_MAX_LUNS];

  UINTN                             UfsHcBase;
  UINT32                            Capabilities;

  UINT8                             TaskTag;

  VOID                              *UtpTrlBase;
  UINT8                             Nutrs;
  VOID                              *UtpTmrlBase;
  UINT8                             Nutmrs;

  UFS_PEIM_EXPOSED_LUNS             Luns;
} UFS_PEIM_HC_PRIVATE_DATA;

#define UFS_TIMEOUT                 MultU64x32((UINT64)(3), 1000000)

#define ROUNDUP8(x) (((x) % 8 == 0) ? (x) : ((x) / 8 + 1) * 8)

#define IS_ALIGNED(addr, size)      (((UINTN) (addr) & (size - 1)) == 0)

#define UFS_SCSI_OP_LENGTH_SIX      0x6
#define UFS_SCSI_OP_LENGTH_TEN      0xa
#define UFS_SCSI_OP_LENGTH_SIXTEEN  0x10

typedef struct _UFS_DEVICE_MANAGEMENT_REQUEST_PACKET {
  UINT64                            Timeout;
  VOID                              *InDataBuffer;
  VOID                              *OutDataBuffer;
  UINT8                             Opcode;
  UINT8                             DescId;
  UINT8                             Index;
  UINT8                             Selector;
  UINT32                            InTransferLength;
  UINT32                            OutTransferLength;
  UINT8                             DataDirection;
  UINT8                             Ocs;
} UFS_DEVICE_MANAGEMENT_REQUEST_PACKET;

/**
  Sends a UFS-supported SCSI Request Packet to a UFS device that is attached to the UFS host controller.

  @param[in]      Private       The pointer to the UFS_PEIM_HC_PRIVATE_DATA data structure.
  @param[in]      Lun           The LUN of the UFS device to send the SCSI Request Packet.
  @param[in, out] Packet        A pointer to the SCSI Request Packet to send to a specified Lun of the
                                UFS device.

  @retval EFI_SUCCESS           The SCSI Request Packet was sent by the host. For bi-directional
                                commands, InTransferLength bytes were transferred from
                                InDataBuffer. For write and bi-directional commands,
                                OutTransferLength bytes were transferred by
                                OutDataBuffer.
  @retval EFI_DEVICE_ERROR      A device error occurred while attempting to send the SCSI Request
                                Packet.
  @retval EFI_OUT_OF_RESOURCES  The resource for transfer is not available.
  @retval EFI_TIMEOUT           A timeout occurred while waiting for the SCSI Request Packet to execute.

**/
EFI_STATUS
UfsExecScsiCmds (
  IN     UFS_PEIM_HC_PRIVATE_DATA      *Private,
  IN     UINT8                         Lun,
  IN OUT UFS_SCSI_REQUEST_PACKET       *Packet
  );

/**
  Initialize the UFS host controller.

  @param[in] Private                 The pointer to the UFS_PEIM_HC_PRIVATE_DATA data structure.

  @retval EFI_SUCCESS                The Ufs Host Controller is initialized successfully.
  @retval Others                     A device error occurred while initializing the controller.

**/
EFI_STATUS
UfsControllerInit (
  IN  UFS_PEIM_HC_PRIVATE_DATA       *Private
  );

/**
  Stop the UFS host controller.

  @param[in] Private                 The pointer to the UFS_PEIM_HC_PRIVATE_DATA data structure.

  @retval EFI_SUCCESS                The Ufs Host Controller is stopped successfully.
  @retval Others                     A device error occurred while stopping the controller.

**/
EFI_STATUS
UfsControllerStop (
  IN  UFS_PEIM_HC_PRIVATE_DATA       *Private
  );

/**
  Set specified flag to 1 on a UFS device.

  @param[in]  Private           The pointer to the UFS_PEIM_HC_PRIVATE_DATA data structure.
  @param[in]  FlagId            The ID of flag to be set.

  @retval EFI_SUCCESS           The flag was set successfully.
  @retval EFI_DEVICE_ERROR      A device error occurred while attempting to set the flag.
  @retval EFI_TIMEOUT           A timeout occurred while waiting for the completion of setting the flag.

**/
EFI_STATUS
UfsSetFlag (
  IN  UFS_PEIM_HC_PRIVATE_DATA     *Private,
  IN  UINT8                        FlagId
  );

/**
  Read or write specified device descriptor of a UFS device.

  @param[in]      Private       The pointer to the UFS_PEIM_HC_PRIVATE_DATA data structure.
  @param[in]      Read          The boolean variable to show r/w direction.
  @param[in]      DescId        The ID of device descriptor.
  @param[in]      Index         The Index of device descriptor.
  @param[in]      Selector      The Selector of device descriptor.
  @param[in, out] Descriptor    The buffer of device descriptor to be read or written.
  @param[in]      DescSize      The size of device descriptor buffer.

  @retval EFI_SUCCESS           The device descriptor was read/written successfully.
  @retval EFI_DEVICE_ERROR      A device error occurred while attempting to r/w the device descriptor.
  @retval EFI_TIMEOUT           A timeout occurred while waiting for the completion of r/w the device descriptor.

**/
EFI_STATUS
UfsRwDeviceDesc (
  IN     UFS_PEIM_HC_PRIVATE_DATA     *Private,
  IN     BOOLEAN                      Read,
  IN     UINT8                        DescId,
  IN     UINT8                        Index,
  IN     UINT8                        Selector,
  IN OUT VOID                         *Descriptor,
  IN     UINT32                       DescSize
  );

/**
  Sends NOP IN cmd to a UFS device for initialization process request.
  For more details, please refer to UFS 2.0 spec Figure 13.3.

  @param[in]  Private           The pointer to the UFS_PEIM_HC_PRIVATE_DATA data structure.

  @retval EFI_SUCCESS           The NOP IN command was sent by the host. The NOP OUT response was
                                received successfully.
  @retval EFI_DEVICE_ERROR      A device error occurred while attempting to execute NOP IN command.
  @retval EFI_OUT_OF_RESOURCES  The resource for transfer is not available.
  @retval EFI_TIMEOUT           A timeout occurred while waiting for the NOP IN command to execute.

**/
EFI_STATUS
UfsExecNopCmds (
  IN  UFS_PEIM_HC_PRIVATE_DATA       *Private
  );

/**
  Initialize the memory management pool for the host controller.

  @param  Private               The Ufs Peim driver private data.

  @retval EFI_SUCCESS           The memory pool is initialized.
  @retval Others                Fail to init the memory pool.

**/
EFI_STATUS
UfsInitMemPool (
  IN  UFS_PEIM_HC_PRIVATE_DATA      *Private
  );

/**
  Allocate some memory from the host controller's memory pool
  which can be used to communicate with host controller.

  @param  Pool      The host controller's memory pool.
  @param  Size      Size of the memory to allocate.

  @return The allocated memory or NULL.

**/
VOID *
UfsAllocateMem (
  IN  UFS_PEIM_MEM_POOL        *Pool,
  IN  UINTN                    Size
  );

/**
  Free the allocated memory back to the memory pool.

  @param  Pool           The memory pool of the host controller.
  @param  Mem            The memory to free.
  @param  Size           The size of the memory to free.

**/
VOID
UfsFreeMem (
  IN UFS_PEIM_MEM_POOL    *Pool,
  IN VOID                 *Mem,
  IN UINTN                Size
  );

#endif
