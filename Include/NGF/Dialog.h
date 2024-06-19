//==========================================================================================================
// @file	:	Dialog
// @author	:	NAGISA
// @data	:	2023/2/20 21:17:57
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Dialog
#define __HEAD_Dialog

#include "NGS/NGS.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NGF_Dialog;
#endif
#else // USE_NGS_MODULE
#include "NGF/Dialog_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_Dialog
