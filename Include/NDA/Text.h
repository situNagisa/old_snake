//==========================================================================================================
// @file	:	Text
// @author	:	NAGISA
// @data	:	2023/2/10 14:08:30
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Text
#define __HEAD_Text

#include "NGS/NGS.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NDA_Text;
#endif
#else // USE_NGS_MODULE
#include "NDA/Text_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_Text
