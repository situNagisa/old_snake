//==========================================================================================================
// @file	:	NGS_Blend
// @author	:	NAGISA
// @data	:	2023/2/9 13:07:55
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Blend
#define __HEAD_NGS_Blend

#include "NGS/NGS_Module.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NGS_Blend;
#endif
#else // USE_NGS_MODULE
#include "NGS/NGS_Blend_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_NGS_Blend
