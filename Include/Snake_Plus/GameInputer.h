//==========================================================================================================
// @file	:	GameInputer
// @author	:	NAGISA
// @data	:	2023/1/26 16:41:20
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_GameInputer
#define __HEAD_GameInputer

#include "Snake_Plus/Library.h"


class GameInputer : public Object,public Singleton<GameInputer>{
public:
    NGS_TYPE_DEFINE(GameInputer, this);
    using __map = std::map<_TYP UINT32, _TYP BOOL>;
    NGS_TYPE_DEFINE(__map, map);
public:
    _TYP BOOL Up(G_team team) {
        auto& config = team == G_team::P1 ? G_1p_input_config : G_2p_input_config;
        return _inputMap[config.up];
    }
    _TYP BOOL Left(G_team team) {
        auto& config = team == G_team::P1 ? G_1p_input_config : G_2p_input_config;
        return _inputMap[config.left];
    }
    _TYP BOOL Down(G_team team) {
        auto& config = team == G_team::P1 ? G_1p_input_config : G_2p_input_config;
        return _inputMap[config.down];
    }
    _TYP BOOL Right(G_team team) {
        auto& config = team == G_team::P1 ? G_1p_input_config : G_2p_input_config;
        return _inputMap[config.right];
    }
    _TYP BOOL Select(G_team team) {
        auto& config = team == G_team::P1 ? G_1p_input_config : G_2p_input_config;
        return _inputMap[config.select];
    }

    _TYP VOID InputMap(_TYP UINT32 keycode,_TYP BOOL value){
        _inputMap[keycode] = value;
    }
public:
    _TYP BOOL enable = TRUE;
private:
    
private:
    __map _inputMap;
};

#endif // !__HEAD_GameInputer
