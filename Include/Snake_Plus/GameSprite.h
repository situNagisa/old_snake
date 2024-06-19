//==========================================================================================================
// @file	:	GameSprite
// @author	:	NAGISA
// @data	:	2023/1/26 16:24:07
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_GameSprite
#define __HEAD_GameSprite

#include "Snake_Plus/Library.h"

USE_NGS
USE_NGS_TYPE

class GameSprite {
public:
    NDA_DEFAULT_TYPE;
    NGS_TYPE_DEFINE(GameSprite, this);
    NGS_TYPE_DEFINE(DisplayObject, display);

public:
    NGS_INLINE
    GameSprite(__display_ref display):
        _display_o(display)
    {}
    virtual ~GameSprite() {
        Delete(&_display_o);
    }
    virtual VOID Update() {}
    //virtual VOID UpdateAnimate() {}
    
    virtual __rect_ref_cst GetBounds() = 0;

    NGS_INLINE __display_ref Display() { return _display_o; }
    NGS_INLINE __display_ref_cst Display()const { return _display_o; }

    NGS_INLINE VOID SetPosition(G_pos x, G_pos y) {
        _display_o.X() = x;
        _display_o.Y() = y;
    }
protected:
    __display_ref _display_o;
    __rect _bounds;
};

#endif // !__HEAD_GameSprite
