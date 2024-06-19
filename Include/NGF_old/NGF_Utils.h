//==========================================================================================================
// @file	:	NGF_Utils
// @author	:	NAGISA
// @data	:	2023/1/6 16:56:15
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGF_Utils
#define __HEAD_NGF_Utils

#include "NGF/NGF_Defined.h"
#include <source_location>



NGF_BEGIN

class NGF_Object;
class NGF_String;

enum class NGF_BIT : BYTE
{
	BIT_1 = 0x01,
	BIT_2 = 0x02,
	BIT_3 = 0x04,
	BIT_4 = 0x08,
	BIT_5 = 0x10,
	BIT_6 = 0x20,
	BIT_7 = 0x40,
	BIT_8 = 0x80
};

BOOL Assert(BOOL expression, LPCTSTR text, const std::source_location& location = std::source_location::current());

VOID Trace(const NGF_String& message);
VOID Trace(const NGF_Object& message);
VOID Trace(LPCTSTR message);

VOID Trace(const auto& message) {
	if constexpr (typeid(message) == typeid(LPCTSTR)) {
		Trace(message);
	}
	else {
		Trace(NGF_String(message));
	}
}

template<typename ...Args>
VOID Trace(Args... args) {
	(Trace(args), ...);
};

inline VOID NGF_SetFlag(std::integral auto& flag,enum class NGF_BIT bit, BOOL boolean, UINT32 offsetByte = 0) {
	UINT64 offBit = static_cast<UINT64>(bit);
	offBit <<= offsetByte * sizeof(NGF_BIT);
	boolean ? (flag |= offBit) : (flag &= ~offBit);
}

inline BOOL NGF_IsFlag(std::integral auto flag, enum class NGF_BIT bit, UINT32 offsetByte = 0) {
	UINT64 offBit = static_cast<UINT64>(bit);
	offBit <<= offsetByte * sizeof(NGF_BIT);
	return (flag & offBit) == (offBit);
}

#ifdef _DEBUG

inline BOOL Assert_Dynamic(BOOL expression, LPCTSTR text, const std::source_location& location = std::source_location::current()) {
	return nagisa::Assert(expression, text, location);
}
inline VOID Assert_Static(BOOL expression, LPCTSTR text, const std::source_location& location = std::source_location::current()) {
	nagisa::Assert(expression, text, location);
}

#else // _DEBUG

inline constexpr BOOL Assert_Dynamic(BOOL expression, LPCTSTR text) {
	return TRUE;
}
inline constexpr VOID Assert_Static(BOOL expression, LPCTSTR text) {

}
#endif // _DEBUG

NGF_END



#endif // !__HEAD_NGF_Utils
