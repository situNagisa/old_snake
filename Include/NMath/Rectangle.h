//==========================================================================================================
// @file	:	Rectangle
// @author	:	NAGISA
// @data	:	2023/1/27 20:28:17
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Rectangle
#define __HEAD_Rectangle

#include "NGS/NGS.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NMath_Rectangle;
#endif
#else // USE_NGS_MODULE
#include "NMath/Rectangle_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_Rectangle
