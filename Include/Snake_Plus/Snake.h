//==========================================================================================================
// @file	:	Snake
// @author	:	NAGISA
// @data	:	2023/1/26 16:20:53
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Snake
#define __HEAD_Snake

#include "Library.h"

#include "Snake_Plus/GameConfig.h"
#include "Snake_Plus/GameSprite.h"
#include "Snake_Plus/Food.h"
#include "Snake_Plus/GameInputer.h"

#include <stdio.h>
USE_NGS_TYPE


enum class Direct :INT8 {
    UP = -2,
    DOWN = 2,
    RIGHT = 1,
    LEFT = -1
};

class Snake : public GameSprite {
public:
    NGS_TYPE_DEFINE(Snake, this);
    NGS_TYPE_DEFINE(GameSprite, base);
    NGS_TYPE_DEFINE(Bitmap, bitmap);
    NGS_TYPE_DEFINE(__bitmap_ptr, node);
    NGS_TYPE_DEFINE(BitmapData, bitmapData);
    NGS_TYPE_DEFINE(Sprite, sprite);
    NGS_TYPE_DEFINE(Food, food);

public:
    Snake(__node head_o, __bitmapData_ref bodyData) :
        GameSprite(*New(new Sprite())),
        _bodyData_o(bodyData)
    {
        _Container().AddChild(*head_o);
        _nodes_o.push_back(head_o);
    }
    ~Snake() {
        auto& headData = _nodes_o.front()->Data();
        //auto& tailData = _nodes_o.back()->Data();
        _Container().RemoveChildren();
        Delete(&headData);
        Delete(&_bodyData_o);

        for (auto node : _nodes_o) {
            auto& data = node->Data();
            Delete(node);
        }
    }

    _TYP VOID Update()override {
        __base::Update();
        _UpdateAction();
        _UpdateMove();

        _display_o.Redraw(TRUE);
        _display_o.Resize(TRUE);
    }

    __rect_ref_cst GetBounds() override {
        _bounds = _nodes_o.front()->Bounds();
        _bounds.x += _nodes_o.front()->X() + _Container().X();
        _bounds.y += _nodes_o.front()->Y() + _Container().Y();
        return _bounds;
    }

    _TYP VOID Eat(__food_ref_cst food) {
        for (G_size i = 0; i < food.power; i++)
            AddNode();

        score += food.power * 1;
    }

    _TYP VOID AddNode() {
        auto& body = *New(new Bitmap(_bodyData_o));
        auto& prev = *_nodes_o.back();
        _nodes_o.push_back(&body);
        _Container().AddChildAt(body, 0);
        _SetBodyPosition(&prev, &body, (Direct)(-(int)direct));
        body.Resize();
        if (_nodes_o.size() >= 4 && (_nodes_o.size() & bit_max(3)) == 0x000)velocity *= 1.5;
    }
    _TYP VOID RemoveNode() {
        auto& back = *_nodes_o.back();
        _nodes_o.pop_back();
        _Container().RemoveChild(back);
    }
    std::list<__node>& Nodes() { return _nodes_o; }
    const std::list<__node>& Nodes()const { return _nodes_o; }
private:
    _TYP VOID _UpdateAction() {
        auto& inputer = GameInputer::I();
        auto isUp = inputer.Up(team);
        auto isLeft = inputer.Left(team);
        auto isDown = inputer.Down(team);
        auto isRight = inputer.Right(team);

        if (isUp && !isDown && direct != Direct::DOWN)
            direct = Direct::UP;
        else if (isDown && !isUp && direct != Direct::UP)
            direct = Direct::DOWN;
        else if (isRight && !isLeft && direct != Direct::LEFT)
            direct = Direct::RIGHT;
        else if (isLeft && !isRight && direct != Direct::RIGHT)
            direct = Direct::LEFT;
    }
    _TYP VOID _UpdateMove() {
        G_int sx, sy;
        _ParsingDirect(direct, sx, sy);
        _advance += velocity;
        if (_advance < 1) return;
        for (G_size i = 0; i < G_int(_advance); i++)
        {
            //将尾部调到头后面
            auto& back = *_nodes_o.back();
            _nodes_o.pop_back();
            auto&& it = _nodes_o.begin()++;
            it++;
            _nodes_o.insert(it, &back);
            //设置尾部在头的位置
            back.X() = _nodes_o.front()->X();
            back.Y() = _nodes_o.front()->Y();
            back.Matrix().Identity();
            back.Matrix()
                .Translate(-G_game_snake_body_width/2, -G_game_snake_body_height/2)
                .Rotate(atan2(sy, sx));
            
            //头向前移动
            auto& front = *_nodes_o.front();
            front.X() += sx * G_game_snake_body_width;
            front.Y() += sy * G_game_snake_body_height;
            front.Matrix().Identity();
            front.Matrix()
                .Translate(-G_game_snake_body_width / 2, -G_game_snake_body_height / 2)
                .Rotate(atan2(sy, sx));
            if (moveCheck(*this))return;
        }
        _advance -= G_int(_advance);
    }
    __sprite_ref _Container() { return *reinterpret_cast<__sprite_ptr>(&_display_o); }
    __sprite_ref_cst _Container()const { return *reinterpret_cast<__sprite_ptr>(&_display_o); }

    _TYP VOID _SetBodyPosition(__node refTo,__node body,Direct direct) {
        G_int sx, sy;
        _ParsingDirect(direct, sx, sy);
        body->X() = refTo->X() + G_game_snake_body_width * sx;
        body->Y() = refTo->Y() + G_game_snake_body_height * sy;
    }
    _TYP VOID _ParsingDirect(Direct direct, G_int& sx, G_int& sy) {
        switch (direct)
        {
        case Direct::UP:
            sx = 0;
            sy = -1;
            break;
        case Direct::DOWN:
            sx = 0;
            sy = 1;
            break;
        case Direct::RIGHT:
            sx = 1;
            sy = 0;
            break;
        case Direct::LEFT:
            sx = -1;
            sy = 0;
            break;
        }
    }
public:
    G_team team = G_team::P1;
    G_uint score = 0;
    Direct direct = Direct::RIGHT;
    G_float velocity = 0.3;
    std::function<_TYP BOOL(__this_ref)> moveCheck = nullptr;
private:
    G_float _advance = 0;
    __bitmapData_ref _bodyData_o;
    std::list<__node> _nodes_o;
};

#endif // !__HEAD_Snake
