//==========================================================================================================
// @file	:	ResrouceUtil
// @author	:	NAGISA
// @data	:	2023/1/30 23:14:28
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_ResrouceUtil
#define __HEAD_ResrouceUtil

#include "Snake_Plus/Library.h"
#include "Snake_Plus/Font.h"
#include "Snake_Plus/Resource.h"

NGS_INLINE const auto GetTextFontData(_TYP CHAR8 c) {
    return ASCII_1608[c - ' '];
}

USE_NGS
USE_NGS_TYPE

class ResourceFactory {
private:
    NGS_INL_CSTEXPR static G_color
        data_food[] = {
            G_game_food_color,G_game_food_color,G_game_food_color,
            G_game_food_color,G_game_food_color,G_game_food_color,
            G_game_food_color,G_game_food_color,G_game_food_color,
        }
        ;
    NGS_INLINE static BitmapData
    _CreateBackground() {
        auto data = BitmapData(GAME_WIDTH, GAME_HEIGHT, G_game_background_color);
        //data.DrawRect(G_rgb_default::white , G_game_map_size.x, G_game_map_size.y, G_game_map_size.width, G_game_map_size.height);
        return data;
    }
public:
    static _TYP VOID DrawMenuBG(BitmapData& data) {
        data.Fill(G_rgb_default::black);
        data.DrawRect(G_rgb_default::white, G_game_map_size.x, G_game_map_size.y, G_game_map_size.width, 106);
        auto& d = *CreateData_menuSnake();
        G_matrix m{};
        m.Translate(G_menu_snake_x, G_menu_snake_y);
        data.Draw(d, m);
        Delete(&d);
    }
    static _TYP VOID DrawSettingBG(BitmapData& data) {
        DrawMenuBG(data);
    }
    static _TYP VOID DrawGameBG(BitmapData& data) {
        data.Fill(G_rgb_default::black);
        data.DrawRect(G_rgb_default::white, G_game_map_size.x, G_game_map_size.y, G_game_map_size.width, G_game_map_size.height);
    }

    NGS_INLINE static BitmapData
        game_bg = _CreateBackground(),
        menu_btns[] = {
                BitmapData(G_menu_button_width, G_menu_button_height, G_menu_button_color_normal),
                BitmapData(G_menu_button_width, G_menu_button_height, G_menu_button_color_hover),
                BitmapData(G_menu_button_width, G_menu_button_height, G_menu_button_color_press)
        },
        setting_btns[] = {
                BitmapData(G_setting_button_width, G_setting_button_height, G_menu_button_color_normal),
                BitmapData(G_setting_button_width, G_setting_button_height, G_menu_button_color_hover),
                BitmapData(G_setting_button_width, G_setting_button_height, G_menu_button_color_press)
        },
        food[] = {
            BitmapData(G_game_food_width,G_game_food_height,const_cast<G_color*>(data_food))
        }
        ;
public:
    
    static _TYP VOID Initialize() {
        resource::Initialize();

        menu_btns[0].DrawRect(G_rgb_default::white, G_menu_button_frame.x, G_menu_button_frame.y, G_menu_button_frame.width , G_menu_button_frame.height);
        menu_btns[1].DrawRect(G_rgb_default::white, G_menu_button_frame.x, G_menu_button_frame.y, G_menu_button_frame.width , G_menu_button_frame.height);
        menu_btns[2].DrawRect(G_rgb_default::white, G_menu_button_frame.x, G_menu_button_frame.y, G_menu_button_frame.width , G_menu_button_frame.height);

        setting_btns[0].DrawRect(G_rgb_default::white, G_setting_button_frame.x, G_setting_button_frame.y, G_setting_button_frame.width, G_setting_button_frame.height);
        setting_btns[1].DrawRect(G_rgb_default::white, G_setting_button_frame.x, G_setting_button_frame.y, G_setting_button_frame.width, G_setting_button_frame.height);
        setting_btns[2].DrawRect(G_rgb_default::white, G_setting_button_frame.x, G_setting_button_frame.y, G_setting_button_frame.width, G_setting_button_frame.height);

    }
    static BitmapMovieClip*
    CreateMenuButton() {
        return New(new BitmapMovieClip(menu_btns, 3));
    }
    static BitmapMovieClip*
    CreateSettingButton() {
        return New(new BitmapMovieClip(setting_btns, 3));
    }
    static Bitmap*
    CreateBackground() {
        return New(new Bitmap(game_bg));
    }
    static Bitmap* CreateTrans() {
        auto& data =* New(new BitmapData(GAME_WIDTH, GAME_HEIGHT, G_game_background_color,TRUE));
        auto& bmp = *New(new Bitmap(data));
        return &bmp;
    }

    static Bitmap* CreateData_start() {
        auto& d = resource::data_start;
        BitmapData* data = Encoder::Font<0,_TYP BYTE, G_rgb_default::white>(d.data,d.width,d.height);
        return New(new Bitmap(*data));
    }
    static Bitmap* CreateData_setting() {
        auto& d = resource::data_setting;
        BitmapData* data = Encoder::Font<0, _TYP BYTE, G_alpha, G_rgb_default::white>(d.data, d.width, d.height);
        return New(new Bitmap(*data));
    }
    static BitmapData* CreateData_menuSnake() {
        auto& d = resource::data_menu_snake;
        return New(new BitmapData(d.width, d.height, any_cast<G_rgb::type*>(d.data)));
    }
    static Bitmap* CreateData_snake_tail() {
        auto& d = resource::data_snake_tail;
        BitmapData* data = New(new BitmapData(d.width, d.height, any_cast<G_rgb::type*>(d.data)));
        return New(new Bitmap(*data));
    }
    static BitmapData* CreateData_snake_body() {
        auto& d = resource::data_snake_body;
        return New(new BitmapData(d.width, d.height, any_cast<G_rgb::type*>(d.data)));
    }
    static Bitmap* CreateData_snake_head() {
        auto& d = resource::data_snake_head;
        BitmapData* data = New(new BitmapData(d.width, d.height, any_cast<G_rgb::type*>(d.data)));
        return New(new Bitmap(*data));
    }
};

NGS_INLINE Bitmap& background = *ResourceFactory::CreateBackground();

#endif // !__HEAD_ResrouceUtil
