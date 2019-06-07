/** @file

  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php.

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

/* 
//  Purpose:
//     Intel(R) Integrated Performance Primitives. Cryptography Primitives.
//     Unsigned internal BNU32 misc functionality
// 
//  Contents:
//     cpNLZ_BNU32()
//     cpNTZ_BNU32()
// 
//     cpLSL_BNU32()
//     cpLSR_BNU32()
// 
//     cpFromOctStr_BNU32()
//     cpToOctStr_BNU32()
// 
// 
*/

#include "owncp.h"
#include "pcpbnuimpl.h"
#include "pcpbnumisc.h"
#include "pcpbnu32misc.h"


/*
// number of leading zeros
*/
cpSize cpNLZ_BNU32(Ipp32u x)
{
   cpSize nlz = BITSIZE(Ipp32u);
   if(x) {
      nlz = 0;
      if( 0==(x & 0xFFFF0000) ) { nlz +=16; x<<=16; }
      if( 0==(x & 0xFF000000) ) { nlz += 8; x<<= 8; }
      if( 0==(x & 0xF0000000) ) { nlz += 4; x<<= 4; }
      if( 0==(x & 0xC0000000) ) { nlz += 2; x<<= 2; }
      if( 0==(x & 0x80000000) ) { nlz++; }
   }
   return nlz;
}

/*
// Convert Oct String into BNU representation
//
// Returns length of BNU in Ipp32u chunks
*/
cpSize cpFromOctStr_BNU32(Ipp32u* pBNU, const Ipp8u* pOctStr, cpSize strLen)
{
   cpSize bnuSize=0;
   *pBNU = 0;

   /* start from the end of string */
   for(; strLen>=4; bnuSize++,strLen-=4) {
      /* pack 4 bytes into single Ipp32u value*/
      *pBNU++ = ( pOctStr[strLen-4]<<(8*3) )
               +( pOctStr[strLen-3]<<(8*2) )
               +( pOctStr[strLen-2]<<(8*1) )
               +  pOctStr[strLen-1];
   }

   /* convert the beginning of the string */
   if(strLen) {
      Ipp32u x;
      for(x=0; strLen>0; strLen--) {
         Ipp32u d = *pOctStr++;
         x = x*256 + d;
       }
       *pBNU++ = x;
       bnuSize++;
   }

   return bnuSize? bnuSize : 1;
}


/*
// Convert BNU into Octet String representation
//
// Returns strLen or 0 if no success
*/
cpSize cpToOctStr_BNU32(Ipp8u* pStr, cpSize strLen, const Ipp32u* pBNU, cpSize bnuSize)
{
   FIX_BNU(pBNU, bnuSize);
   {
      int bnuBitSize = BITSIZE_BNU32(pBNU, bnuSize);
      if(bnuBitSize <= strLen*BYTESIZE) {
         Ipp32u x = pBNU[bnuSize-1];
#ifdef _SLIMBOOT_OPT
         SetMem (pStr, strLen, 0);
#else
         ZEXPAND_BNU(pStr, 0, strLen);
#endif
         pStr += strLen - BITS2WORD8_SIZE(bnuBitSize);

         if(x) {
            int nb;
            for(nb=cpNLZ_BNU32(x)/BYTESIZE; nb<4; nb++)
               *pStr++ = EBYTE(x,3-nb);

            for(--bnuSize; bnuSize>0; bnuSize--) {
               x = pBNU[bnuSize-1];
               *pStr++ = EBYTE(x,3);
               *pStr++ = EBYTE(x,2);
               *pStr++ = EBYTE(x,1);
               *pStr++ = EBYTE(x,0);
            }
         }
         return strLen;
      }
      else
         return 0;
   }
}
