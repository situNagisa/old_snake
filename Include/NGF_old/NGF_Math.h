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

//ƽ������
#define	NGF_Sqrt(x)	sqrtf(x)

//�������ⲻͬʱ����0��ʵ����x��y��
//atan2(y,x)��������˼������ԭ��Ϊ��㣬
//ָ��(y,x)������������ƽ������x��������֮��ĽǵĽǶȶ�
//���� http://zh.wikipedia.org/wiki/Atan2
#define	NGF_Atan2(y, x)	atan2f(y, x)

#define NGF_InRange(value,low,high) ((value) >= (low) && (value) <= (high))

NGF_BEGIN

/**************************************************************************
* ��������������ȷ��һ������������һ��NaN�������
* ����˵���� x :��ֵ
* �� �� ֵ�� true ����Ч
			 false: ��Ч
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
* ����������һ�������ҿ��ٵ�ƽ���������㷨[x^ (-1/2) ]
*			���Բ��� http://zh.wikipedia.org/wiki/ƽ�����������㷨
*			�� http://en.wikipedia.org/wiki/Fast_inverse_square_root
* ����˵���� x :��ֵ
* �� �� ֵ�� ƽ��������
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
	x = x * (1.5f - xhalf * x * x);                  //��һ��ţ�ٵ���
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
* ��ȡ���ֵ�λ��
*
* @param number ��������֣��������ֲ�����19λ��С�����ֲ�����16λ
* @param pintBit ����λ��ָ�루��Ϊ�գ�
* @param ppointBit С��λ��ָ�루��Ϊ�գ�
*
* @return ��λ��
*
*/
INT32 NGF_NumberBits(DOUBLE number, _Out_opt_ PINT pintBit = nullptr, _Out_opt_ PINT ppointBit = nullptr);


NGF_END

#endif // !__HEAD_NGF_Math
