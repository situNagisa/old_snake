//==========================================================================================================
// @file	:	Matrix
// @author	:	NAGISA
// @data	:	2023/1/27 20:49:05
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Matrix
#define __HEAD_Matrix

#include "NGS/NGS.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NMath_Matrix;
#endif
#else // USE_NGS_MODULE
#include "NMath/Matrix_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_Matrix
