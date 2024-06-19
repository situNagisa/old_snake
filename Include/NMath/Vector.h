//==========================================================================================================
// @file	:	Vector
// @author	:	NAGISA
// @data	:	2023/1/26 22:02:38
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Vector
#define __HEAD_Vector

#include "NGS/NGS.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NMath_Vector;
#endif
#else // USE_NGS_MODULE
#include "NMath/Vector_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_Vector
