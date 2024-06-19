//==========================================================================================================
// @file	:	MenuState
// @author	:	NAGISA
// @data	:	2023/1/26 17:02:20
// @brief	:	
//==========================================================================================================

#include "Snake_Plus/MenuState.h"
#include "Snake_Plus/ResrouceFactory.h"
#include "Snake_Plus/MainGame.h"


VOID MenuState::AfterBuild()
{
    return VOID();
}

VOID MenuState::_OnStartGame(__btnGrp::__btn_ref)
{
    MainGame::I().ChangeStage(&MainGame::GoGame);
}

VOID MenuState::_OnSetting(__btnGrp::__btn_ref)
{
    MainGame::I().ChangeStage(&MainGame::GoSetting);
}
