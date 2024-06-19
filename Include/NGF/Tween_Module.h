//==========================================================================================================
// @file	:	Tween_Module
// @author	:	NAGISA
// @data	:	2023/2/23 13:29:12
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Tween_Module
#define __HEAD_Tween_Module

#include "NGS/NGS.h"
#include "NDA/NDA.h"

NGS_BEGIN


inline namespace ease {
    using EASE_CALLBACK = _TYP FLOAT64(*)(_TYP FLOAT64 t);

    template< _TYP SIZE_T32 POWER>
    struct PowerEase {
        NGS_INL_CSTEXPR static _TYP FLOAT64 EaseIn(_TYP FLOAT64 t) {
            return ::pow(t, POWER);
        }
        NGS_INL_CSTEXPR static _TYP FLOAT64 EaseOut( _TYP FLOAT64 t) {
            return 1 - ::pow(1 - t, POWER);
        }
        NGS_INL_CSTEXPR static _TYP FLOAT64 EaseInOut(_TYP FLOAT64 t) {
            t *= 2;
            if (t <= 1) return EaseIn(t) * 0.5;
            return EaseOut(t - 1) * 0.5 + 0.5;
        }
    };
    struct Linear : PowerEase<1>{
        NGS_INL_CSTEXPR static _TYP FLOAT64 EaseNone(_TYP FLOAT64 t) {
            return t;
        }
    };
    using Quadratic = PowerEase<2>;
    using Cubic = PowerEase<3>;
    using Quartic = PowerEase<4>;
    using Quintic = PowerEase<5>;


    template<_TYP FLOAT64 S = 1.70158>
    struct Back {
        NGS_INL_CSTEXPR static _TYP FLOAT64 EaseIn(_TYP FLOAT64 t) {
            constexpr auto c3 = S + 1;

            return (c3 * t * t * t - S * t * t);
        }
        NGS_INL_CSTEXPR static _TYP FLOAT64 EaseOut(_TYP FLOAT64 t) {
            constexpr auto c3 = S + 1;

            return (1 + c3 * ::pow(t - 1, 3) + S * ::pow(t - 1, 2));
        }
        NGS_INL_CSTEXPR static _TYP FLOAT64 EaseInOut(_TYP FLOAT64 t) {
            constexpr auto c2 = S * 1.525;
            t *= 2;
            return t < 1
                ? (::pow(t, 2) * ((c2 + 1) * t - c2)) / 2
                : (::pow(t - 2, 2) * ((c2 + 1) * (t - 2) + c2) + 2) / 2;
        }
    };
};

NGS_CONCEPT



NGS_END

template<class DataType>
struct Tween {
public:
    NGS_TYPE_DEFINE(DataType, data);
public:
    Tween(__data_ref dst)
        :_cur(dst)
        , _start(_cur)
        , _delta(0)
    {}

    Tween(__data_ref dst,__data to)
        :_cur(dst)
        , _start(_cur)
        ,_delta(to - _cur)
    {}

    _TYP VOID To(__data to) {
        _start = _cur;
        _delta = to - _start;
        //_cur = _start;
    }
    _TYP VOID From(__data from) {
        _start = from;
        _delta = _cur - _start;
        _cur = _start;
    }

    _TYP VOID Update(_TYP FLOAT64 t,EASE_CALLBACK ease) {
        _cur = _start + ease(t) * _delta;
    }
private:

private:
    __data_ref _cur;
    __data _start;
    __data _delta;
};

template<typename DataType>
class Tweens : public Movie {
public:
    NGS_TYPE_DEFINE(DataType, data);
    NGS_TYPE_DEFINE(Tweens<__data>, this);
    NGS_TYPE_DEFINE(Tween<__data>, tween);

    NGS_INL_CSTEXPR static auto
        F_IS_YOYO = bit(0)
        ;
public:
    Tweens() {
        StopLoop();
    }
    Tweens(
        EASE_CALLBACK ease,
        _TYP SIZE_T32 totalFrames = 1
    ) 
        :Movie(totalFrames)
        ,_dsts()
        ,_ease(ease)
        ,_flag(0)
    {
        StopLoop();
        Stop();
    }
    __this_ref operator+=(__tween&& tween) { Add(std::forward<__tween>(tween)); return *this; }
    _TYP VOID Add(__tween&& tween) { _dsts.emplace_back(std::forward<__tween>(tween)); }

    _TYP VOID To(__size totalFrame, __data to) {
        TotalFrames(totalFrame);
        for (auto& i : _dsts)
            i.To(to);
        PlayDirect(FALSE);
        GoToAndPlay(FrameStart());
    }
    _TYP VOID From(__size totalFrame, __data from) {
        TotalFrames(totalFrame);
        for (auto& i : _dsts)
            i.From(from);
        PlayDirect(FALSE);
        GoToAndPlay(FrameStart());
    }
    NGS_GET(Ease, _ease);
    NGS_SET(Ease, _ease,EASE_CALLBACK);

    _TYP VOID Update() {
        Movie::Update();
        if (!IsPlaying())return;
        auto t = _TYP FLOAT64(CurrentFrame()) / TotalFrames();
        for (auto& i : _dsts) {
            i.Update(t, _ease);
        }
        if (IsPlayEnd()) {
            if (YoYo())PlayDirect(!IsInvertPlay());
        }
    }

    NGS_FLAG(YoYo, _flag, F_IS_YOYO);
private:

private:
    std::vector<__tween> _dsts;
    EASE_CALLBACK _ease;
    _TYP FLAG _flag;
};

NGS_END

#endif // !__HEAD_Tween_Module
