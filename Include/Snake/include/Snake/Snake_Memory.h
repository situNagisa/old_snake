//==========================================================================================================
// @file	:	Snake_Memory
// @author	:	NAGISA
// @data	:	2023/1/19 12:16:07
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Snake_Memory
#define __HEAD_Snake_Memory

#include "NGS/NGS.h"

USE_NGS_TYPE

template<UnsignedIntegral UINT,BOOL reverseSet = FALSE>
VOID MemorySet(UINT* des, UINT val, UINT16 size) {
    if NGS_CONSTEXPR(reverseSet) {
        for (INT32 i = size - 1; i >= 0; i--)des[i] = val;
    } else {
        for (UINT16 i = 0; i < size; i++)des[i] = val;
    }
}
template<BOOL reverseSet = FALSE>
NGS_INLINE VOID MemorySet(PVOID des, UINT8 val, UINT16 size) {MemorySet<UINT8, reverseSet>(static_cast<UINT8*>(des), val, size);}

template<UnsignedIntegral UINT>
VOID MemoryMove(UINT* from, UINT* to, UINT16 size) {
    if (from < to) {
        for (INT32 i = size - 1; i >= 0; i--) {
            to[i] = from[i];
        }
        return;
    }
    for (UINT16 i = 0; i < size; i++) {
        to[i] = from[i];
    }
}

NGS_INLINE VOID MemoryMove(PVOID from, PVOID to, UINT16 size) {
    MemoryMove<UINT8>(static_cast<UINT8*>(from), static_cast<UINT8*>(to), size);
}

template<UnsignedIntegral UINT>
VOID MemorySwap(UINT* a, UINT* b, UINT16 size) {
    for (UINT16 i = 0; i < size; i++)
    {
        a[i] ^= b[i];
        b[i] ^= a[i];
        a[i] ^= b[i];
    }
}

NGS_INLINE VOID MemorySwap(PVOID a, PVOID b, UINT16 size) {
    MemorySwap<UINT8>(static_cast<UINT8*>(a), static_cast<UINT8*>(b), size);
}

#endif // !__HEAD_Snake_Memory
