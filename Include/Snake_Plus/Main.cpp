//==========================================================================================================
// @file	:	Main
// @author	:	NAGISA
// @data	:	2023/1/26 16:10:47
// @brief	:	
//==========================================================================================================

#include "Snake_Plus/GameConfig.h"

#include "N_WIN/N_WIN.h"
#include "Snake_Plus/Library.h"
#include "Snake_Plus/MainGame.h"
#include "Snake_Plus/GameInputer.h"
#include "Snake_Plus/GameUpdater.h"
#include "Snake_Plus/GameEvent.h"

#include <iostream>

USE_NGS

_TYP VOID KeyboardHandler(Event e) {
    auto& evt = *(KeyboardEvent*)&e;

    auto keycode = evt.GetParam()->KeyCode();
    switch (evt.GetParam()->message)
    {
    case KeyboardEvent::KEY_DOWN:
        if (!G_isInputKey(keycode))break;
        GameInputer::I().InputMap(keycode, TRUE);
        switch (keycode) {
        case G_1p_input_config.up:
            GameEventCtrl::I().Dispatch(GameEvent::DIRECT_UP, nullptr);
            break;
        case G_1p_input_config.down:
            GameEventCtrl::I().Dispatch(GameEvent::DIRECT_DOWN, nullptr);
            break;
        case G_1p_input_config.select:
            GameEventCtrl::I().Dispatch(GameEvent::BUTTON_PRESS,nullptr);
            break;
        }
        break;
    case KeyboardEvent::KEY_UP:
        if (!G_isInputKey(keycode))break;
        GameInputer::I().InputMap(keycode, FALSE);
        switch (keycode) {
        case G_1p_input_config.select:
            GameEventCtrl::I().Dispatch(GameEvent::BUTTON_RELEASE,nullptr);
            break;
        }
        break;
    default:
        break;
    }
    rand();
}

_TYP VOID UpdateHandler(Event e) {
    auto& evt = *(WM_Event*)&e;
    auto& param = *any_cast<W_Param*>(e.param);
    MainGame::I().RenderHandler((G_uint)param.user / 1000);
    GameUpdater::Update();

    evt.GetParam()->pWindow->Render();
}

int main() {
    auto& window = App::I().CreateWindow(L"Snake", { 300,300,GAME_WIDTH * G_scale,GAME_HEIGHT * G_scale });
    auto& stage = window.GetStage();
    Allocator::Instance()->Show();

    window.Listen(WM_Event::UPDATE, UpdateHandler);
    window.Listen(KeyboardEvent::KEY_DOWN, KeyboardHandler);
    window.Listen(KeyboardEvent::KEY_UP, KeyboardHandler);

    
    stage.Matrix().Scale(G_scale, G_scale);
    if (!MainGame::I().Initialize(stage, stage)) return -1;
    
    App::I().Update();
    Delete(&background);
    
    return 0;
}