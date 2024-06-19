//==========================================================================================================
// @file	:	SettingState
// @author	:	NAGISA
// @data	:	2023/2/19 22:35:59
// @brief	:	
//==========================================================================================================

#include "Snake_Plus/SettingState.h"
#include "Snake_Plus/MainGame.h"

VOID SettingState::_OnBack(__btnGrp::__btn_ref)
{
    MainGame::I().ChangeStage(&MainGame::GoMenu);
}
