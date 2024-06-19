//==========================================================================================================
// @file	:	NGS_TypeTrait
// @author	:	NAGISA
// @data	:	2023/1/16 20:51:41
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_TypeTrait
#define __HEAD_NGS_TypeTrait

#include "NGS/NGS_Module.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NGS_TypeTrait;
#endif
#else // USE_NGS_MODULE
#include "NGS/NGS_TypeTrait_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_NGS_TypeTrait
