//==========================================================================================================
// @file	:	Sprite
// @author	:	NAGISA
// @data	:	2023/1/28 1:38:10
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Sprite
#define __HEAD_Sprite

#include "NGS/NGS.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NDA_Sprite;
#endif
#else // USE_NGS_MODULE
#include "NDA/Sprite_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_Sprite
