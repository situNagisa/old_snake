//==========================================================================================================
// @file	:	NGF_IEventDispatcher
// @author	:	NAGISA
// @data	:	2022/12/28 10:31:12
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGF_IEventDispatcher
#define __HEAD_NGF_IEventDispatcher

#include "NGF/NGF_Defined.h"
#include "NGF/NGF_Event.h"
#include "NGF/NGF_String.h"
#include <functional>



NGF_BEGIN

class NGF_IEventDispatcher
{
	virtual VOID AddEventListener(const NGF_String& type,const std::function<VOID(NGF_Event)>& listener, BOOL useCapture = FALSE, SIZE_T priority = 0, BOOL weakRef = false) = 0;
	virtual BOOL Dispatch(const NGF_Event& event)const = 0;
	virtual BOOL HasEventListener(const NGF_String& type)const = 0;
	virtual VOID RemoveEventListener(const NGF_String& type, const std::function<VOID(NGF_Event)>& listener, BOOL useCapture = FALSE) = 0;
	virtual BOOL WillTrigger(const NGF_String& type) const = 0;
};

NGF_END


#endif // !__HEAD_NGF_IEventDispatcher
