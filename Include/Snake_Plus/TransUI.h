//==========================================================================================================
// @file	:	TransUI
// @author	:	NAGISA
// @data	:	2023/3/2 16:34:48
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_TransUI
#define __HEAD_TransUI

#include "Snake_Plus/Library.h"
#include "Snake_Plus/ResrouceFactory.h"

class TransUI :public _NGS Object,public _NGS Singleton<TransUI>{
public:
    NDA_DEFAULT_TYPE;
    NGS_TYPE_DEFINE(_NGS DisplayObject, display);
    NGS_INL_CSTEXPR static auto
        F_IS_FAD_IN = bit(0),
        F_IS_FAD_OUT = bit(1)
        ;
public:
    TransUI():
        _ui(ResourceFactory::CreateTrans())
    {
        _ui->Visible(FALSE);
        _ui->X() = 0;
        _tween.Stop();
        _tween += _ui->X();
    }
    /*_TYP VOID Initialize(__display_ptr ui) {
        _ui = ui;
        _ui->Visible(FALSE);
        _ui->X() = 0;
        _tween.Stop();
        _tween += _ui->X();
    }*/

    __display_ref Display() { return *_ui; }
    __display_ref_cst Display()const { return *_ui; }

    _TYP VOID Update() {
        _tween.Update();
        if (!IsFading())_ui->Visible(FALSE);
    }
    
    _TYP VOID FadIn() {
        _ui->Visible(TRUE);
        _ui->X() = 0;
        _ui->Resize();
        _tween.From(5, _ui->Width());
        IsFadIn(TRUE);
        IsFadOut(FALSE);
    }
    _TYP VOID FadOut() {
        _ui->Visible(TRUE);
        _ui->X() = 0;
        _tween.To(5, -_ui->Width());
        IsFadIn(FALSE);
        IsFadOut(TRUE);
    }
    _TYP BOOL IsFading()const { return !_tween.IsPlayEnd(); }

    NGS_FLAG(IsFadIn, _flag, F_IS_FAD_IN);
    NGS_FLAG(IsFadOut, _flag, F_IS_FAD_OUT);
private:

private:
    _NGS Tweens<G_float> _tween{ _NGS Cubic::EaseOut };
    __display_ptr _ui = nullptr;
    _TYP FLAG _flag = 0;
};

#endif // !__HEAD_TransUI
