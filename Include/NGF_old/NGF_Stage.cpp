//==========================================================================================================
// @file	:	NGF_Stage
// @author	:	NAGISA
// @data	:	2022/12/29 23:42:31
// @brief	:	
//==========================================================================================================


#include "NGF/NGF_Stage.h"
#include "NGF/NGF_Windows.h"

NGF_BEGIN

NGF_PDC NGF_Stage::GetDC() const
{
	return _window->GetDC();
}

NGF_PCanvasDC NGF_Stage::GetCanvas() const
{
	return _window->GetCanvasDC();
}

NGF_END


