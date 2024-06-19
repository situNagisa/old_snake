//==========================================================================================================
// @file	:	NGS_Concepts
// @author	:	NAGISA
// @data	:	2023/1/16 20:58:37
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Concepts
#define __HEAD_NGS_Concepts

#include "NGS/NGS_Module.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NGS_Concepts;
#endif
#else // USE_NGS_MODULE
#include "NGS/NGS_Concepts_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_NGS_Concepts
