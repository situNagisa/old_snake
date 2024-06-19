//==========================================================================================================
// @file	:	Resource
// @author	:	NAGISA
// @data	:	2023/2/15 19:37:58
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Resource
#define __HEAD_Resource

#include "Snake_Plus/Library.h"



NGS_INLINE namespace resource {
    template<_TYP FLAG F = 0>
    struct Snake_Data {
        NGS_INL_CSTEXPR static auto flag = F;
        _TYP SIZE_T16 width = 0;
        _TYP SIZE_T16 height = 0;
        _TYP PBYTE data = nullptr;
    };

    //========================================
    // 
    //========================================
    NGS_INLINE static _TYP BYTE mode_menu_snake[] = {
    #include "data_menu_snake.h"
    };
    NGS_INLINE Snake_Data<_NGS Encoder::BYTE_INVERSE> data_menu_snake = {
        .width = 107,
        .height = 84,
        .data = mode_menu_snake
    };
    //========================================
    // 
    //========================================
    NGS_INLINE static _TYP BYTE mode_snake_tail[] = {
    #include "data_snake1.h"
    };
    NGS_INLINE Snake_Data<_NGS Encoder::BYTE_INVERSE> data_snake_tail = {
        .width = 5,
        .height = 5,
        .data = mode_snake_tail
    };
    //========================================
    // 
    //========================================
    NGS_INLINE static _TYP BYTE mode_snake_body[] = {
    #include "data_snake2.h"
    };
    NGS_INLINE Snake_Data<_NGS Encoder::BYTE_INVERSE> data_snake_body = {
        .width = 5,
        .height = 5,
        .data = mode_snake_body
    };
    //========================================
    // 
    //========================================
    NGS_INLINE static _TYP BYTE mode_snake_head[] = {
    #include "data_snake3.h"
    };
    NGS_INLINE Snake_Data<_NGS Encoder::BYTE_INVERSE> data_snake_head = {
        .width = 5,
        .height = 5,
        .data = mode_snake_head
    };
    //========================================
    // 
    //========================================
    NGS_INLINE static _TYP BYTE mode_start[] = {
    #include "data_start.h"
    };
    NGS_INLINE Snake_Data<_NGS Encoder::IS_BIT | _NGS Encoder::IS_VERTICAL> data_start = {
        .width = 30,
        .height = 8,
        .data = mode_start
    };
    //========================================
    // 
    //========================================
    NGS_INLINE static _TYP BYTE mode_setting[] = {
    #include "data_setting.h"
    };
    NGS_INLINE Snake_Data<_NGS Encoder::IS_BIT | _NGS Encoder::IS_VERTICAL> data_setting = {
        .width = 33,
        .height = 8,
        .data = mode_setting
    };
    //========================================
    // 
    //========================================

    template<_TYP FLAG flag>
    NGS_INLINE static _TYP VOID InitSnakeData(Snake_Data<flag>& config) {
        _NGS Encoder::RGB_ModelTrans<_TYP RGB15, flag>(config.data, config.width, config.height);
    }
    template<_TYP FLAG flag>
    NGS_INLINE static _TYP VOID InitSnakeFont(Snake_Data<flag>& config) {
        _NGS Encoder::Font_ModelTrans<_TYP BYTE, flag>(config.data, config.width, config.height);
    }
    NGS_INLINE _TYP VOID Initialize() {
        InitSnakeData(data_menu_snake);
        InitSnakeData(data_snake_tail);
        InitSnakeData(data_snake_body);
        InitSnakeData(data_snake_head);

        InitSnakeFont(data_start);
        InitSnakeFont(data_setting);
    }

};

#endif // !__HEAD_Resource
