//==========================================================================================================
// @file	:	NGF_Matrix
// @author	:	NAGISA
// @data	:	2023/1/7 0:06:10
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGF_Matrix
#define __HEAD_NGF_Matrix

#include "NGF/NGF_Defined.h"
#include "NGF/NGF_Object.h"
#include "NGF/NGF_Math.h"



NGF_BEGIN

class NGF_Vector2D;

NGF_INTERNAL_BEGIN


NGF_END

typedef class NGF_Matrix :virtual public NGF_Object {

public:
	NGF_Matrix(
		FLOAT a = 1.0f,
		FLOAT b = 0.0f,
		FLOAT c = 0.0f,
		FLOAT d = 1.0f,
		FLOAT tx = 0.0f,
		FLOAT ty = 0.0f
	) :
		a(a),
		b(b),
		c(c),
		d(d),
		tx(tx),
		ty(ty)
	{}

	NGF_Matrix& operator +=(const NGF_Matrix& other);
	NGF_Matrix operator+(const NGF_Matrix& other)const;

	NGF_Vector2D DeltaTransformPoint(const NGF_Vector2D& point)const;
	NGF_Vector2D TransformPoint(const NGF_Vector2D& point)const;

	VOID Identity() {
		a = d = 1.0f;
		b = c = 0.0f;
		tx = ty = 0.0f;
	}
	VOID Invert();

	VOID Rotate(FLOAT angle) {
		a = d = cos(angle);
		b = sin(angle);
		c = -b;
	}
	VOID Scale(FLOAT sx, FLOAT sy) {
		a = sx;
		d = sy;
	}
	VOID Translate(FLOAT dx, FLOAT dy) {
		tx = dx;
		ty = dy;
	}
	VOID Tilt(FLOAT skewx, FLOAT skewy) {
		b = tan(skewy);
		c = tan(skewx);
	}

	VOID Set(
		FLOAT a,
		FLOAT b,
		FLOAT c,
		FLOAT d,
		FLOAT tx,
		FLOAT ty
	) {
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
		this->tx = tx;
		this->ty = ty;
	}
	VOID Set(const NGF_Matrix& other) {
		a = other.a;
		b = other.b;
		c = other.c;
		d = other.d;
		tx = other.tx;
		ty = other.ty;
	}

	VOID CreateBox(
		FLOAT scaleX,
		FLOAT scaleY,
		FLOAT angle = 0.0f,
		FLOAT tx = 0.0f,
		FLOAT ty = 0.0f
	) {
		Identity();
		Rotate(angle);
		Scale(scaleX, scaleY);
		Translate(tx, ty);
	}
	VOID CreateGradientBox(
		FLOAT width,
		FLOAT height,
		FLOAT angle = 0.0f,
		FLOAT tx = 0.0f,
		FLOAT ty = 0.0f
	);

	NGF_String ToString()const override;
private:

public:
	FLOAT a;
	FLOAT b;
	FLOAT c;
	FLOAT d;
	FLOAT tx;
	FLOAT ty;

private:
	constexpr static const FLOAT u = 0.0f;
	constexpr static const FLOAT v = 0.0f;
	constexpr static const FLOAT w = 1.0f;

} *NGF_PMatrix;


NGF_END

#endif // !__HEAD_NGF_Matrix
