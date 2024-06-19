//==========================================================================================================
// @file	:	NGF_Rectangle
// @author	:	NAGISA
// @data	:	2022/12/27 16:28:03
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGF_Rectangle
#define __HEAD_NGF_Rectangle

#include "NGF/NGF_Defined.h"
#include "NGF/NGF_Math.h"
#include "NGF/NGF_Vector_import.h"

NGF_BEGIN

class NGF_Rectangle {
public:
	NGF_Rectangle(FLOAT x = 0.0f, FLOAT y = 0.0f, FLOAT width = 0.0f, FLOAT height = 0.0f) :x(x), y(y), width(width), height(height) {}
	NGF_Rectangle(const NGF_Vector2D<FLOAT32>& position, const NGF_Vector2D<FLOAT32>& size);

	NGF_Rectangle& operator+=(const NGF_Rectangle& rect);
	NGF_Rectangle& operator-=(const NGF_Rectangle& rect);

	NGF_Rectangle operator+(const NGF_Rectangle& rect)const;
	NGF_Rectangle operator-(const NGF_Rectangle& rect)const;

	BOOL operator==(const NGF_Rectangle& rect)const { return (x == rect.x) && (y == rect.y) && (width == rect.width) && (height == rect.height); }
	BOOL operator!=(const NGF_Rectangle& rect)const { return !(*this == rect); }

	operator BOOL() const{ return width && height; }
	BOOL Empty() const { return width && height; }

	FLOAT GetTop() const { return height > 0 ? y : y + height; }
	FLOAT GetBottom() const { return height > 0 ? y + height : y; }
	FLOAT GetRight() const { return width > 0 ? x + width : x; }
	FLOAT GetLeft() const { return width > 0 ? x : x + width; }

	
	VOID Set(FLOAT x_, FLOAT y_, FLOAT width_, FLOAT height_) {
		x = x_;
		y = y_;
		width = width_;
		height = height_;
	}
	VOID Set(const NGF_Rectangle& other) {
		x = other.x;
		y = other.y;
		width = other.width;
		height = other.height;
	}
	VOID SetZero() {
		x = y = 0.0f;
		width = height = 0.0f;
	}
	VOID Normalize() {
		if (width < 0) {
			x += width;
			width = -width;
		}
		if (height < 0) {
			y += height;
			height = -height;
		}
	}


public:
	FLOAT x, y;
	FLOAT width, height;
};

NGF_END


#endif // !__HEAD_NGF_Rectangle
