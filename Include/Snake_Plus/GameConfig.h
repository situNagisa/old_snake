//==========================================================================================================
// @file	:	GameConfig
// @author	:	NAGISA
// @data	:	2023/1/26 16:35:52
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_GameConfig
#define __HEAD_GameConfig

#include "NGS/NGS.h"
#include "Snake_Plus/Font.h"

enum class G_player_mode_e {
    SINGLE,
    VS_PEOPLE
};

NGS_INLINE G_player_mode_e G_player_mode = G_player_mode_e::SINGLE;

using G_pos         = _TYP UINT16;
using G_size        = _TYP SIZE_T16;

using G_int         = _TYP INT16;
using G_uint        = _TYP UINT8;
using G_float       = _TYP FLOAT32;

using G_num         = _TYP UINT16;

using G_char        = char;
using G_str         = G_char*;
using G_str_cst     = const G_char*;

using G_rgb = _TYP RGB15;
using G_color = G_rgb::type;
using G_rgb_default = _NGS RGB_Default<G_rgb>;

NGS_INL_CSTEXPR auto G_alpha = G_rgb(0x00, 0x00, 0xFF, 0x00);

#include "NMath/Math.h"

using G_vector      = _NGS Vector2D<G_float>;
using G_matrix      = _NGS Matrix<G_float>;
using G_rect        = _NGS Rectangle<G_float>;

#define CUSTOM_NDA_TYPE_POS G_pos
#define CUSTOM_NDA_TYPE_SIZE G_size
#define CUSTOM_NDA_TYPE_NUM G_float
#define CUSTOM_NDA_TYPE_COLOR G_rgb

#include "NDA/NDA.h"

using G_fontConfig = _NGS FontMessage <
    ASCII_1608_Width, ASCII_1608_Height,
    _NGS Encoder::IS_VERTICAL,
    _TYP UINT16,
    G_rgb_default::white, G_alpha
>;
using G_text = _NGS TextField<G_fontConfig>;

NGS_INL_CSTEXPR const G_size GAME_WIDTH = 160;
NGS_INL_CSTEXPR const G_size GAME_HEIGHT = 128;
NGS_INLINE const G_rect GAME_SIZE = { 0,0,GAME_WIDTH,GAME_HEIGHT };

NGS_INL_CSTEXPR const auto G_scale = 1;

NGS_INL_CSTEXPR const G_uint FPS = 30;
NGS_INL_CSTEXPR const G_uint FPS_Animate = 10;


NGS_INL_CSTEXPR const auto G_menu_button_width = 41;
NGS_INL_CSTEXPR const auto G_menu_button_height = 16;
NGS_INL_CSTEXPR const auto G_menu_button_start_x = 100;
NGS_INL_CSTEXPR const auto G_menu_button_start_y = 48;
NGS_INL_CSTEXPR const auto G_menu_button_gap_x = 0;
NGS_INL_CSTEXPR const auto G_menu_button_gap_y = G_menu_button_height + 4;
NGS_INL_CSTEXPR const auto G_menu_button_color_normal = G_rgb(0x00,0x76, 0x42, 0x8A);
NGS_INL_CSTEXPR const auto G_menu_button_color_hover = G_rgb(0x00, 0x8F, 0x97, 0x43);
NGS_INL_CSTEXPR const auto G_menu_button_color_press = G_rgb(0x00, 0x6A, 0x75, 0x0A);
NGS_INL_CSTEXPR const auto G_menu_button_font_yin = G_alpha;
NGS_INL_CSTEXPR const auto G_menu_button_font_yang = G_rgb_default::white;
NGS_INL_CSTEXPR const G_rect G_menu_button_frame = { 1,1,39,14 };

NGS_INL_CSTEXPR const auto G_setting_button_width = G_menu_button_width * 2;
NGS_INL_CSTEXPR const auto G_setting_button_height = G_menu_button_height;
NGS_INL_CSTEXPR const auto G_setting_button_start_x = GAME_WIDTH / 2 - G_setting_button_width / 2;
NGS_INL_CSTEXPR const auto G_setting_button_start_y = 15;
NGS_INL_CSTEXPR const auto G_setting_button_gap_x = 0;
NGS_INL_CSTEXPR const auto G_setting_button_gap_y = G_menu_button_height + 4;
NGS_INL_CSTEXPR const G_rect G_setting_button_frame = { 1,1,79,14 };

NGS_INL_CSTEXPR auto G_menu_snake_x = 7;
NGS_INL_CSTEXPR auto G_menu_snake_y = 30;


NGS_INL_CSTEXPR const auto G_game_size_width = G_menu_button_width;
NGS_INL_CSTEXPR const auto G_game_size_height = G_menu_button_height;
NGS_INL_CSTEXPR const auto G_game_background_color = G_rgb_default::black;

NGS_INL_CSTEXPR const auto G_game_map_width = 137;
NGS_INL_CSTEXPR const auto G_game_map_height = 80;
NGS_INL_CSTEXPR const G_rect G_game_map_size = { 11 ,9 ,G_game_map_width,G_game_map_height };


NGS_INL_CSTEXPR const auto G_game_snake_body_width = 5;
NGS_INL_CSTEXPR const auto G_game_snake_body_height = 5;
NGS_INLINE auto G_game_snake_check_self = TRUE;

NGS_INL_CSTEXPR const auto G_game_food_width = 2;
NGS_INL_CSTEXPR const auto G_game_food_height = 2;
NGS_INL_CSTEXPR const auto G_game_food_color = G_rgb_default::purple;
NGS_INL_CSTEXPR const auto G_game_food_max = 4;

NGS_INL_CSTEXPR const auto G_font_scale = 0.9;
NGS_INL_CSTEXPR const auto G_font_yin = G_rgb_default::black;
NGS_INL_CSTEXPR const auto G_font_yang = G_rgb_default::white;

NGS_INLINE const G_vector G_txt_1p_score_pos = { 5,100 };
NGS_INLINE const G_vector G_txt_2p_score_pos = { 50,100 };

#include "Snake_Plus/InputConfig.h"

enum class G_team
{
    P1,
    P2
};

#ifdef WIN32 || _WIN64

NGS_INL_CSTEXPR auto G_1p_input_config = InputConfig(
    'W',
    'A',
    'S',
    'D',
    'J'
);
NGS_INL_CSTEXPR auto G_2p_input_config = InputConfig(
    0x26,
    0x25,
    0x28,
    0x27,
    0x00
);

NGS_INL_CSTEXPR _TYP BOOL G_isInputKey(_TYP UINT32 keycode) {
    return
        keycode == G_1p_input_config.up ||
        keycode == G_1p_input_config.down ||
        keycode == G_1p_input_config.left ||
        keycode == G_1p_input_config.right ||
        keycode == G_1p_input_config.select ||

        keycode == G_2p_input_config.up ||
        keycode == G_2p_input_config.down ||
        keycode == G_2p_input_config.left ||
        keycode == G_2p_input_config.right ||
        keycode == G_2p_input_config.select
        ;
}
NGS_INL_CSTEXPR const InputConfig& G_getInputConfigByTeam(G_team team) {
    switch (team)
    {
    case G_team::P1:
        return G_1p_input_config;
        break;
    case G_team::P2:
        return G_2p_input_config;
        break;
    default:
        break;
    }
}
#endif



#endif // !__HEAD_GameConfig
