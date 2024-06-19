//==========================================================================================================
// @file	:	StageCtrl
// @author	:	NAGISA
// @data	:	2023/1/30 20:50:14
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_StageCtrl
#define __HEAD_StageCtrl

#include "NGS/NGS.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NGF_StageCtrl;
#endif
#else // USE_NGS_MODULE
#include "NGF/StageCtrl_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_StageCtrl
