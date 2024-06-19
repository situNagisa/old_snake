//==========================================================================================================
// @file	:	NGS_Movie_Module
// @author	:	NAGISA
// @data	:	2023/2/16 22:38:46
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Movie_Module
#define __HEAD_NGS_Movie_Module

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_Bit.h"

NGS_BEGIN

/**
* @brief 影片剪辑的计算部分，可以使需要成为影片剪辑的类继承此类
* @brief 帧数范围为[1,?)（非0）
* @brief 请调用Update函数实时刷新影片剪辑
*/
class Movie {
public:
    NGS_DEFAULT_TYPE;

    NGS_INL_CSTEXPR const static _TYP FLAG
        IS_PLAYING = bit(0),
        IS_INVERT_PLAY = bit(1),
        IS_LOOP = bit(2)
        ;
public:
    Movie() :
        _frameCount(0),
        _currentFrame(0),
        _totalFrames(1)
    {}
    Movie(__size totalFrames) :
        _frameCount(0),
        _currentFrame(0),
        _totalFrames(totalFrames)
    {}

    virtual _TYP VOID Update() {
        if (IsPlaying()) {
            if (IsInvertPlay())
                PrevFrame();
            else
                NextFrame();
        }
        ++_frameCount;
    }

    _TYP VOID AddFrameScript();

    _TYP VOID NextFrame() {
        if (_currentFrame < TotalFrames() - 1) {
            GoTo(_currentFrame + 1 + 1);
            return;
        }
        if (IsLoop())
            GoTo(1);
        else
            Stop();
    }
    _TYP VOID PrevFrame() {
        if (_currentFrame > 0) {
            GoTo(_currentFrame + 1 - 1);
            return;
        }
        if (IsLoop())
            GoTo(TotalFrames());
        else
            Stop();
    }

    _TYP VOID Play() { Bits<TRUE>(_mc_flag, IS_PLAYING); }
    _TYP VOID Stop() { Bits<FALSE>(_mc_flag, IS_PLAYING); }
    _TYP BOOL IsPlaying()const { return Bits(_mc_flag, IS_PLAYING); }

    _TYP VOID GoTo(__size frame, _TYP BOOL isPlay) {
        GoTo(frame);
        Bits(_mc_flag, IS_PLAYING, isPlay);
    }
    template<_TYP BOOL IS_PLAY>
    _TYP VOID GoTo(__size frame) {
        GoTo(frame);
        Bits<IS_PLAY>(_mc_flag, IS_PLAYING);
    }
    _TYP VOID GoTo(__size frame) {
        _currentFrame = frame - 1;
        _frameCount = 0;
    }
    _TYP VOID GoToAndPlay(__size frame) { GoTo<TRUE>(frame); }
    _TYP VOID GoToAndStop(__size frame) { GoTo<FALSE>(frame); }

    _TYP VOID Loop() { GoTo(IsInvertPlay() ? TotalFrames() : 1); Bits<TRUE>(_mc_flag, IS_LOOP); }
    _TYP VOID StopLoop() { Bits<FALSE>(_mc_flag, IS_LOOP); }
    _TYP BOOL IsLoop()const { return Bits(_mc_flag, IS_LOOP); }

    _TYP BOOL IsInvertPlay()const { return Bits(_mc_flag, IS_INVERT_PLAY); }
    _TYP VOID PlayDirect(_TYP BOOL isInvertPlay) { Bits(_mc_flag, IS_INVERT_PLAY, isInvertPlay); }

    __size TotalFrames()const { return _totalFrames; }
    _TYP VOID TotalFrames(__size v) { _totalFrames = v; }
    __size CurrentFrame()const { return _currentFrame + 1; }
    __size FrameCount()const { return _frameCount; }

    __size FrameStart()const { return (_totalFrames - 1) * IsInvertPlay() + 1; }
    __size FrameEnd()const { return (_totalFrames - 1) * !IsInvertPlay() + 1; }

    _TYP BOOL IsPlayStart()const { return CurrentFrame() == FrameStart(); }
    _TYP BOOL IsPlayEnd()const { return CurrentFrame() == FrameEnd(); }
private:
    _TYP FLAG _mc_flag = IS_PLAYING | IS_LOOP;

    __size _frameCount;
    __size _currentFrame;
    __size _totalFrames;
};

NGS_END

#endif // !__HEAD_NGS_Movie_Module
