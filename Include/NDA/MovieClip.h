//==========================================================================================================
// @file	:	MovieClip
// @author	:	NAGISA
// @data	:	2023/1/30 23:05:05
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_MovieClip
#define __HEAD_MovieClip

#include "NGS/NGS.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NDA_MovieClip;
#endif
#else // USE_NGS_MODULE
#include "NDA/MovieClip_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_MovieClip
