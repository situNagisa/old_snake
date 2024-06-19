//==========================================================================================================
// @file	:	NGF_DisplayObject
// @author	:	NAGISA
// @data	:	2022/12/28 10:35:13
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGF_DisplayObject
#define __HEAD_NGF_DisplayObject

#include "NGF/NGF_Defined.h"
#include "NGF/NGF_EventDispatcher.h"
#include "NGF/NGF_Vector.h"
#include "NGF/NGF_Rectangle.h"
#include "NGF/NGF_GDI.h"
#include "NGF/NGF_Vector_import.h"


NGF_BEGIN

class NGF_DisplayObject;
class NGF_DisplayObjectContainer;
class NGF_Stage;

NGF_INTERNAL_BEGIN

struct DisplayTreeMsg
{
	FLOAT radian = 0.0f;
	NGF_Vector2D<FLOAT32> scale = { 1.0f,1.0f };
};

DisplayTreeMsg DisplayObject_GetTreeMessage(const NGF_DisplayObject& display);

NGF_END

inline constexpr const NGF_BIT visible = NGF_BIT::BIT_1;

typedef class NGF_DisplayObject :virtual public NGF_EventDispatcher {
	friend NGF_INTERNAL::DisplayTreeMsg NGF_INTERNAL::DisplayObject_GetTreeMessage(const NGF_DisplayObject& display);

public:
	NGF_DisplayObject() :
		_radian(0.0f),
		_alpha(1.0f),
		_parent(nullptr),
		_stage(nullptr),
		_canvas(nullptr)
	{
		_pos.SetZero();
		_size.SetZero();
		_scale.Set(1.0f, 1.0f);

		SetVisible(TRUE);
	}
	virtual ~NGF_DisplayObject()override;

	FLOAT GetAlpha()const { return _alpha; }
	VOID SetAlpha(FLOAT alpha) { _alpha = alpha; }

	// ======= Position ========

	const NGF_Vector2D<FLOAT32>& GetPosition() const { return _pos; };
	VOID SetPosition(FLOAT x, FLOAT y);

	// ====== Size ========

	const NGF_Vector2D<FLOAT32>& GetSize() const { return _size; }
	VOID SetSize(FLOAT width, FLOAT height);

	// ======= Scale ==========

	const NGF_Vector2D<FLOAT32>& GetScale()const { return _scale; }
	VOID SetScale(FLOAT scaleX, FLOAT scaleY);

	// ======= radian ==========

	FLOAT GetRadian() const { return _radian; }
	VOID SetRadian(FLOAT radian);

	BOOL GetVisible() const { return NGF_IsFlag(_flag, visible); }
	VOID SetVisible(BOOL fixed) { NGF_SetFlag(_flag, visible, fixed); }

	NGF_Vector2D<FLOAT32> GlobalToLocal(const NGF_Vector2D<FLOAT32>& point) const;
	NGF_Vector2D<FLOAT32> LocalToGlobal(const NGF_Vector2D<FLOAT32>& point) const;

	virtual NGF_Rectangle GetBounds(const NGF_DisplayObject& targetCoordinateSpace) const;

	NGF_DisplayObjectContainer* GetParent() const { return _parent; }
	NGF_Stage* GetStage() const { return _stage; }

	virtual NGF_PCanvasDC Draw() = 0;

	
protected:
	virtual VOID _SetStage(NGF_Stage* pStage);
	virtual VOID _CalculateCurBounds();
protected:

	BYTE _flag = 0x00;
	//ÏÔÊ¾
	FLOAT _radian;
	FLOAT _alpha;
	NGF_Vector2D<FLOAT32> _pos;
	NGF_Vector2D<FLOAT32> _size;
	NGF_Vector2D<FLOAT32> _scale;
	NGF_Rectangle _bounds;

	//ÈÝÆ÷
	NGF_DisplayObjectContainer* _parent;
	NGF_Stage* _stage;
	
	NGF_PCanvasDC _canvas;



	friend class NGF_DisplayObjectContainer;

} *NGF_PDisplayObject;

NGF_END

#endif // !__HEAD_NGF_DisplayObject
