//==========================================================================================================
// @file	:	NGS_Memory
// @author	:	NAGISA
// @data	:	2023/1/26 15:02:17
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Memory
#define __HEAD_NGS_Memory

#include "NGS/NGS_Module.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NGS_Memory;
#endif
#else // USE_NGS_MODULE
#include "NGS/NGS_Memory_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_NGS_Memory
