//==========================================================================================================
// @file	:	NGS_Lib
// @author	:	NAGISA
// @data	:	2023/2/16 18:05:31
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Lib
#define __HEAD_NGS_Lib

#include "NGS/NGS_Module.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NGS_Lib;
#endif
#else // USE_NGS_MODULE
#include "NGS/NGS_Lib_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_NGS_Lib
