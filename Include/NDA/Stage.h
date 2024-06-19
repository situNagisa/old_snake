//==========================================================================================================
// @file	:	Stage
// @author	:	NAGISA
// @data	:	2023/1/28 1:37:43
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Stage
#define __HEAD_Stage

#include "NGS/NGS.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NDA_Stage;
#endif
#else // USE_NGS_MODULE
#include "NDA/Stage_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_Stage
