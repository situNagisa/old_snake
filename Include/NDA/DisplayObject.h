//==========================================================================================================
// @file	:	DisplayObject
// @author	:	NAGISA
// @data	:	2023/1/26 21:03:04
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_DisplayObject
#define __HEAD_DisplayObject

#include "NGS/NGS.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NDA_DisplayObject;
#endif
#else // USE_NGS_MODULE
#include "NDA/DisplayObject_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_DisplayObject
