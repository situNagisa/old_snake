//==========================================================================================================
// @file	:	Encode
// @author	:	NAGISA
// @data	:	2023/2/5 23:26:17
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Encode
#define __HEAD_Encode

#include "NGS/NGS.h"

#if USE_NGS_MODULE
#if !NGS_IN_MODULE
import NDA_Encode;
#endif
#else // USE_NGS_MODULE
#include "NDA/Encode_Module.h"
#endif // USE_NGS_MODULE

#endif // !__HEAD_Encode
