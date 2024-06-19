//==========================================================================================================
// @file	:	NGS_Event
// @author	:	NAGISA
// @data	:	2023/2/13 15:20:59
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Event
#define __HEAD_NGS_Event

#include "NGS/NGS_Module.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NGS_Event;
#endif
#else // USE_NGS_MODULE
#include "NGS/NGS_Event_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_NGS_Event
