//==========================================================================================================
// @file	:	NGS_Color
// @author	:	NAGISA
// @data	:	2023/2/6 21:32:59
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Color
#define __HEAD_NGS_Color

#include "NGS/NGS_Module.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NGS_Color;
#endif
#else // USE_NGS_MODULE
#include "NGS/NGS_Color_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_NGS_Color
