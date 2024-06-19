//==========================================================================================================
// @file	:	NGS_Setting
// @author	:	NAGISA
// @data	:	2023/2/9 17:46:31
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Setting
#define __HEAD_NGS_Setting

#include "NGS/NGS_Module.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NGS_Setting;
#endif
#else // USE_NGS_MODULE
#include "NGS/NGS_Setting_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_NGS_Setting
