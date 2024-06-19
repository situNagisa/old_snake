//==========================================================================================================
// @file	:	GameUpdater
// @author	:	NAGISA
// @data	:	2023/1/26 20:16:17
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_GameUpdater
#define __HEAD_GameUpdater

#include "Snake_Plus/Library.h"

#include <functional>

class GameUpdater {
public:
    NGS_TYPE_DEFINE(std::function<_TYP VOID()>,update)

public:
    static
    _TYP VOID Update() {
        for (auto cb : _callbacks) {
            cb();
        }
    }
    static
    _TYP VOID Add(__update_ref_cst update) {
        _callbacks.push_back(update);
    }
    static
    _TYP VOID Remove(__update_ref_cst update) {
        G_uint index = 0;
        for ( index = 0; index < _callbacks.size(); index++)
            if (update == _callbacks[index])break;
        _callbacks.erase(_callbacks.begin() + index);
    }
private:
    NGS_INLINE static std::vector<__update> _callbacks = {};
};

#endif // !__HEAD_GameUpdater
