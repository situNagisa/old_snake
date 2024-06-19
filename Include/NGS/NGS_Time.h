//==========================================================================================================
// @file	:	NGS_Time
// @author	:	NAGISA
// @data	:	2023/2/14 14:48:37
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Time
#define __HEAD_NGS_Time

#include "NGS/NGS_Module.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NGS_Time;
#endif
#else // USE_NGS_MODULE
#include "NGS/NGS_Time_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_NGS_Time
