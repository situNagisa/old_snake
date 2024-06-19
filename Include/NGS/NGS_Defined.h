//==========================================================================================================
// @file	:	NGS_Defined
// @author	:	NAGISA
// @data	:	2022/12/24 10:54:33
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Defined
#define __HEAD_NGS_Defined

#include "NGS/NGS_Module.h"
#include "NGS/NGS_Defined_Macro.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NGS_Defined;
#endif
#else // USE_NGS_MODULE
#include "NGS/NGS_Defined_Module.h"
#endif // USE_NGS_MODULE

#endif