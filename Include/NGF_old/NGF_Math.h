//==========================================================================================================
// @file	:	NGF_Math
// @author	:	NAGISA
// @data	:	2022/12/24 14:52:50
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGF_Math
#define __HEAD_NGF_Math

#include "NGF/NGF_Defined.h"




#define	NGF_MaxFloat	FLT_MAX
#define	NGF_Epsilon		FLT_EPSILON
#define NGF_PI			3.14159265359f

//平方根宏
#define	NGF_Sqrt(x)	sqrtf(x)

//对于任意不同时等于0的实参数x和y，
//atan2(y,x)所表达的意思是坐标原点为起点，
//指向(y,x)的射线在坐标平面上与x轴正方向之间的角的角度度
//参照 http://zh.wikipedia.org/wiki/Atan2
#define	NGF_Atan2(y, x)	atan2f(y, x)

#define NGF_InRange(value,low,high) ((value) >= (low) && (value) <= (high))

NGF_BEGIN

/**************************************************************************
* 功能描述：用来确保一个浮点数不是一个NaN或无穷大
* 参数说明： x :数值
* 返 回 值： true ：有效
			 false: 无效
**************************************************************************/
inline bool NGF_IsValid(FLOAT x)
{
	if (x != x)
	{
		// NaN.
		return false;
	}

	constexpr FLOAT infinity = std::numeric_limits<FLOAT>::infinity();
	return -infinity < x&& x < infinity;
}

/**************************************************************************
* 功能描述：一个近似且快速的平方根倒数算法[x^ (-1/2) ]
*			可以参照 http://zh.wikipedia.org/wiki/平方根倒数速算法
*			或 http://en.wikipedia.org/wiki/Fast_inverse_square_root
* 参数说明： x :数值
* 返 回 值： 平方根倒数
**************************************************************************/
inline FLOAT NGF_InvSqrt(FLOAT x)
{
	union
	{
		FLOAT x;
		INT32 i;
	} convert;

	convert.x = x;
	FLOAT xhalf = 0.5f * x;
	convert.i = 0x5f3759df - (convert.i >> 1);
	x = convert.x;
	x = x * (1.5f - xhalf * x * x);                  //第一次牛顿迭代
	return x;
}

template <typename T>
inline T NGF_Abs(T a) { return a > T(0) ? a : -a; }

template <typename T>
inline T NGF_Min(T a, T b) { return a < b ? a : b; }

template <typename T>
inline T NGF_Max(T a, T b) { return a > b ? a : b; }

template <typename T>
inline T NGF_Clamp(T a, T low, T high) { return NGF_Max(low, NGF_Min(a, high)); }

template<typename T> 
inline void NGF_Swap(T& a, T& b) {
	T tmp = a;
	a = b;
	b = tmp;
}
template<> 
inline void NGF_Swap(INT& a, INT& b) {
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}

/// "Next Largest Power of 2
/// Given a binary integer value x, the next largest power of 2 can be computed by a SWAR algorithm
/// that recursively "folds" the upper bits into the lower bits. This process yields a bit vector with
/// the same most significant 1 as x, but all 1's below it. Adding 1 to that value yields the next
/// largest power of 2. For a 32-bit value:"
inline UINT32 NGF_NextPowerOfTwo(UINT32 x)
{
	x |= (x >> 1);
	x |= (x >> 2);
	x |= (x >> 4);
	x |= (x >> 8);
	x |= (x >> 16);
	return x + 1;
}

inline bool NGF_IsPowerOfTwo(UINT32 x)
{
	bool result = x > 0 && (x & (x - 1)) == 0;
	return result;
}

/**
* 获取数字的位数
*
* @param number 传入的数字，整数部分不超过19位，小数部分不超过16位
* @param pintBit 整数位数指针（可为空）
* @param ppointBit 小数位数指针（可为空）
*
* @return 总位数
*
*/
INT32 NGF_NumberBits(DOUBLE number, _Out_opt_ PINT pintBit = nullptr, _Out_opt_ PINT ppointBit = nullptr);


NGF_END

#endif // !__HEAD_NGF_Math
