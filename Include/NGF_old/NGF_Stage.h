//==========================================================================================================
// @file	:	NGF_Stage
// @author	:	NAGISA
// @data	:	2022/12/29 22:02:38
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGF_Stage
#define __HEAD_NGF_Stage

#include "NGF/NGF_Defined.h"
#include "NGF/NGF_DisplayObjectContainer.h"



NGF_BEGIN

class NGF_Windows;

typedef class NGF_Stage :public NGF_DisplayObjectContainer {
public:
	NGF_Stage(NGF_Windows* pWindow):
		_window(pWindow)
	{
		_SetStage(this);
	}
	NGF_PDC GetDC() const;
	NGF_PCanvasDC GetCanvas()const;
private:
	
	
private:
	NGF_Windows* _window;

} *NGF_PStage;

NGF_END

#endif // !__HEAD_NGF_Stage
