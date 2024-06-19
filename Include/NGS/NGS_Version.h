//==========================================================================================================
// @file	:	NGS_Version
// @author	:	NAGISA
// @data	:	2023/1/16 20:46:01
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Version
#define __HEAD_NGS_Version

#include "NGS/NGS_Module.h"
#include "NGS/NGS_Version_Macro.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NGS_Version;
#endif
#else // USE_NGS_MODULE
#include "NGS/NGS_Version_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_NGS_Version
