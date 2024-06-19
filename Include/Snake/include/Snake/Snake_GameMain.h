//==========================================================================================================
// @file	:	Snake_GameMain
// @author	:	NAGISA
// @data	:	2023/1/19 20:03:39
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Snake_GameMain
#define __HEAD_Snake_GameMain

#include "NGS/NGS.h"
#include "Snake/Snake_DisplayObject.h"
#include "Snake/Snake_Snake.h"
#include "Snake/Snake_Stage.h"
#include "Snake/Snake_Bitmap.h"
#include "Snake/Snake_Vector.h"
#include "Snake/Snake_Food.h"
#include "Snake/Snake_Math.h"
#include "Snake/Snake_ActionCtrler.h"

USE_NGS_TYPE;
USE_NGS;
//USE_NGS_TYTR;

GAME_RGB data_convas[GAME_WIDTH * GAME_HEIGHT];
GAME_RGB data_bg[GAME_WIDTH * GAME_HEIGHT];
GAME_RGB data_head[SNAKE_BODY_SIZE * SNAKE_BODY_SIZE];

//{
//    0x1111,0x1111,0x1111,
//    0x1111,0x2222,0x1111,
//    0x1111,0x1111,0x1111
//};
GAME_RGB data_body[SNAKE_BODY_SIZE * SNAKE_BODY_SIZE];

//{
//    0x2222,0x2222,0x2222,
//    0x2222,0x2222,0x2222,
//    0x2222,0x2222,0x2222
//};
GAME_RGB data_food[FOOD_SIZE * FOOD_SIZE];

BitmapData bd_bg(GAME_WIDTH, GAME_HEIGHT, data_bg);
BitmapData bd_convas(GAME_WIDTH, GAME_HEIGHT, data_convas);
BitmapData bd_head(SNAKE_BODY_SIZE, SNAKE_BODY_SIZE, data_head);
BitmapData bd_body(SNAKE_BODY_SIZE, SNAKE_BODY_SIZE, data_body);
BitmapData bd_food(FOOD_SIZE, FOOD_SIZE, data_food);

class Game {
public:
    UINT32 tick = 0;

    Stage<30> stage;
    Node head;
    Node nodes[SNAKE_MAX_LENGTH];

    Snake snake;
    ActionCtrler* snakeActionCtrler = nullptr;

    Bitmap bg;
    Bitmap head_bm;
    Bitmap body_bm[SNAKE_MAX_LENGTH];

    Vector<Food, FOOD_MAX_NUM> foods;

    Rectangle GameSize = { 0,0,GAME_WIDTH,GAME_HEIGHT };

    DC dc;

public:
    Game() :
        snake(Snake(&head)),
        dc(&bd_convas)
    {

    }
    VOID Update() {
        tick++;
        snake.Update();
        if (!(tick % 10)) {
            _AddFood();
        }
        //撞墙
        auto rect = GameSize & snake.GetHead()->display->GetCurBounds();
        if (!rect || rect.Empty()) {
            //std::cout << "YOU ARE DIE!!!" << std::endl;
            while (TRUE);
        }
        //头部碰撞检测
        auto head_bounds = snake.GetHead()->display->GetCurBounds();
        for (UINT16 i = 0; i < foods.GetLength(); i++)
        {
            auto& food = foods[i];
            if (head_bounds.IsCross(food.bitmap.GetCurBounds())) {
                _SnakeEat(food);
            }
        }
    }
    VOID Init() {
        bg.SetBitmapData(&bd_bg);
        head_bm.SetBitmapData(&bd_head);

        stage.AddChild(bg);
        stage.AddChild(head_bm);

        head.display = &head_bm;

        snake.SetActionCtrler(snakeActionCtrler);
        _AddSnakeNode();
        _AddSnakeNode();
        _AddSnakeNode();
        snake.SetPosition(10, 10);
    }
    VOID Render() {
        for (UINT16 i = 0, numc = stage.GetNumChildren(); i < numc; i++)
        {
            auto& child = *stage.GetChildAt<Bitmap>(i);
            if (!child.requiredDraw)continue;
            const auto& bounds = child.GetPostBounds();
            _RefreshBackGround(bounds);
            child.Draw(dc);
        }
    }
private:

    VOID _AddFood() {
        if (foods.IsFull()) {
            _RemoveFood(foods[0]);
        }
        auto&& food = foods.Push(Food());
        food.bitmap.SetBitmapData(&bd_food);

        INT16 x = Random(GAME_WIDTH);
        INT16 y = Random(GAME_HEIGHT);

        food.SetPosition(x, y);
        stage.AddChild(food.bitmap);
    }
    VOID _RemoveFood(const Food& food) {
        _RemoveChild(food.bitmap);
        foods.Erase(foods.IndexOf(food));
    }
    //此函数应为Snake的成员函数，受限于内存申请，此将其提取到Game
    VOID _SnakeEat(Food& food) {
        for (UINT16 i = 0; i < food.power; i++)
        {
            _AddSnakeNode();
            //考虑长度达到最大的情况
            //
        }
        _RemoveFood(food);
    }
    VOID _AddSnakeNode() {
        auto pNode = nodes + snake.GetLength();
        pNode->display = (body_bm + snake.GetLength());
        pNode->display->SetBitmapData(&bd_body);
        stage.AddChild(*pNode->display);
        snake.AddNode(pNode);
    }
    VOID _RemoveSnakeNode() {
        auto pNode = snake.RemoveNode();
        _RemoveChild(*pNode->display);
    }
    VOID _RemoveChild(const DisplayObject<Bitmap>& child) {
        _RefreshBackGround(child.GetCurBounds());
        stage.RemoveChild(child);
    }
    VOID _RefreshBackGround(const Rectangle& bounds) {
        for (UINT16 y_ = 0; y_ < bounds.height; y_++)
        {
            for (UINT16 x_ = 0; x_ < bounds.width; x_++)
            {
                dc.DrawPoint(bounds.x + x_, bounds.y + y_, UINT16(bd_bg(bounds.x + x_, bounds.y + y_)));
            }
        }
    }
};

#endif // !__HEAD_Snake_GameMain
