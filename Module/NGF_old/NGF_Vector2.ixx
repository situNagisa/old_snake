module;

#include "NGF/NGF_Defined.h"
export module NGF_Vector;
import NGF_Concepts;


NGF_BEGIN

/**
* 不负责申请内存，子类需要申请 sizeof(Number) * (N - 1)的内存
*
*/
template<SIZE_T N , Arithmetic Number>
class _NGF_Vector {
	template<typename Num>
	using Vector = _NGF_Vector<N,Num>;
	using Vector_Same = Vector<Number>;

	using PNumber = Number*;
	
public:
	_NGF_Vector()
	{}
	template<typename ...Args>
	_NGF_Vector(Args ...args):_NGF_Vector() {
		_Construct(args...);
	}
	_NGF_Vector(const Vector_Same& other) :_NGF_Vector() { _Construct(other); }
	template<Arithmetic Num> _NGF_Vector(const Vector<Num>& other) : _NGF_Vector() {
		_Construct(other);
	}
	
	template<Arithmetic Num> explicit operator Vector<Num>()const {
		Vector<Num> v(*this);
		return v;
	}
	
	Number& operator[](const SIZE_T index) { return (&x)[index]; }
	Number operator[](const SIZE_T index)const { return (&x)[index]; }
	
	auto operator<=>(const Vector_Same& other) const= default;

	_NGF_Vector operator-()const  {
		Vector_Same v(*this);
		for (SIZE_T i = 0; i < N; i++)
			v[i] *= -1;

		return v;
	}
	
	template<Arithmetic Num> _NGF_Vector& operator+=(const Vector<Num>& other) {
		for (SIZE_T i = 0; i < N; i++)
			(&x)[i] += other[i];
		
		return *this;
	}
	template<Arithmetic Num> _NGF_Vector operator+(const Vector<Num>& other)const {
		Vector_Same v(*this);
		v += other;
		return v;
	}
	
	template<Arithmetic Num> _NGF_Vector& operator-=(const Vector<Num>& other) {
		for (SIZE_T i = 0; i < N; i++)
			(&x)[i] -= other[i];

		return *this;
	}
	template<Arithmetic Num> _NGF_Vector operator-(const Vector<Num>& other)const {
		Vector_Same v(*this);
		v -= other;
		return v;
	}

	template<Arithmetic Num> _NGF_Vector& operator*=(const Vector<Num>& other) {
		for (SIZE_T i = 0; i < N; i++)
			(&x)[i] *= other[i];

		return *this;
	}
	template<Arithmetic Num> _NGF_Vector& operator*=(Num scale) {
		for (SIZE_T i = 0; i < N; i++)
			(&x)[i] *= scale;

		return *this;
	}
	template<Arithmetic Num> _NGF_Vector operator*(Num scale)const {
		Vector_Same v(*this);
		v *= scale;
		return v;
	}
	template<Arithmetic Num> friend _NGF_Vector operator*(Num scale,const Vector_Same& v) {
		return v * scale;
	}
	
	template<Arithmetic Num> _NGF_Vector& operator/=(const Vector<Num>& other) {
		for (SIZE_T i = 0; i < N; i++)
			(&x)[i] /= other[i];

		return *this;
	}
	template<Arithmetic Num> _NGF_Vector& operator/=(Num scale) {
		//assert(scale,"scale == 0");
		for (SIZE_T i = 0; i < N; i++)
			(&x)[i] /= scale;

		return *this;
	}
	template<Arithmetic Num> _NGF_Vector operator/(Num scale)const {
		Vector_Same v(*this);
		v /= scale;
		return v;
	}
	template<Arithmetic Num> friend _NGF_Vector operator/(Num scale, const Vector_Same& v) {
		Vector_Same v2(v);
		for (SIZE_T i = 0; i < N; i++)
			v2[i] = scale / v[i];

		return v2;
	}

	template<Arithmetic Num> auto operator*(const Vector<Num>& other) const{
		auto sum = Num() + Number();
		for (SIZE_T i = 0; i < N; i++) 
			sum += ((&x)[i] * other[i]);
		
		return sum;
	}
	template<Arithmetic Num> auto operator/(const Vector<Num>& other)const {
		auto sum = Num() + Number();
		for (SIZE_T i = 0; i < N; i++)
			sum += ((&x)[i] / other[i]);

		return sum;
	}
	
	constexpr SIZE_T GetSize() const { return N; }

	VOID SetZero() {memset((&x), 0, _size()); }
	VOID Fill(Number value) {
		for (SIZE_T i = 0; i < N; i++)
			(&x)[i] = value;
	}
	template<typename ...Args> VOID Set(Args ...args) {
		static_assert(sizeof...(args) <= N && "初始化数量过多");
		SIZE_T index = 0;
		((index < (sizeof...(args)) && ((&x)[index++] = args)), ...);
	}
	
	FLOAT32 Length()const {return /*NGF_Sqrt*/((*this) * (*this));}
	Number LengthSquard()const {return (*this) * (*this);}
	
	/**
	* @brief 将该向量转变成单位向量
	*
	* @return 向量长度[注意是未转变之前的长度]
	*/
	FLOAT32 Normalize() {
		FLOAT32 length = Length();
		/*if (length < NGF_Epsilon)return 0.0f;*/
		FLOAT32 invLength = 1.0f / length;
		//*this *= invLength;
		return length;
	}

	BOOL IsValid() const {
		/*for (SIZE_T i = 0; i < N; i++)
			if (!nagisa::IsValid((&x)[i]))return FALSE;*/
		return TRUE;
	}

protected:
	constexpr SIZE_T _size()const { return N * sizeof(Number); }

	template<typename ...Args>
	VOID _Construct(Args ...args){
		static_assert(sizeof...(args) <= N && "初始化数量过多");
		SIZE_T index = 0;
		(((&x)[index++] = args), ...);
	}
	VOID _Construct(const Vector_Same& other){ memcpy((&x), &other.x, _size()); }
	template<Arithmetic Num> VOID _Construct(const Vector<Num>& other){
		for (SIZE_T i = 0; i < N; i++)
			(&x)[i] = other[i];
	}
public:
	Number x;
};

// ================================
// 继承链
// ================================

//子类只负责申请内存，不做其他拓展
template<SIZE_T N = 2,Arithmetic Number = FLOAT32 >
	requires (N > 1)
class _NGF_Vector2D :public _NGF_Vector<N,Number> {
public:
	Number y;
};

template<SIZE_T N = 3, Arithmetic Number = FLOAT32>
	requires (N > 2)
class _NGF_Vector3D :public _NGF_Vector2D<N,Number> {
public:
	Number z;
};

template<SIZE_T N = 2 , Arithmetic Number = FLOAT32>
	requires (N > 1)
class _NGF_VectorND :public _NGF_Vector<N,Number> {
public:
	Number data[N - 1];
};

// ================================
// 1D
// ================================
export
template<Arithmetic Number = FLOAT32>
class NGF_Vector1D final :public _NGF_Vector<1, Number> {
	using Vector_Same = NGF_Vector1D<Number>;
public:
	NGF_Vector1D(Number x = 0) {
		this->_Construct(x);
	}
};

export
template<Arithmetic Number = FLOAT32>
inline const NGF_Vector1D<Number> NGF_Vector1D_Zero = { 0 };
// ================================
// 2D
// ================================
export
template<Arithmetic Number = FLOAT32>
class NGF_Vector2D final :public _NGF_Vector2D<2,Number>  {
	using Vector_Same = NGF_Vector2D<Number>;
public:
	NGF_Vector2D(Number x = 0, Number y = 0) {
		this->_Construct(x, y);
	}

	/**
	* @brief 获取斜对称向量(反对称向量),dot(skew_vec, other) == cross(vec, other)
	*
	* @return 斜对称向量(反对称向量)
	*/
	NGF_Vector2D Skew() const { return Vector_Same(-this->y, this->x); }

	/**
	* @brief 在标量和矢量上执行叉乘，在2d中这是一个向量
	*/
	friend NGF_Vector2D operator&(const Vector_Same& a, FLOAT s) { return Vector_Same(s * a.y, -s * a.x); }
	/**
	* @brief 在标量和矢量上执行叉乘，在2d中这是一个向量
	*/
	friend NGF_Vector2D operator&(FLOAT s, const Vector_Same& a) { return Vector_Same(-s * a.y, s * a.x); }
};

export
template<Arithmetic Number = FLOAT32>
inline const NGF_Vector2D<Number> NGF_Vector2D_Zero = { 0 , 0 };
// ================================
// 3D
// ================================
export
template<Arithmetic Number = FLOAT32>
class NGF_Vector3D final :public _NGF_Vector3D<3,Number> {
public:
	NGF_Vector3D(Number x = 0, Number y = 0, Number z = 0) {
		this->_Construct(x,y,z);
	}


};

export
template<Arithmetic Number = FLOAT32>
inline const NGF_Vector2D<Number> NGF_Vector3D_Zero = { 0 , 0 , 0 };
// ================================
// ND
// ================================
export
template<SIZE_T N = 2,Arithmetic Number = FLOAT32>
	requires (N > 1)
class NGF_Vector final :public _NGF_VectorND<N,Number> {
public:
	template<typename ...Args>
	NGF_Vector(Args ...args){
		this->_Construct(args...);
	}
};

// ================================
// Base
// ================================
export
template<SIZE_T N, Arithmetic Number>
using NGF_VectorBase = _NGF_Vector<N, Number>;


NGF_END