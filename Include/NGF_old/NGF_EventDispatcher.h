//==========================================================================================================
// @file	:	NGF_EventDispacher
// @author	:	NAGISA
// @data	:	2022/12/28 10:32:11
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGF_EventDispatcher
#define __HEAD_NGF_EventDispatcher

#include "NGF/NGF_Defined.h"
#include "NGF/NGF_IEventDispatcher.h"
#include "NGF/NGF_Object.h"



NGF_BEGIN

class NGF_EventDispatcher:virtual public NGF_Object,virtual public NGF_IEventDispatcher {
public:

public:


	virtual VOID AddEventListener(const NGF_String& type, const std::function<VOID(NGF_Event)>& listener, BOOL useCapture = FALSE, SIZE_T priority = 0, BOOL weakRef = false) override;
	virtual BOOL Dispatch(const NGF_Event& event)const override;
	virtual BOOL HasEventListener(const NGF_String& type)const override;
	virtual VOID RemoveEventListener(const NGF_String& type, const std::function<VOID(NGF_Event)>& listener, BOOL useCapture = FALSE) override;
	virtual BOOL WillTrigger(const NGF_String& type) const override;


private:

private:
};

NGF_END

#endif // !__HEAD_NGF_EventDispacher
