module;

#include "NGF/NGF_Defined.h"

export module NGF_Concepts;

NGF_BEGIN

//�ɼ�����ֵ
export
template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

NGF_END