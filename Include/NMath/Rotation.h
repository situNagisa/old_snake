//==========================================================================================================
// @file	:	Rotation
// @author	:	NAGISA
// @data	:	2023/2/25 12:51:24
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Rotation
#define __HEAD_Rotation

#include "NGS/NGS.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NMath_Rotation;
#endif
#else // USE_NGS_MODULE
#include "NMath/Rotation_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_Rotation
