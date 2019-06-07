/** @file
Header file for extra base routines

Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef _EXTRA_BASE_LIB_H_
#define _EXTRA_BASE_LIB_H_

/**
  Flush a range of  cache lines in the cache coherency domain of the calling
  CPU.

  Flushes the cache lines specified by Address and Length.  If Address is not aligned
  on a cache line boundary, then entire cache line containing Address is flushed.
  If Address + Length is not aligned on a cache line boundary, then the entire cache
  line containing Address + Length - 1 is flushed.  This function may choose to flush
  the entire cache if that is more efficient than flushing the specified range.  If
  Length is 0, the no cache lines are flushed.

  @param[in]  Address The base address of the lines to invalidate.

  @param[in]  Length  The number of bytes to invalidate from the cache.


**/
VOID
EFIAPI
AsmFlushCacheRange (
  IN      VOID                      *Address,
  IN      UINTN                     Length
  );

#endif
