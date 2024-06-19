//==========================================================================================================
// @file	:	Food
// @author	:	NAGISA
// @data	:	2023/1/26 16:21:15
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Food
#define __HEAD_Food

#include "Snake_plus/Library.h"

#include "Snake_plus/GameSprite.h"

USE_NGS_TYPE

class Snake;

class Food : public GameSprite {
public:
    NGS_TYPE_DEFINE(BitmapData, bitmapData);
    NGS_TYPE_DEFINE(Snake, snake);

public:
    Food(__bitmapData_ref data):
        GameSprite(*New(new Bitmap(data)))
    {}
    VOID Initialize() {
        if (_display_o.NeedResize())_display_o.Resize();
        _display_o.Matrix().Identity();
        _display_o.Matrix()
            .Scale(power, power)
            .Translate(-power * _display_o.Width()/ 2, -power * _display_o.Height()/ 2)
            ;
        _bounds = _display_o.Bounds() << _display_o.Matrix();
        _bounds.x += _display_o.X();
        _bounds.y += _display_o.Y();
    }

    VOID BeEaten(__snake_ref_cst snake);

    __rect_ref_cst GetBounds() override { return _bounds; }
public:
    G_int power = 1;
private:
    
};

#endif // !__HEAD_Food
