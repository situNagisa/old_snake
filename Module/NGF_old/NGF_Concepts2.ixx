module;

#include "NGF/NGF_Defined.h"

export module NGF_Concepts;

NGF_BEGIN

//可计算数值
export
template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

NGF_END