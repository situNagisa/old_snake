//==========================================================================================================
// @file	:	SettingState
// @author	:	NAGISA
// @data	:	2023/2/16 0:13:45
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_SettingState
#define __HEAD_SettingState

#include "Snake_Plus/Library.h"
#include "Snake_Plus/ResrouceFactory.h"
#include "Snake_Plus/GameEvent.h"

class SettingState : public IStage, public Sprite {
public:
    NGS_TYPE_DEFINE(SettingState, this);
    NGS_TYPE_DEFINE(ButtonGroup, btnGrp);
    NGS_TYPE_DEFINE(BitmapMovieClip, movie);

public:
    SettingState() {
        _btnGroup_o = New(new ButtonGroup(GameEventCtrl::I(), GameEvent::BUTTON_PRESS, GameEvent::BUTTON_RELEASE, *this));
        _btnGroup_o->start.Set(G_setting_button_start_x, G_setting_button_start_y);
        _btnGroup_o->offset.Set(G_setting_button_gap_x, G_setting_button_gap_y);
        EventListener listener(_OnButtonMove, this);
        GameEventCtrl::I().AddEventListener(GameEvent::DIRECT_DOWN, listener);
        GameEventCtrl::I().AddEventListener(GameEvent::DIRECT_UP, listener);
    }
    ~SettingState()final override{
        GameEventCtrl::I().RemoveEventListener(GameEvent::DIRECT_DOWN, _OnButtonMove);
        GameEventCtrl::I().RemoveEventListener(GameEvent::DIRECT_UP, _OnButtonMove);

        Delete(_btnGroup_o);
    };

    __display_ref Display() final override { return *this; }
    /**
    * @brief 构建自身（在添加到显示列表之前）
    */
    _TYP VOID Build()final override {
        ResourceFactory::DrawMenuBG(background.Data());
        AddChild(background);

        _SetGamePlayerModeText(_AddButton(L" ", _OnGamePlayerMode));
        _SetSnakeCheckSelfText(_AddButton(L" ", _OnSnakeCheckSelf));
        _AddButton(L" back", _OnBack);
        _tween.From(30, G_setting_button_start_y);

        _btnGroup_o->Current().Hover();
    }
    /**
    * @brief 构建自身（在添加到显示列表之后）
    */
    _TYP VOID AfterBuild()final override {}

    _TYP VOID Update()final override {
        _tween.Update();
        _btnGroup_o->Update();
    }

    _TYP VOID Destory()final override {
        RemoveChild(background);
    }

private:
    static VOID _OnBack(__btnGrp::__btn_ref);
    static VOID _OnGamePlayerMode(__btnGrp::__btn_ref btn) {
        switch (G_player_mode)
        {
        case G_player_mode_e::SINGLE:
            G_player_mode = G_player_mode_e::VS_PEOPLE;
            break;
        case G_player_mode_e::VS_PEOPLE:
            G_player_mode = G_player_mode_e::SINGLE;
            break;
        }
        _SetGamePlayerModeText(btn);
    }
    static VOID _SetGamePlayerModeText(__btnGrp::__btn_ref btn) {
        switch (G_player_mode)
        {
        case G_player_mode_e::VS_PEOPLE:
            btn.Text().Text(L" 2P     mode");
            break;
        case G_player_mode_e::SINGLE:
            btn.Text().Text(L" signle mode");
            break;
        }
    }
    static VOID _OnSnakeCheckSelf(__btnGrp::__btn_ref btn) {
        G_game_snake_check_self = !G_game_snake_check_self;
        _SetSnakeCheckSelfText(btn);
    }
    static VOID _SetSnakeCheckSelfText(__btnGrp::__btn_ref btn) {
        switch (G_game_snake_check_self)
        {
        case TRUE:
            btn.Text().Text(L" check self:T");
            break;
        case FALSE:
            btn.Text().Text(L" check self:F");
            break;
        }
    }

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

    __btnGrp::__btn_ref _AddButton(__btnGrp::__btn::__label::__text_ref_cst label, __btnGrp::callback callback) {
        __movie_ref movie = *ResourceFactory::CreateSettingButton();
        auto& button = _btnGroup_o->AddButton<G_fontConfig>(label, movie, __btnGrp::__btn::OnPress, callback);
        button.Text().X() += 3;
        button.Text().Y() += 2;
        button.Text().Matrix().Scale(0.7, 0.7);
        _tween += button.Y();
        return button;
    }
private:
    Tweens<G_float> _tween{ Cubic::EaseOut };
    __btnGrp_ptr _btnGroup_o = nullptr;
};

#endif // !__HEAD_SettingState
