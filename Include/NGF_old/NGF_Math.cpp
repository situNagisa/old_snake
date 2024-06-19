//==========================================================================================================
// @file	:	NGF_Math
// @author	:	NAGISA
// @data	:	2022/12/24 14:53:27
// @brief	:	
//==========================================================================================================


#include "NGF/NGF_Math.h"
#include "NGF/NGF_Utils.h"

NGF_BEGIN

INT32 NGF_NumberBits(DOUBLE number, _Out_opt_ PINT pintBit, _Out_opt_ PINT ppointBit) {
	number = NGF_Abs(number);
	UINT64 _int = static_cast<INT64>(number);
	INT bits = 1;// _int ? 1 : 0; // 不包括0
	INT intBit = 0;
	INT pointBit = 0;
	DOUBLE point = number - _int;

	//检测数字是否合法
	Assert_Dynamic(point < 1, TEXT("传入整数溢出！"));

	//整数部分
	if (pintBit != nullptr)*pintBit = intBit;
	if (ppointBit != nullptr)*ppointBit = pointBit;
	while ((_int /= 10) > 0)bits++;
	intBit = bits;
	if (_int == number)return bits;

	//小数部分
	while (point > 0) {
		point *= 10;
		_int = static_cast<INT>(point);
		point -= _int;
		_int = 0;
		pointBit++;
		bits++;
		if (pointBit >= 16)break;
	}
	if (pintBit != nullptr)*pintBit = intBit;
	if (ppointBit != nullptr)*ppointBit = pointBit;

	return bits;
}

NGF_END