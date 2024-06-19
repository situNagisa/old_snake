//==========================================================================================================
// @file	:	NGS_Module_Macro
// @author	:	NAGISA
// @data	:	2023/1/16 18:10:35
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Module_Macro
#define __HEAD_NGS_Module_Macro

#if _NGS_PROJECT_

#if _BUILD_MODULE_
#define USE_NGS_MODULE 1
#else
#define USE_NGS_MODULE 0
#endif//_BUILD_MODULE_

#endif //_NGS_PROJECT_

#if USE_NGS_MODULE

#define NGS_EXPORT export

#else

#define NGS_EXPORT 

#endif

#endif // !__HEAD_NGS_Module_Macro
