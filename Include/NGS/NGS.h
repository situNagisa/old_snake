//==========================================================================================================
// @file	:	NGS
// @author	:	NAGISA
// @data	:	2023/1/15 3:48:35
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS
#define __HEAD_NGS

#include "NGS/NGS_Module.h"
#include "NGS/NGS_Bit.h"
#include "NGS/NGS_Concepts.h"
#include "NGS/NGS_Defined.h"
#include "NGS/NGS_String.h"
#include "NGS/NGS_TypeTrait.h"
#include "NGS/NGS_Version.h"
#include "NGS/NGS_Config.h"
#include "NGS/NGS_Object.h"
#include "NGS/NGS_Memory.h"
#include "NGS/NGS_TemplateMetaBase.h"
#include "NGS/NGS_Color.h"
#include "NGS/NGS_Bases.h"
#include "NGS/NGS_Setting.h"
#include "NGS/NGS_Event.h"
#include "NGS/NGS_Time.h"
#include "NGS/NGS_Function.h"
#include "NGS/NGS_Lib.h"
#include "NGS/NGS_Movie.h"


#include "NGS/NGS_Macro.h"

#if _MSC_VER

#if USE_NGS_MODULE
#pragma comment(lib,"NGS.lib")
#else
#pragma comment(lib,"NGS_nomodule.lib")
#endif // USE_NGS_MODULE

#endif//_MSC_VER




#endif // !__HEAD_NGS
