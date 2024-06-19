//==========================================================================================================
// @file	:	MainGame
// @author	:	NAGISA
// @data	:	2023/1/26 16:19:45
// @brief	:	
//==========================================================================================================

#include "Snake_Plus/GameSate.h"
#include "Snake_Plus/GameCtrl.h"

VOID GameState::Destory() {
    GameCtrl::I().Destory();
    _ui_o->RemoveChild(background);
}

VOID GameState::Build() {
    _ui_o = New(new __ui());

    ResourceFactory::DrawGameBG(background.Data());

    _ui_o->AddChild(background);

    GameCtrl::I().Initialize(this);
}

VOID GameState::AfterBuild()
{
    return VOID();
}

VOID GameState::Update()
{
    GameCtrl::I().Update();
}
