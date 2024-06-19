//==========================================================================================================
// @file	:	NGF_Matrix
// @author	:	NAGISA
// @data	:	2023/1/7 0:44:40
// @brief	:	
//==========================================================================================================


#include "NGF/NGF_Matrix.h"
#include "NGF/NGF_String.h"


NGF_BEGIN

NGF_String NGF_Matrix::ToString() const
{
	return NGF_String(6 * 6,TEXT("Matrix::( a = %3.2f, b = %3.2f ,c = %3.2f , d = %3.2f , tx = %3.2f , ty = %3.2f )"),a,b,c,d,tx,ty);
}

NGF_END