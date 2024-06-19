//==========================================================================================================
// @file	:	NGF_DisplayObjectContainer
// @author	:	NAGISA
// @data	:	2023/1/3 11:44:30
// @brief	:	
//==========================================================================================================


#include "NGF/NGF_DisplayObjectContainer.h"
#include "NGF/NGF_Stage.h"
#include "NGF/NGF_BitmapData.h"

NGF_BEGIN


VOID NGF_DisplayObjectContainer::AccessChildren(
	const std::function<BOOL(NGF_DisplayObject&)> callBack,
	const std::function<BOOL(const NGF_DisplayObject&)> isContinue
)const
{
	for (auto it : _children) {
		if (callBack(*it))break;
		if (isContinue(*it))continue;
		if (auto container = dynamic_cast<NGF_PDisplayObjectContainer>(it)) {
			container->AccessChildren(callBack);
		}
	}
}

NGF_PDisplayObject NGF_DisplayObjectContainer::AddChild(NGF_DisplayObject& child)
{
	_children.push_back(&child);
	_AddChild(child);
	return &child;
}

NGF_PDisplayObject NGF_DisplayObjectContainer::AddChildAt(NGF_DisplayObject& child, UINT32 index)
{
	if (index >= _numChildren) {
		AddChild(child);
		return &child;
	}
	auto it = _children.begin();
	it += index;
	_children.insert(it, 1, &child);
	_AddChild(child);
	return &child;
}

NGF_PDisplayObject NGF_DisplayObjectContainer::GetChildAt(UINT32 index) const
{
	return _children.at(index);
}

UINT32 NGF_DisplayObjectContainer::GetChildIndex(NGF_DisplayObject& child) const
{
	for (UINT32 i = 0; i < _numChildren; i++)
	{
		if (_children[i] == &child)return i;
	}
	return -1;
}

NGF_PDisplayObject NGF_DisplayObjectContainer::RemoveChildAt(UINT32 index)
{
	auto& child = *_children.at(index);
	_children.erase(_children.begin() + index);
	_RemoveChild(child);
	return &child;
}

NGF_PDisplayObject NGF_DisplayObjectContainer::RemoveChild(NGF_DisplayObject& child)
{
	UINT32 index = GetChildIndex(child);
	if (index == -1)return nullptr;
	return RemoveChildAt(index);
}

UINT32 NGF_DisplayObjectContainer::GetNumChildren(BOOL includeChildsChildren) const
{
	if (!includeChildsChildren)return _numChildren;
	UINT32 num = _numChildren;
	for (auto& it : _children) {
		NGF_PDisplayObjectContainer container = dynamic_cast<NGF_PDisplayObjectContainer>(it);
		if (!container)continue;
		num += container->GetNumChildren(TRUE);
	}
	return num;
}

BOOL NGF_DisplayObjectContainer::Contain(const NGF_DisplayObject& display) const
{
	const NGF_DisplayObject* p = &display;
	do
	{
		if (p == this)return TRUE;
		p = p->GetParent();
	} while (p);
	return FALSE;
}

NGF_PCanvasDC NGF_DisplayObjectContainer::Draw()
{
	auto bounds = GetBounds(*this);
	_canvas->CreateCanvas(static_cast<LONG>(bounds.x),static_cast<LONG>(bounds.y),static_cast<LONG>(bounds.width), static_cast<LONG>(bounds.height));
	//绘制Shape
	
	/*for (UINT32 i = 0; i < _numChildren; i++)
	{
		NGF_PDisplayObject pDisplay = _children[i];
		NGF_Rectangle thisBounds = pDisplay->GetBounds(*this);
		NGF_Rectangle bounds = pDisplay->GetBounds(*pDisplay);
		_canvas->StretchBlt(thisBounds, *pDisplay->Draw(), bounds);
	}*/
	//_stage->GetDC()->BitBlt(NGF_Vector2D_Zero, _size, *_canvas, NGF_Vector2D_Zero);
	return _canvas;
}

VOID NGF_DisplayObjectContainer::_SetStage(NGF_Stage* pStage)
{
	NGF_DisplayObject::_SetStage(pStage);
	for (auto& it : _children) 
		it->_SetStage(_stage);
}

VOID NGF_DisplayObjectContainer::_CalculateCurBounds()
{
	_bounds.SetZero();
	//计算Shape
	for (auto& it : _children)
		_bounds += it->GetBounds(*this);
	
	_size.x = _bounds.width;
	_size.y = _bounds.height;
	NGF_DisplayObject::_CalculateCurBounds();
}

VOID NGF_DisplayObjectContainer::_AddChild(NGF_DisplayObject& child)
{
	child._parent = this;
	child._SetStage(_stage);
	_numChildren++;
	_CalculateCurBounds();
}

VOID NGF_DisplayObjectContainer::_RemoveChild(NGF_DisplayObject& child)
{
	child._parent = nullptr;
	child._SetStage(nullptr);
	_numChildren--;
	_CalculateCurBounds();
}

NGF_END


