;
; This file contains an 'Intel Peripheral Driver' and is
; licensed for Intel CPUs and chipsets under the terms of your
; license agreement with Intel or your vendor.  This file may
; be modified by the user, subject to additional terms of the
; license agreement
;
;------------------------------------------------------------------------------
;
; Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>
; This software and associated documentation (if any) is furnished
; under a license and may only be used or copied in accordance
; with the terms of the license. Except as permitted by such
; license, no part of this software or documentation may be
; reproduced, stored in a retrieval system, or transmitted in any
; form or by any means without the express written consent of
; Intel Corporation.
;
; Module Name:
;
;  IbblSramEarlyBoardInit.nasm
;
; Abstract:
;
;  This is the code that will be called before FSP TempRamInit API
;
;------------------------------------------------------------------------------

SECTION .text

global  ASM_PFX(EarlyBoardInit)
ASM_PFX(EarlyBoardInit):
        ;
        ; This hook is called before FSP TempRamInit API call
        ; ESI, EDI need to be preserved
        ; ESP contains return address
        ;
        jmp     esp        

