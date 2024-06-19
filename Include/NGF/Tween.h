//==========================================================================================================
// @file	:	Tween
// @author	:	NAGISA
// @data	:	2023/2/23 15:08:49
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Tween
#define __HEAD_Tween

#include "NGS/NGS.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NGF_Tween;
#endif
#else // USE_NGS_MODULE
#include "NGF/Tween_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_Tween
