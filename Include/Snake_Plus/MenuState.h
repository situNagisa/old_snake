//==========================================================================================================
// @file	:	MenuState
// @author	:	NAGISA
// @data	:	2023/1/26 16:29:08
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_MenuState
#define __HEAD_MenuState

#include "Snake_Plus/Library.h"

#include "Snake_Plus/ResrouceFactory.h"
#include "Snake_Plus/MenuBtnGroup.h"
#include "Snake_Plus/GameConfig.h"
#include "Snake_Plus/GameInputer.h"
#include "Snake_Plus/GameUpdater.h"
#include "Snake_Plus/GameEvent.h"

USE_NGS
USE_NGS_TYPE
#include <iostream>

class MenuState final : public IStage{
public:
    NDA_DEFAULT_TYPE;
    NGS_TYPE_DEFINE(MenuState, this);
    NGS_TYPE_DEFINE(Bitmap, bitmap);
    NGS_TYPE_DEFINE(Sprite, ui);
    NGS_TYPE_DEFINE(ButtonGroup, btnGrp);
    NGS_TYPE_DEFINE(BitmapMovieClip, movie);

    static NGS_INL_CSTEXPR
        G_size MAX_BUTTON = 3;
public:
    NGS_INLINE
    MenuState()
    {
        _ui_o = New(new __ui());
        _btnGroup_o = New(new ButtonGroup(GameEventCtrl::I(),GameEvent::BUTTON_PRESS,GameEvent::BUTTON_RELEASE, *_ui_o));
        _btnGroup_o->start.Set(G_menu_button_start_x, G_menu_button_start_y);
        _btnGroup_o->offset.Set(G_menu_button_gap_x, G_menu_button_gap_y);
        EventListener listener(_OnButtonMove, this);
        GameEventCtrl::I().AddEventListener(GameEvent::DIRECT_DOWN, listener);
        GameEventCtrl::I().AddEventListener(GameEvent::DIRECT_UP, listener);
    }
    MenuState(__this_ref_cst other) = delete;

    ~MenuState()final override{
        GameEventCtrl::I().RemoveEventListener(GameEvent::DIRECT_DOWN, _OnButtonMove);
        GameEventCtrl::I().RemoveEventListener(GameEvent::DIRECT_UP, _OnButtonMove);
        Delete(_btnGroup_o);
        Delete(_ui_o);
    }

    __this_ref operator=(__this_ref_cst other) = delete;

    VOID Destory()final override {
        _ui_o->RemoveChild(background);
        _RemoveButton();
    }
    VOID Build()final override {
        ResourceFactory::DrawMenuBG(background.Data());
        _ui_o->AddChild(background);

        _AddButton(L" start", std::bind(&__this::_OnStartGame,this,std::placeholders::_1));
        _AddButton(L"config", std::bind(&__this::_OnSetting, this, std::placeholders::_1));
        _tween.From(20, G_menu_button_start_y);
        _btnGroup_o->Current().Hover();
    }
    VOID AfterBuild()final override;

    __display_ref Display()override { return *_ui_o; }

    VOID Update() final override{
        _tween.Update();
        _btnGroup_o->Update();
    }
private:
    static VOID _OnButtonMove(Event& e) {
        auto& self = e.CurrentTarget<__this>();
        auto btn = &self._btnGroup_o->Current();
        btn->Normal();
        if (e.type == GameEvent::DIRECT_UP)
            self._btnGroup_o->Prev();
        else if (e.type == GameEvent::DIRECT_DOWN)
            self._btnGroup_o->Next();
        btn = &self._btnGroup_o->Current();
        btn->Hover();
    }
    VOID _OnStartGame(__btnGrp::__btn_ref);
    VOID _OnSetting(__btnGrp::__btn_ref);

    VOID _AddButton(__btnGrp::__btn::__label::__text_ref_cst label, __btnGrp::callback callback) {
        __movie_ref movie = *ResourceFactory::CreateMenuButton();
        auto& button = _btnGroup_o->AddButton<G_fontConfig>(label, movie, __btnGrp::__btn::OnPress, callback);
        button.Text().X() += 3;
        button.Text().Y() += 2;
        button.Text().Matrix().Scale(0.7, 0.7);
        _tween += button.Y();
    }
    VOID _RemoveButton(){

    }
private:
    Tweens<G_float> _tween{ Cubic::EaseOut };
    __ui_ptr _ui_o = nullptr;
    __btnGrp_ptr _btnGroup_o = nullptr;
};
#endif // !__HEAD_MenuState
