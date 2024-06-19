//==========================================================================================================
// @file	:	NGF_EventDispatcher
// @author	:	NAGISA
// @data	:	2022/12/31 11:45:52
// @brief	:	
//==========================================================================================================


#include "NGF/NGF_EventDispatcher.h"

NGF_BEGIN

VOID NGF_EventDispatcher::AddEventListener(const NGF_String& type, const std::function<VOID(NGF_Event)>& listener, BOOL useCapture, SIZE_T priority, BOOL weakRef)
{
	
}

BOOL NGF_EventDispatcher::Dispatch(const NGF_Event& event) const
{
	return 0;
}

BOOL NGF_EventDispatcher::HasEventListener(const NGF_String& type) const
{
	return 0;
}

VOID NGF_EventDispatcher::RemoveEventListener(const NGF_String& type, const std::function<VOID(NGF_Event)>& listener, BOOL useCapture)
{
	return VOID();
}

BOOL NGF_EventDispatcher::WillTrigger(const NGF_String& type) const
{
	return 0;
}


NGF_END

