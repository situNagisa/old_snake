//==========================================================================================================
// @file	:	Food
// @author	:	NAGISA
// @data	:	2023/2/5 20:03:21
// @brief	:	
//==========================================================================================================

#include "Snake_Plus/Food.h"
#include "Snake_Plus/Snake.h"
#include "Snake_Plus/GameCtrl.h"

VOID Food::BeEaten(__snake_ref_cst snake)
{
    GameCtrl::I().RemoveGameSprite(this);
}
