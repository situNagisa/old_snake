//==========================================================================================================
// @file	:	GameMainLogic
// @author	:	NAGISA
// @data	:	2023/1/31 12:43:36
// @brief	:	
//==========================================================================================================

#include "Snake_Plus/GameMainLogic.h"
#include "Snake_Plus/GameCtrl.h"

VOID GameMainLogic::Initialize(__state_ref gameState)
{
    _gameState = &gameState;
}

VOID GameMainLogic::Destory()
{

}

_TYP BOOL GameMainLogic::Update()
{
    if (_snake_crash)return TRUE;
    auto& sps = _gameState->GetGameSprites();
    for (auto sp : sps) {
        sp->Update();
    }
    if (_tickCount & bit(5)) {
        _tickCount = 0;
        G_float x = G_game_map_size.x + (rand() % G_uint(G_game_map_size.width));
        G_float y = G_game_map_size.y + (rand() % G_uint(G_game_map_size.height));
        GameCtrl::I().AddFood(x, y,rand() % 3 + 1);
    }
    ++_tickCount;
    return FALSE;
}

VOID GameMainLogic::UpdateAnimate()
{
    return VOID();
}

BOOL GameMainLogic::_CheckSnakeCallback(__snake_ref snake)
{
    __rect rect = snake.GetBounds();
    BOOL isCrash = FALSE;
    isCrash |= !G_game_map_size.Contain(rect);

    auto& sps = _gameState->GetGameSprites();
    for (auto sp : sps) {
        auto&& intersect = sp->GetBounds() & rect;
        if (!intersect)continue;
        switch (SizeOf(sp))
        {
            case sizeof(Snake) :
            {
                if (!G_game_snake_check_self && sp == &snake)break;
                auto& s = *reinterpret_cast<Snake*>(sp);
                isCrash |= _CheckSnakeTouchSelfCallback(s, s);
                /*if (GameCtrl::I().Is2PMode()) {
                    auto& target = (sp == GameCtrl::I().P1() ? *GameCtrl::I().P2() : *GameCtrl::I().P1());
                    isCrash |= _CheckSnakeTouchSelfCallback(s, target);
                }*/
            }
            break;
            case sizeof(Food) :
            {
                auto& food = *reinterpret_cast<Food*>(sp);
                snake.Eat(food);
                food.BeEaten(snake);
            }
            break;
        }
    }
    if (!isCrash)return FALSE;

    return _snake_crash = TRUE;
}

_TYP BOOL GameMainLogic::_CheckSnakeTouchSelfCallback(__snake_ref snake,__snake_ref target)
{
    if (snake.Nodes().size() < target.Nodes().size())return FALSE;
    auto& nodes = target.Nodes();
    auto& head = *snake.Nodes().front();
    auto rect = head.Bounds();
    rect.x += head.X();
    rect.y += head.Y();
    for (auto i : nodes) {
        if (i == nodes.front())continue;
        G_vector center = { i->X() + i->Width() / 2 , i->Y() + i->Height() / 2 };
        if (!rect.Contain(center))continue;
        return TRUE;
    }
    return FALSE;
}
