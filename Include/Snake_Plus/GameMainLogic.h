//==========================================================================================================
// @file	:	GameMainLogic
// @author	:	NAGISA
// @data	:	2023/1/26 16:22:00
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_GameMainLogic
#define __HEAD_GameMainLogic

#include "Snake_Plus/Library.h"
#include "Snake_Plus/GameSate.h"
#include "Snake_Plus/Snake.h"

USE_NGS_TYPE

class GameMainLogic {
public:
    NGS_TYPE_DEFINE(GameMainLogic, this);
    NGS_TYPE_DEFINE(GameSprite, sp);
    NGS_TYPE_DEFINE(GameState, state);
    NGS_TYPE_DEFINE(Snake, snake);
    NGS_TYPE_DEFINE(G_rect, rect);

public:
    GameMainLogic()
    {}

    VOID Initialize(__state_ref gameState);
    VOID Destory();

    /**
    * @brief 游戏逻辑刷新
    * 
    * @return 是否结束游戏
    */
    _TYP BOOL Update();
    VOID UpdateAnimate();

    std::function <_TYP BOOL(__snake_ref)> checkSnakeCrash = std::bind(&__this::_CheckSnakeCallback,this,std::placeholders::_1);
private:
    _TYP BOOL _CheckSnakeCallback(__snake_ref snake);
    _TYP BOOL _CheckSnakeTouchSelfCallback(__snake_ref snake, __snake_ref target);
private:
    __state_ptr _gameState = nullptr;
    _TYP BOOL _snake_crash = FALSE;
    G_uint _tickCount = 0;
};


#endif // !__HEAD_GameMainLogic
