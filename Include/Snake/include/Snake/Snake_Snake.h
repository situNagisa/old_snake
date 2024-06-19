//==========================================================================================================
// @file	:	Snake_Snake
// @author	:	NAGISA
// @data	:	2023/1/17 18:45:26
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Snake_Snake
#define __HEAD_Snake_Snake

#include "NGS/NGS.h"
#include "Snake/Snake_DeviceContext.h"
#include "Snake/Snake_Bitmap.h"
#include "Snake/Snake_Config_Macro.h"
#include "Snake/Snake_Direct.h"
#include "Snake/Snake_ActionCtrler.h"


struct Node {
private:
    using _this = Node;
    using _this_ptr = _this*;
    using _this_ptr_cst = const _this_ptr;
    using _this_ref = _this&;
    using _this_ref_cst = const _this_ref;

    using _display = Bitmap;
    using _display_ptr = _display*;

public:
    _this_ptr prev = nullptr;
    _this_ptr next = nullptr;
    _display_ptr display = nullptr;
};

class Snake {
private:
    using _this = Snake;
    using _this_ptr = _this*;
    using _this_ptr_cst = const _this_ptr;
    using _this_ref = _this&;
    using _this_ref_cst = const _this_ref;

    using _node = Node;
    using _node_ptr = _node*;
    using _node_ptr_cst = const _node_ptr;
    using _node_ref = _node&;
    using _node_ref_cst = const _node_ref;

    using _size = UINT16;
    using _pos = INT16;

    using _list_t = _node_ptr;

    using _dc = DC;
    using _dc_ptr = _dc*;
    using _dc_ptr_cst = const _dc*;
    using _dc_ref = _dc&;
    using _dc_ref_cst = const _dc&;

public:
    Snake(_node_ptr headNode) :
        _head(headNode),
        _list(headNode),
        _length(0),
        direct(Direct::RIGHT),
        velocity(1)
    {

    }

    VOID Update() {
        INT8 dx = 0, dy = 0;
        if (_pActionCtrler)direct = _pActionCtrler->GetDirect();
        switch (direct)
        {
        case Direct::UP:
            dy = -1;
            break;
        case Direct::DOWN:
            dy = 1;
            break;
        case Direct::RIGHT:
            dx = 1;
            break;
        case Direct::LEFT:
            dx = -1;
            break;
        }
        for (SIZE_T i = 0; i < velocity; i++)
        {
            _MoveOnce(dx, dy);
        }

    }
    VOID SetPosition(_pos x, _pos y) {
        x -= _head->display->x;
        y -= _head->display->y;
        for (auto pNode = _head; pNode; pNode = pNode->next)
        {
            pNode->display->BoundsMove(x, y);
            pNode->display->x += x;
            pNode->display->y += y;
        }

    }
    NGS_INLINE VOID AddNode(_node_ptr pNode) {
        pNode->display->x = _list->display->x;
        pNode->display->y = _list->display->y;

        INT8 dx = 0, dy = 0;
        switch (direct)
        {
        case Direct::UP:
            dy = -1;
            break;
        case Direct::DOWN:
            dy = 1;
            break;
        case Direct::RIGHT:
            dx = 1;
            break;
        case Direct::LEFT:
            dx = -1;
            break;
        }
        _MoveOnce(dx, dy);
        
        _list->next = pNode;
        pNode->prev = _list;
        _list = pNode;

        
        _length++;
    }
    NGS_INLINE _list_t RemoveNode() {
        auto pNode = _list;
        _list = pNode->prev;
        _list->next = nullptr;
        _length--;

        return pNode;
    }
    NGS_INLINE _size GetLength()const { return _length; }

    NGS_INLINE _list_t GetHead() { return _head; }
    NGS_INLINE _pos GetX()const { return _head->display->x; }
    NGS_INLINE _pos GetY()const { return _head->display->y; }

    NGS_INLINE VOID SetActionCtrler(ActionCtrler* pActionCtrler) {
        _pActionCtrler = pActionCtrler;
    }
private:
    NGS_INLINE VOID _MoveOnce(INT8 dx,INT8 dy) {
        auto pNode = _list;
        if (_length > 1) {
            _list = pNode->prev;
            _list->next = nullptr;

            _head->next->prev = pNode;
            pNode->next = _head->next;
            _head->next = pNode;
            pNode->prev = _head;
        }
        pNode->display->RecordCurBounds();
        pNode->display->x = _head->display->x;
        pNode->display->y = _head->display->y;

        _head->display->RecordCurBounds();
        _head->display->x += dx * SNAKE_BODY_SIZE;
        _head->display->y += dy * SNAKE_BODY_SIZE;
        
    }

public:
    _list_t _head;
    _list_t _list;
    _size _length;
    ActionCtrler* _pActionCtrler = nullptr;
public:
    Direct direct;
    BYTE velocity;
};

#endif // !__HEAD_Snake_Snake
