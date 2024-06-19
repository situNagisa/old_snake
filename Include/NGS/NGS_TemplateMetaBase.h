//==========================================================================================================
// @file	:	NGS_TemplateMetaBase
// @author	:	NAGISA
// @data	:	2023/1/27 11:57:37
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_TemplateMetaBase
#define __HEAD_NGS_TemplateMetaBase

#include "NGS/NGS_Module.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NGS_TemplateMetaBase;
#endif
#else // USE_NGS_MODULE
#include "NGS/NGS_TemplateMetaBase_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_NGS_TemplateMetaBase
