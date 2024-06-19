//==========================================================================================================
// @file	:	Math
// @author	:	NAGISA
// @data	:	2023/1/26 16:09:09
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Math
#define __HEAD_Math

#include "NMath/Math_Module.h"

#include "NMath/Vector.h"
#include "NMath/Rectangle.h"
#include "NMath/Matrix.h"

#if _MSC_VER

#if USE_NGS_MODULE
#pragma comment(lib,"NMath.lib")
#else
#pragma comment(lib,"NMath.lib")
#endif // USE_NGS_MODULE

#endif//_MSC_VER


#endif // !__HEAD_Math
