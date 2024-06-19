//==========================================================================================================
// @file	:	NGS_String
// @author	:	NAGISA
// @data	:	2023/1/16 18:52:05
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_String
#define __HEAD_NGS_String

#include "NGS/NGS_Module.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NGS_String;
#endif
#else // USE_NGS_MODULE
#include "NGS/NGS_String_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_NGS_String
