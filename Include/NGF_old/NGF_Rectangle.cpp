//==========================================================================================================
// @file	:	NGF_Rectangle
// @author	:	NAGISA
// @data	:	2022/12/27 17:08:01
// @brief	:	
//==========================================================================================================


#include "NGF/NGF_Rectangle.h"
#include "NGF/NGF_Vector.h"


NGF_BEGIN

NGF_Rectangle::NGF_Rectangle(const NGF_Vector2D<FLOAT32>& position, const NGF_Vector2D<FLOAT32>& size) :
	NGF_Rectangle(position.x, position.y, size.x, size.y)
{

}

NGF_Rectangle& NGF_Rectangle::operator+=(const NGF_Rectangle& rect) {
	FLOAT top = NGF_Min(GetTop(), rect.GetTop());
	FLOAT bottom = NGF_Max(GetBottom(), rect.GetBottom());
	FLOAT right = NGF_Max(GetRight(), rect.GetRight());
	FLOAT left = NGF_Min(GetLeft(), rect.GetLeft());
	x = left;
	y = top;
	width = right - left;
	height = bottom - height;

	return *this;
}

NGF_Rectangle& NGF_Rectangle::operator-=(const NGF_Rectangle& rect) {
	FLOAT top = GetTop();
	FLOAT bottom = GetBottom();
	FLOAT right = GetRight();
	FLOAT left = GetLeft();
	FLOAT top2 = rect.GetTop();
	FLOAT bottom2 = rect.GetBottom();
	FLOAT right2 = rect.GetRight();
	FLOAT left2 = rect.GetLeft();

	if (
		!NGF_InRange(left2, left, right)
		|| !NGF_InRange(right2, left, right)
		|| !NGF_InRange(top2, top, bottom)
		|| !NGF_InRange(bottom2, top, bottom)
		) {
		x = y = width = height = 0.0f;
		return *this;
	}
	x = NGF_Min(left, left2);
	y = NGF_Min(top, top2);
	width = NGF_Max(right, right2) - x;
	height = NGF_Max(bottom, bottom2) - y;
	return *this;
}

NGF_Rectangle NGF_Rectangle::operator+(const NGF_Rectangle& rect) const {
	NGF_Rectangle r(*this);
	r += rect;
	return r;
}
NGF_Rectangle NGF_Rectangle::operator-(const NGF_Rectangle& rect)const {
	NGF_Rectangle r(*this);
	r -= rect;
	return r;
}

NGF_END
