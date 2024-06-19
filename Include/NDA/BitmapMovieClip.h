//==========================================================================================================
// @file	:	BitmapMovieClip
// @author	:	NAGISA
// @data	:	2023/1/30 23:34:32
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_BitmapMovieClip
#define __HEAD_BitmapMovieClip


#include "NGS/NGS.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NDA_BitmapMovieClip;
#endif
#else // USE_NGS_MODULE
#include "NDA/BitmapMovieClip_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_BitmapMovieClip
