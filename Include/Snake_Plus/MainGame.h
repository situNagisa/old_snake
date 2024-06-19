//==========================================================================================================
// @file	:	MainGame
// @author	:	NAGISA
// @data	:	2023/1/26 16:17:02
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_MainGame
#define __HEAD_MainGame

#include "Snake_Plus/Library.h"

#include "Snake_Plus/MenuState.h"
#include "Snake_Plus/GameSate.h"
#include "Snake_Plus/SettingState.h"
#include "Snake_Plus/GameConfig.h"
#include "Snake_Plus/GameCtrl.h"
#include "Snake_Plus/GameEvent.h"
#include "Snake_Plus/TransUI.h"

USE_NGS_TYPE
USE_NGS


class MainGame :public Singleton<MainGame>{
public:
    NGS_TYPE_DEFINE(MainGame, this);
    NGS_TYPE_DEFINE(Sprite, sprite);
    NGS_TYPE_DEFINE(Stage, stage);
public:
    MainGame() = default;
    ~MainGame() {
        Delete(_stageCtrl_o);
    }

    _TYP BOOL Initialize(__sprite_ref root, __stage_ref stage) {
        _rootSprite_r = &root;
        _stage_r = &stage;

        _stageCtrl_o = New(new StageCtrl(*_rootSprite_r));

        ResourceFactory::Initialize();
        GameUpdater::Add(_Update);
        GameEventCtrl::I().AddEventListener(GameEvent::STAGE_CHANGE, {  _StageChangeHandler ,this});

        GoMenu();
        return TRUE;
    }
    
    VOID GoLogo() {

    }
    VOID GoMenu() {
        I()._Go<MenuState>();

        Allocator::I().Show();
    }
    VOID GoOption() {

    }
    VOID GoSetting() {
        I()._Go<SettingState>();

        Allocator::I().Show();
    }
    VOID GoGame() {
        I()._Go<GameState>();

        GameCtrl::I().StartGame();

        Allocator::I().Show();
    }
    VOID GoGameOver() {

    }

    VOID ChangeStage(VOID(__this::* nextStage)()) {
        GameEvent event(GameEvent::STAGE_CHANGE);
        event.param = any_cast<_TYP PVOID>(nextStage);
        _queue.Dispatch(event);
    }

    NGS_INLINE static _TYP BOOL RenderHandler(G_uint ms) {return ms * MainGame::I().FPS >= 1000;}
private:
    static _TYP VOID _Update() {
        auto& self = MainGame::I();
        auto& stage = self._stageCtrl_o->CurrentStage();

        GameEventCtrl::I().Dispatch(self._queue);
        if (TransUI::I().Display().Parent()) {
            self._UpdateTween();
            return;
        }
        if (self._isChangeStage) {
            self._isChangeStage = FALSE;
            return;
        }
        //self._time.Update();
        //if (!RenderHandler(self._time.DeltaCount()))return;
        stage.Update();
        //self._time.Record();
    }
    _TYP VOID _UpdateTween() {
        TransUI::I().Update();
        if (!TransUI::I().IsFading()) {
            if (TransUI::I().IsFadIn()) _ChangeState();
            else if (TransUI::I().IsFadOut()) _rootSprite_r->RemoveChild(TransUI::I().Display());
        }
    }

    static _TYP VOID _StageChangeHandler(Event& e) {
        auto& mainGame = e.CurrentTarget<__this>();
        auto& stage = mainGame._stageCtrl_o->CurrentStage();
        mainGame._rootSprite_r->AddChild(TransUI::I().Display());
        TransUI::I().FadIn();
        mainGame._goStageAfterTween = e.param;
    }

    _TYP VOID _ChangeState() {
        using callback = _TYP VOID(*)(__this_ptr);
        volatile auto cb = any_cast<callback>(_goStageAfterTween);
        _rootSprite_r->RemoveChild(TransUI::I().Display());
        cb(this);
        _rootSprite_r->AddChild(TransUI::I().Display());
        TransUI::I().FadOut();
        _isChangeStage = TRUE;
    }

    template<class State>
    NGS_INLINE VOID _Go() {
        _stageCtrl_o->GoStage(*New(new State()));
    }
public:
    G_uint FPS = 5;
    //G_uint FPS_Animate = 5;
private:
    _TYP BOOL _isChangeStage = FALSE;
    EventQueue _queue;
    StageCtrl* _stageCtrl_o = nullptr;
    __sprite_ptr _rootSprite_r = nullptr;
    __stage_ptr _stage_r = nullptr;

    _TYP PVOID _goStageAfterTween = nullptr;
};

#endif // !__HEAD_MainGame
