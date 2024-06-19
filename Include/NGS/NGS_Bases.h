//==========================================================================================================
// @file	:	NGS_Bases
// @author	:	NAGISA
// @data	:	2023/2/9 0:08:28
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Bases
#define __HEAD_NGS_Bases

#include "NGS/NGS_Module.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NGS_Bases;
#endif
#else // USE_NGS_MODULE
#include "NGS/NGS_Bases_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_NGS_Bases
