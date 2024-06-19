//==========================================================================================================
// @file	:	GameEventCtrl
// @author	:	NAGISA
// @data	:	2023/1/26 16:53:01
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_GameEvent
#define __HEAD_GameEvent

#include "Snake_Plus/Library.h"

USE_NGS

struct GameParam : public Object {

};

struct GameEvent : public Event {
    NGS_TYPE_DEFINE(GameParam, param);

    NGS_INLINE static __type
        STAGE_CHANGE = L"StageChange",
        DIRECT_DOWN = L"DirectDown",
        DIRECT_UP = L"DirectUP",
        BUTTON_PRESS = L"ButtonPress",
        BUTTON_RELEASE = L"ButtonRelease"

        ;
    __param_ptr GetParam() { return reinterpret_cast<__param_ptr>(param); }
};

class GameEventCtrl : public EventDispatcher , public Singleton<GameEventCtrl>{
public:
    NGS_TYPE_DEFINE(EventDispatcher, base);
    NGS_TYPE_DEFINE(GameEvent, evt);
    NGS_TYPE_DEFINE(__evt::__param, param);
public:
    using __base::Dispatch;
    _TYP VOID Dispatch(__evt::__type type,_TYP PVOID param) {
        GameEvent evt(type);
        evt.param = param;
        __base::Dispatch(evt);
    }
};

#endif // !__HEAD_GameEvent
