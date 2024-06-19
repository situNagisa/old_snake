//==========================================================================================================
// @file	:	GameRunFactory
// @author	:	NAGISA
// @data	:	2023/1/26 20:03:23
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_GameRunFactory
#define __HEAD_GameRunFactory

#include "Library.h"
#include "Snake_Plus/ResrouceFactory.h"

#include "Snake_Plus/Snake.h"

USE_NGS_TYPE

class GameRunFactory {
public:

public:
    
    NGS_INLINE static Snake* CreateSnake() {
        auto head = ResourceFactory::CreateData_snake_head();
        auto& bd = *ResourceFactory::CreateData_snake_body();
        auto& snake = *New(new Snake(head,bd));
        return &snake;
    }
    NGS_INLINE static Food* CreateFood() {
        auto food = New(new Food(ResourceFactory::food[0]));
        return food;
    }
};

#endif // !__HEAD_GameRunFactory
