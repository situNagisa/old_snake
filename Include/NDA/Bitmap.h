//==========================================================================================================
// @file	:	Bitmap
// @author	:	NAGISA
// @data	:	2023/1/30 16:21:39
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Bitmap
#define __HEAD_Bitmap

#include "NGS/NGS.h"


#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NDA_Bitmap;
#endif
#else // USE_NGS_MODULE
#include "NDA/Bitmap_Module.h"
#endif // USE_NGS_MODULE


#endif // !__HEAD_Bitmap
