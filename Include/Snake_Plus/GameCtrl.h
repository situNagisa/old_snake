//==========================================================================================================
// @file	:	GameCtrl
// @author	:	NAGISA
// @data	:	2023/1/26 16:28:42
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_GameCtrl
#define __HEAD_GameCtrl

#include "Snake_plus/Library.h"

#include "Snake_plus/GameSate.h"
#include "Snake_plus/GameMainLogic.h"
#include "Snake_plus/GameRunFactory.h"
#include "Snake_plus/GameUpdater.h"

USE_NGS_TYPE

/**
* ÓÎÏ·Ö÷¿Ø
* 
*/
class GameCtrl : public Singleton<GameCtrl>{
public:
    NGS_TYPE_DEFINE(GameCtrl, this);
    NGS_TYPE_DEFINE(G_text, text);
    NGS_TYPE_DEFINE(GameState, sp);
    NGS_TYPE_DEFINE(GameSprite, gsp);
    NGS_TYPE_DEFINE(Snake, snake);
    NGS_TYPE_DEFINE(Food, food);
    NGS_TYPE_DEFINE(std::wstring, string);
    
    NGS_INL_CSTEXPR static _TYP FLAG
        F_IS_GAME_OVER = bit(0),
        F_2P_MODE = bit(1)
        ;
public:
    GameCtrl() = default;
    ~GameCtrl() {
        Destory();
    }
    VOID Initialize(__sp_ptr gameState) {
        _GameOver(FALSE);
        _Is2PMode(G_player_mode == G_player_mode_e::VS_PEOPLE);
        _gameOverTickCount = 0;

        _gameState = gameState;
        _InitMainLogic();
        _InitFoods();
        _InitTxt();
        
    }
    NGS_INLINE VOID Destory() {
        _DestoryTxt();
        _DestorySnake(_P1_o);
        if (Is2PMode())_DestorySnake(_P2_o);
        for (auto food : _foods_o) 
            _DestoryFood(food);

        _gameState = nullptr;

        _mainLogic_o->Destory();
        Delete(_mainLogic_o);
        _mainLogic_o = nullptr;
    }
    NGS_INLINE
    VOID StartGame() {

        _DoStartGame();
    }

    VOID Update() {
        if (_GameOver()) {
            if (_gameOverTickCount > 25) {
                GameOver();
                return;
            }
            _gameOverTickCount++;
            if ((_gameOverTickCount & bit_max(2)) == 0x00) {
                auto& display = _P1_o->Display();
                display.Visible(!display.Visible());
                display.Redraw(TRUE);
            }
            return;
        }
        if (_mainLogic_o->Update()) {
            _GameOver(TRUE);
            return;
        }
        _UpdateTxt();
    }

    VOID GameOver();

    __food_ptr AddFood(G_float x,G_float y,G_size power = 1) {
        __food_ptr food = nullptr;
        for (G_size i = 0; i < G_game_food_max; i++){
            food = _foods_o[i];
            if (!food->Display().Parent()) {
                _gameState->AddGameSprite(food);
                food->Display().X() = x;
                food->Display().Y() = y;
                food->power = power;
                food->Initialize();
                break;
            }
        }
        return food;
    }
    

    VOID RemoveGameSprite(__gsp_ptr gsp) {

        _gameState->RemoveGameSprite(gsp);
    }
    NGS_GET(P1, _P1_o);
    NGS_GET(P2, _P2_o);

    NGS_FLAG_GET(Is2PMode, _flag, F_2P_MODE);
private:
    NGS_FLAG(_GameOver, _flag, F_IS_GAME_OVER);
    NGS_FLAG_SET(_Is2PMode, _flag, F_2P_MODE);

    VOID _UpdateTxt() {
        _TYP WCHAR s[7];
        swprintf_s(s, L"scr%2d", _P1_o->score);
        _score1.assign(s);
        _score1_txt.Text(_score1);
        _score1_txt.Resize(TRUE);
        if (Is2PMode()) {
            swprintf_s(s, L"scr%2d", _P2_o->score);
            _score2.assign(s);
            _score2_txt.Text(_score2);
            _score2_txt.Resize(TRUE);
        }
    }
    VOID _DoStartGame() {
        _P1_o = _AddSnake(Direct::RIGHT);
        _P1_o->SetPosition(G_game_map_size.Left() + 30, G_game_map_size.Top() + 30);
        _P1_o->team = G_team::P1;
        if (Is2PMode()) {
            _P2_o = _AddSnake(Direct::LEFT);
            _P2_o->SetPosition(G_game_map_size.Right() - 30, G_game_map_size.Bottom() - 30);
            _P2_o->team = G_team::P2;
        }
    }

    VOID _InitMainLogic() {
        _mainLogic_o = New(new GameMainLogic());
        _mainLogic_o->Initialize(*_gameState);
    }
    VOID _InitFoods() {
        for (G_size i = 0; i < G_game_food_max; i++){
            _foods_o[i] = GameRunFactory::CreateFood();
        }
    }
    VOID _InitTxt() {
        _gameState->Container().AddChild(_score1_txt);
        _score1_txt.X() = G_txt_1p_score_pos.x;
        _score1_txt.Y() = G_txt_1p_score_pos.y;
        _score1_txt.Matrix().Identity();
        _score1_txt.Matrix().Scale(G_font_scale, G_font_scale);

        if (Is2PMode()) {
            _gameState->Container().AddChild(_score2_txt);
            _score2_txt.X() = G_txt_2p_score_pos.x;
            _score2_txt.Y() = G_txt_2p_score_pos.y;
            _score2_txt.Matrix().Identity();
            _score2_txt.Matrix().Scale(G_font_scale, G_font_scale);

        }
    }

    __snake_ptr _AddSnake(Direct direct) {
        __snake_ptr snake = GameRunFactory::CreateSnake();
        snake->direct = direct;
        snake->moveCheck = _mainLogic_o->checkSnakeCrash;

        snake->AddNode();
        snake->AddNode();
        snake->AddNode();

        _gameState->AddGameSprite(snake);

        return snake;
    }
    VOID _DestoryFood(__food_ptr food) {
        if(food->Display().Parent())RemoveGameSprite(food);
        Delete(food);
    }
    VOID _DestorySnake(__snake_ptr snake) {
        RemoveGameSprite(snake);
        Delete(snake);
    }
    VOID _DestoryTxt() {
        _gameState->Container().RemoveChild(_score1_txt);
        if(Bits(_flag,F_2P_MODE))_gameState->Container().RemoveChild(_score2_txt);
    }
private:
    G_uint _gameOverTickCount = 0;
    _TYP FLAG _flag = 0;

    __sp_ptr _gameState = nullptr;
    GameMainLogic* _mainLogic_o = nullptr;

    __snake_ptr _P1_o = nullptr;
    __snake_ptr _P2_o = nullptr;
    __food_ptr _foods_o[G_game_food_max] = {};

    __string _score1 = { 10 };
    __text _score1_txt;
    __string _score2 = { 10 };
    __text _score2_txt;
    

    NGS_INLINE static __this_ptr _instance = nullptr;
};
#endif // !__HEAD_GameCtrl
