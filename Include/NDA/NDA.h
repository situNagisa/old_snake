//==========================================================================================================
// @file	:	NDA
// @author	:	NAGISA
// @data	:	2023/1/28 1:36:49
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NDA
#define __HEAD_NDA

#include "NDA/NDA_Defined.h"
#include "NDA/DisplayObject.h"
#include "NDA/Stage.h"
#include "NDA/Sprite.h"
#include "NDA/Bitmap.h"
#include "NDA/MovieClip.h"
#include "NDA/Encode.h"
#include "NDA/Text.h"

#if _MSC_VER

#if USE_NGS_MODULE
#pragma comment(lib,"NDA.lib")
#else
#pragma comment(lib,"NDA.lib")
#endif // USE_NGS_MODULE

#endif//_MSC_VER

#endif // !__HEAD_NDA
