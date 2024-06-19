//==========================================================================================================
// @file	:	MovieClip_Module
// @author	:	NAGISA
// @data	:	2023/1/30 22:05:28
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_MovieClip_Module
#define __HEAD_MovieClip_Module

#include "NGS/NGS.h"
#include "NDA/Sprite.h"

NGS_BEGIN

/**
* @brief 影片剪辑，既有容器特性，也有播放特性，支持影片剪辑嵌套
*/
class MovieClip :public Sprite, public Movie {
public:
    NDA_DEFAULT_TYPE;
    NGS_TYPE_DEFINE(MovieClip, this);
    NGS_TYPE_DEFINE(std::vector<DisplayObject*>*, frame);
    NGS_TYPE_DEFINE(Movie, ctrl);


public:
    MovieClip() = default;
    MovieClip(__frame_ptr pData,__size totalFrames):
        __ctrl(totalFrames),
        _frames(pData)
    {}
    MovieClip(__this_ref_cst) = default;

    _TYP VOID Update()final override {
        __ctrl::Update();
        _UpdateCurFrame();
    }
private:
    _TYP VOID _UpdateCurFrame() {
        auto cur = _frames[CurrentFrame() - 1];
        if (cur == _current)return;
        RemoveChildren();
        if ((_current = cur) == nullptr)return;
        auto& frame = *cur;
        for (_TYP SIZE_T32 i = 0; i < frame.size(); i++)
            AddChild(*frame[i]);
    }
private:
    __frame _current = nullptr;
    __frame_ptr _frames = nullptr;
};

/**
* @brief 位图剪辑，不可用作容器，具有播放特性与位图特性，虽然相较于影片剪辑灵活度相对较低，但效率更高。
* @brief 推荐优先使用位图剪辑以节省资源
* 
*/
class BitmapMovieClip : public Bitmap,public Movie{
public:
    NDA_DEFAULT_TYPE;
    NGS_TYPE_DEFINE(BitmapMovieClip, this);
    NGS_TYPE_DEFINE(BitmapData, frame);
    NGS_TYPE_DEFINE(Movie, ctrl);

public:
    BitmapMovieClip() = default;
    BitmapMovieClip(__frame_ref pData) :
        Bitmap(pData),
        _frames(&pData)
    {}
    BitmapMovieClip(__frame_ptr pData, __size totalFrames) :
        Bitmap(pData[0]),
        __ctrl(totalFrames),
        _frames(pData)
    {}
    BitmapMovieClip(__this_ref_cst) = default;


    _TYP VOID Update() final override{
        __ctrl::Update();
        _UpdateCurFrame();
    }
private:
    _TYP VOID _UpdateCurFrame() {
        Resize(TRUE);
        Redraw(TRUE);
        auto cur = _frames + CurrentFrame() - 1;
        if (cur == _current)return;
        if ((_current = cur) != nullptr)Data(*_current);
    }
private:
    __frame_ptr _current = nullptr;
    __frame_ptr _frames = nullptr;

};

NGS_END

#endif // !__HEAD_MovieClip_Module
