//==========================================================================================================
// @file	:	Snake_ActionCtrler
// @author	:	NAGISA
// @data	:	2023/1/19 19:17:39
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Snake_ActionCtrler
#define __HEAD_Snake_ActionCtrler

#include "NGS/NGS.h"
#include "Snake/Snake_Direct.h"

USE_NGS_TYPE

class ActionCtrler {

public:
    ActionCtrler():
        _direct(Direct::RIGHT)
    {}
    NGS_INLINE
    Direct GetDirect()const {
        return _direct;
    }
    NGS_INLINE
    VOID SetDirect(Direct direct){
        _direct = direct;
    }

protected:
    Direct _direct;
};

#endif // !__HEAD_Snake_ActionCtrler
