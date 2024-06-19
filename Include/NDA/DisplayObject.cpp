//==========================================================================================================
// @file	:	DisplayObject
// @author	:	NAGISA
// @data	:	2023/1/28 12:18:53
// @brief	:	
//==========================================================================================================

#include "NDA/DisplayObject.h"

NGS_BEGIN

_TYP VOID DisplayObject::Resize(_TYP BOOL v) {
    Bits(_flag, NEED_RESIZE, v);
    if (v) {
        if (!IsContainer()) {
            _refreshArea = _bounds;
            //Redraw(TRUE);
        }
        if (!_parent_r || _parent_r->NeedResize())return;
        _parent_r->Resize(v);
    }
}

DisplayObject::__matrix DisplayObject::GlobalMatrix() const
{
	if (!_parent_r)return _matrix;
	return _parent_r->GlobalMatrix() << _matrix;
}

_TYP VOID DisplayObjectContainer::AccessChildren(
    const std::function<_TYP BOOL(__base_ref)> callBack,
    const std::function<_TYP BOOL(__base_ref_cst)> isContinue
)const{
    for (auto it : _children) {
        if (callBack(*it))break;
        if (isContinue(*it))continue;
        if (it->IsContainer()) {
            auto container = reinterpret_cast<__this_ptr>(it);
            container->AccessChildren(callBack, isContinue);
        }
    }
}

_TYP VOID DisplayObjectContainer::Resize() {
    __base::Resize();
    for (auto it : _children) {
        if (it->NeedResize())it->Resize();
        if (!it->Bounds().Empty()) {
            if (_bounds.Empty())
                _bounds = (it->Bounds() << it->Matrix());
            else
                _bounds |= (it->Bounds() << it->Matrix());
        }
        
    }
}

_TYP VOID DisplayObjectContainer::Redraw(_TYP BOOL v) {
    __base::Redraw(v);
    if (v) {
        for (auto it : _children) {
            it->Redraw(v);
        }
    }
}

NGS_END