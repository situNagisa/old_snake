//==========================================================================================================
// @file	:	GameSate
// @author	:	NAGISA
// @data	:	2023/1/26 16:28:58
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_GameSate
#define __HEAD_GameSate

#include "Snake_Plus/Library.h"

#include "Snake_Plus/GameSprite.h"
#include <vector>

USE_NGS
USE_NGS_TYPE

class GameState final : public IStage {
public:
    NDA_DEFAULT_TYPE;
    NGS_TYPE_DEFINE(GameState, this);
    NGS_TYPE_DEFINE(GameSprite, gsp);
    NGS_TYPE_DEFINE(Sprite, ui);
    
public:
    GameState() = default;
    ~GameState()override {
        Delete(_ui_o);
    }

    VOID Destory()override;

    VOID Build()override;
    VOID AfterBuild()override;

    __display_ref Display() { return *_ui_o; }
    __ui_ref Container() { return *_ui_o; }

    VOID Update()final override;

    VOID AddGameSprite(__gsp_ptr gameSprite) {
        _ui_o->Redraw(TRUE);
        _ui_o->AddChild(gameSprite->Display());
        _gameSprites.push_back(gameSprite);
    }
    VOID RemoveGameSprite(__gsp_ptr gameSprite) {
        _ui_o->Redraw(TRUE);

        G_size index = 0;
        for (; index < _gameSprites.size(); index++)
            if (_gameSprites[index] == gameSprite)break;

        _gameSprites.erase(_gameSprites.begin() + index);
        _ui_o->RemoveChild(gameSprite->Display());
    }
    std::vector<__gsp_ptr>& GetGameSprites() { return _gameSprites; }
    const std::vector<__gsp_ptr>& GetGameSprites()const  { return _gameSprites; }
private:
    std::vector<__gsp_ptr> _gameSprites = {};
    __ui_ptr _ui_o = nullptr;

};
#endif // !__HEAD_GameSate
