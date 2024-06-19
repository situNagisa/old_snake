//==========================================================================================================
// @file	:	NGF_Vector
// @author	:	NAGISA
// @data	:	2022/12/27 13:27:15
// @brief	:	
//==========================================================================================================
#pragma once

#include "NGF/NGF_Vector_import.h"
#ifndef __HEAD_NGF_Vector
#define __HEAD_NGF_Vector

#include "NGF_Defined.h"
#include "NGF_Object.h"
#include "NGF_Math.h"



NGF_BEGIN

class NGF_Vector2D :virtual public NGF_Object
{
public:
	NGF_Vector2D() :
		x(0.0f),
		y(0.0f) {

	}
	NGF_Vector2D(FLOAT x, FLOAT y) :x(x), y(y) {}
	NGF_Vector2D(const NGF_Vector2D& other) {
		x = other.x;
		y = other.y;
	}


	~NGF_Vector2D() = default;

	auto operator<=>(const NGF_Vector2D& other)const  = default;

	NGF_Vector2D& operator=(const NGF_Vector2D& other) {
		x = other.x;
		y = other.y;
		return *this;
	}
	NGF_Vector2D operator-()const { return NGF_Vector2D(-x, -y); }
	FLOAT operator[](SIZE_T index)const { return (&x)[index]; }
	FLOAT& operator[](SIZE_T index) { return (&x)[index]; }
	NGF_Vector2D& operator+=(const NGF_Vector2D& v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	NGF_Vector2D& operator-=(const NGF_Vector2D& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}
	NGF_Vector2D& operator*=(FLOAT scale) {
		x *= scale;
		y *= scale;
		return *this;
	}
	NGF_Vector2D& operator/=(FLOAT scale) {
		x /= scale;
		y /= scale;
		return *this;
	}
	NGF_Vector2D& operator*=(const NGF_Vector2D& v) {
		x *= v.x;
		y *= v.y;
		return *this;
	}
	NGF_Vector2D& operator/=(const NGF_Vector2D& v) {
		x /= v.x;
		y /= v.y;
		return *this;
	}
	
	FLOAT operator*(const NGF_Vector2D& v)const { return x * v.x + y * v.y; }
	FLOAT operator&(const NGF_Vector2D& v)const { return x * v.y - y * v.x; }
	NGF_Vector2D operator+(const NGF_Vector2D& v)const { return NGF_Vector2D(x + v.x, y + v.y); }
	NGF_Vector2D operator-(const NGF_Vector2D& v)const { return NGF_Vector2D(x - v.x, y - v.y); }
	BOOL operator==(const NGF_Vector2D& v)const { return x == v.x && y == v.y; }
	BOOL operator!=(const NGF_Vector2D& v)const { return x != v.x || y != v.y; }



	VOID SetZero() {x = y = 0.0f;}
	VOID Set(FLOAT x, FLOAT y) {
		this->x = x;
		this->y = y;
	}
	VOID Set(const NGF_Vector2D& other) {
		x = other.x;
		y = other.y;
	}
	FLOAT Length() const {return NGF_Sqrt(x * x + y * y);}
	FLOAT LengthSquared() const { return x * x + y * y; }

	/**
	* @brief 将该向量转变成单位向量
	* 
	* @return 向量长度[注意是未转变之前的长度]
	*/
	FLOAT Normalize() {
		FLOAT length = Length();
		if (length < NGF_Epsilon)return 0.0f;
		FLOAT invLength = 1.0f / length;
		x *= invLength;
		y *= invLength;
		return length;
	}

	/**
	* @brief 该向量包含的坐标值是否有效
	*/
	BOOL IsValid() const {return nagisa::NGF_IsValid(x) && nagisa::NGF_IsValid(y);}

	/**
	* @brief 获取斜对称向量(反对称向量),dot(skew_vec, other) == cross(vec, other)
	* 
	* @return 斜对称向量(反对称向量)
	*/
	NGF_Vector2D Skew() const {return NGF_Vector2D(-y, x);}

	NGF_String ToString()const override;
public:
	FLOAT x;
	FLOAT y;
};

extern const NGF_Vector2D NGF_Vector2D_Zero;

/**
* @brief 在标量和矢量上执行叉乘，在2d中这是一个向量
*/
inline NGF_Vector2D operator&(const NGF_Vector2D& a, FLOAT s) { return NGF_Vector2D(s * a.y, -s * a.x); }
/**
* @brief 在标量和矢量上执行叉乘，在2d中这是一个向量
*/
inline NGF_Vector2D operator&(FLOAT s, const NGF_Vector2D& a) { return NGF_Vector2D(-s * a.y, s * a.x); }

inline NGF_Vector2D operator*(FLOAT s, const NGF_Vector2D& a) { return NGF_Vector2D(s * a.x, s * a.y); }
inline NGF_Vector2D operator*(const NGF_Vector2D& v, FLOAT s) { return NGF_Vector2D(s * v.x, s * v.y); }

inline FLOAT Distance(const NGF_Vector2D& a, const NGF_Vector2D& b) {
	NGF_Vector2D c = a - b;
	return c.Length();
}
inline FLOAT DistanceSquared(const NGF_Vector2D& a, const NGF_Vector2D& b) {
	NGF_Vector2D c = a - b;
	return c.LengthSquared();
}

class NGF_Vector3D {
	NGF_Vector3D() = default;
	NGF_Vector3D(FLOAT x, FLOAT y, FLOAT z) :x(x), y(y), z(z) {}

	NGF_Vector3D operator-()const { return NGF_Vector3D(-x, -y, -z); }
	NGF_Vector3D& operator+=(const NGF_Vector3D& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	NGF_Vector3D& operator-=(const NGF_Vector3D& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	NGF_Vector3D& operator*=(FLOAT scale) {
		x *= scale;
		y *= scale;
		z *= scale;
		return *this;
	}

	VOID SetZero() { x = y = z = 0.0f; }
	VOID Set(FLOAT x_, FLOAT y_, FLOAT z_) {
		x = x_;
		y = y_;
		z = z_;
	}



public:
	FLOAT x;
	FLOAT y;
	FLOAT z;
};



NGF_END

#endif // !__HEAD_NGF_Vector
