//==========================================================================================================
// @file	:	NGF_DisplayObjectContainer
// @author	:	NAGISA
// @data	:	2022/12/28 10:38:31
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGF_DisplayObjectContainer
#define __HEAD_NGF_DisplayObjectContainer


#include "NGF/NGF_Defined.h"
#include "NGF/NGF_DisplayObject.h"
#include <vector>
#include <functional>



NGF_BEGIN

typedef class NGF_DisplayObjectContainer:public NGF_DisplayObject{
public:
	NGF_DisplayObjectContainer() :
		_numChildren(0),
		_children()
	{
		
	}

	VOID AccessChildren(
		const std::function<BOOL(NGF_DisplayObject&)> callBack,
		const std::function<BOOL(const NGF_DisplayObject&)> isContinue = [](const NGF_DisplayObject&)->BOOL {return FALSE; }
	)const ;

	NGF_PDisplayObject AddChild(NGF_DisplayObject& child);
	NGF_PDisplayObject AddChildAt(NGF_DisplayObject& child,UINT32 index);
	NGF_PDisplayObject GetChildAt(UINT32 index) const;
	UINT32 GetChildIndex(NGF_DisplayObject& child) const;
	NGF_PDisplayObject RemoveChildAt(UINT32 index);
	NGF_PDisplayObject RemoveChild(NGF_DisplayObject& child);

	UINT32 GetNumChildren(BOOL includeChildsChildren = FALSE)const;
	
	BOOL Contain(const NGF_DisplayObject& display)const;

	NGF_PCanvasDC Draw() override;

protected:
	VOID _SetStage(NGF_Stage* pStage)override;
	VOID _CalculateCurBounds()override;
private:
	VOID _AddChild(NGF_DisplayObject& child);
	VOID _RemoveChild(NGF_DisplayObject& child);

private:
	std::vector<NGF_PDisplayObject> _children;
	UINT32 _numChildren;

	friend class NGF_DisplayObject;

} *NGF_PDisplayObjectContainer;

NGF_END

#endif // !__HEAD_NGF_DisplayObjectContainer
