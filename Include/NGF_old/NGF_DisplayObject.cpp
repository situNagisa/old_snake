//==========================================================================================================
// @file	:	NGF_DisplayObject
// @author	:	NAGISA
// @data	:	2023/1/3 11:21:34
// @brief	:	
//==========================================================================================================


#include "NGF/NGF_DisplayObject.h"
#include "NGF/NGF_Stage.h"


NGF_BEGIN

NGF_INTERNAL_BEGIN

DisplayTreeMsg DisplayObject_GetTreeMessage(const NGF_DisplayObject& display)
{
	DisplayTreeMsg msg = { display._radian,display._scale };
	
	const NGF_DisplayObjectContainer* p = display._parent;
	while (p) {
		msg.radian += p->_radian;
		msg.scale *= p->_scale;
		p = p->GetParent();
	}
	
	return msg;
}

NGF_END

NGF_DisplayObject::~NGF_DisplayObject()
{
	_SetStage(nullptr);
}

VOID NGF_DisplayObject::SetPosition(FLOAT x, FLOAT y)
{
	if (x == _pos.x && y == _pos.y)return;
	_pos.Set(x, y);
	_CalculateCurBounds();
}

VOID NGF_DisplayObject::SetSize(FLOAT width, FLOAT height)
{
	if (width == _size.x && height == _size.y)return;
	_size.Set(width, height);
	_CalculateCurBounds();
}

VOID NGF_DisplayObject::SetScale(FLOAT scaleX, FLOAT scaleY)
{
	if (scaleX == _scale.x && scaleY == _scale.y)return;
	_scale.Set(scaleX, scaleY);
	_CalculateCurBounds();
}

VOID NGF_DisplayObject::SetRadian(FLOAT radian)
{
	if (radian == _radian)return;
	_radian = radian;
	_CalculateCurBounds();
}

NGF_Vector2D<FLOAT32> NGF_DisplayObject::GlobalToLocal(const NGF_Vector2D<FLOAT32>& global) const
{
	auto local = global;
	auto global_scale = NGF_INTERNAL::DisplayObject_GetTreeMessage(*this).scale;
	local -= LocalToGlobal({ 0.0f,0.0f });
	local /= global_scale;
	return local;
}

NGF_Vector2D<FLOAT32> NGF_DisplayObject::LocalToGlobal(const NGF_Vector2D<FLOAT32>& local) const
{
	auto global = local;
	const NGF_DisplayObjectContainer* p = _parent;
	const NGF_DisplayObject* c = this;
	while (p) {
		global *= c->_scale;
		global += c->_pos;
		c = p;
		p = p->GetParent();
	}
	return global;
}

NGF_Rectangle NGF_DisplayObject::GetBounds(const NGF_DisplayObject& targetCoordinateSpace) const
{
	if (&targetCoordinateSpace == this)return _bounds;
	NGF_Vector2D<FLOAT32> l_t = targetCoordinateSpace.GlobalToLocal(LocalToGlobal({ _bounds.x,_bounds.y }));
	NGF_Vector2D<FLOAT32> w_h = targetCoordinateSpace.GlobalToLocal(LocalToGlobal({ _bounds.width,_bounds.height }));
	w_h -= l_t;
	return { l_t.x,l_t.y,w_h.x,w_h.y };
}

VOID NGF_DisplayObject::_SetStage(NGF_Stage* pStage)
{
	_stage = pStage;
	if (_canvas) {
		NGF_Free<NGF_CanvasDC>(_canvas);
	}
	if (_stage)_canvas = NGF_CAllocate<NGF_CanvasDC>(1, _stage->GetDC()->GetDC());
}

VOID NGF_DisplayObject::_CalculateCurBounds()
{
	
	if (_parent)_parent->_CalculateCurBounds();
}

NGF_END
