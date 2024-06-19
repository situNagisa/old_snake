//==========================================================================================================
// @file	:	GameCtrl
// @author	:	NAGISA
// @data	:	2023/1/26 17:13:16
// @brief	:	
//==========================================================================================================

#include "Snake_plus/GameCtrl.h"
#include "Snake_Plus/MainGame.h"

VOID GameCtrl::GameOver(){
    MainGame::I().ChangeStage(&MainGame::GoMenu);
}
