//==========================================================================================================
// @file	:	ButtonGroup
// @author	:	NAGISA
// @data	:	2023/2/19 17:21:25
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_ButtonGroup
#define __HEAD_ButtonGroup

#include "NGS/NGS.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NGF_ButtonGroup;
#endif
#else // USE_NGS_MODULE
#include "NGF/ButtonGroup_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_ButtonGroup
