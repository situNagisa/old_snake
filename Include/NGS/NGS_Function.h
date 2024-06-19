//==========================================================================================================
// @file	:	NGS_Function
// @author	:	NAGISA
// @data	:	2023/2/16 16:18:29
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Function
#define __HEAD_NGS_Function

#include "NGS/NGS_Module.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NGS_Function;
#endif
#else // USE_NGS_MODULE
#include "NGS/NGS_Function_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_NGS_Function
