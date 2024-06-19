//==========================================================================================================
// @file	:	NGS_Bit
// @author	:	NAGISA
// @data	:	2023/1/16 21:03:07
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Bit
#define __HEAD_NGS_Bit

#include "NGS/NGS_Module.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NGS_Bit;
#endif
#else // USE_NGS_MODULE
#include "NGS/NGS_Bit_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_NGS_Bit
