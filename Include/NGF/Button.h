//==========================================================================================================
// @file	:	Button
// @author	:	NAGISA
// @data	:	2023/1/30 22:03:45
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Button
#define __HEAD_Button

#include "NGS/NGS.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NGF_Button;
#endif
#else // USE_NGS_MODULE
#include "NGF/Button_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_Button
