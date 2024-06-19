//==========================================================================================================
// @file	:	NGF
// @author	:	NAGISA
// @data	:	2023/1/26 16:06:07
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGF
#define __HEAD_NGF

#include "NGS/NGS.h"

#include "NGF/StageCtrl.h"
#include "NGF/Button.h"
#include "NGF/ButtonGroup.h"
#include "NGF/Dialog.h"
#include "NGF/Tween.h"

#if _MSC_VER

#if USE_NGS_MODULE
#pragma comment(lib,"NGF.lib")
#else
#pragma comment(lib,"NGF.lib")
#endif // USE_NGS_MODULE

#endif//_MSC_VER

#endif // !__HEAD_NGF
