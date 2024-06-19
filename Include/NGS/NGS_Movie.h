//==========================================================================================================
// @file	:	NGS_Movie
// @author	:	NAGISA
// @data	:	2023/2/16 22:40:24
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Movie
#define __HEAD_NGS_Movie

#include "NGS/NGS_Module.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NGS_Movie;
#endif
#else // USE_NGS_MODULE
#include "NGS/NGS_Movie_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_NGS_Movie
