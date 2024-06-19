//==========================================================================================================
// @file	:	Button_Module
// @author	:	NAGISA
// @data	:	2023/1/30 21:12:10
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Button_Module
#define __HEAD_Button_Module

#include "NGS/NGS.h"
#include "NDA/NDA.h"

NGS_BEGIN

template<class Derived>
class ButtonBase : public Object{
public:
    
    NGS_TYPE_DEFINE(ButtonBase, this);
    NGS_TYPE_DEFINE(EventDispatcher, dispatcher);
    NGS_TYPE_DEFINE(std::wstring, type);

public:
    ButtonBase(
        __dispatcher_ref dispatcher,
        __type_ref_cst pressType,
        __type_ref_cst releaseType
    ):
        _dispatcher(dispatcher),
        _pressType(pressType),
        _releaseType(releaseType)
    {
        _dispatcher.AddEventListener(_pressType, { _OnPress ,this });
        _dispatcher.AddEventListener(_releaseType, { _OnRelease ,this });
    }
    virtual ~ButtonBase() {
        _dispatcher.RemoveEventListener(_pressType, _OnPress);
        _dispatcher.RemoveEventListener(_releaseType, _OnRelease);
    }
private:
    static _TYP VOID _OnPress(__dispatcher::__evt e) {
        auto& self = e.CurrentTarget<Derived>();
        if (!self.enable)return;
        Derived::OnPress(e);
    }
    static _TYP VOID _OnRelease(__dispatcher::__evt e) {
        auto& self = e.CurrentTarget<Derived>();
        if (!self.enable)return;
        Derived::OnRelease(e);
    }
public:
    _TYP BOOL enable = TRUE;
protected:
    __dispatcher_ref _dispatcher;
private:
    __type_ref_cst _pressType;
    __type_ref_cst _releaseType;
};
enum class ButtonFrameLabel {
    NORMAL,
    HOVER,
    PRESS,
    RELEASE,
    UNENABLE,

    TOTALS,
};

template<class FontMessage>
struct ButtonDef
{
    NGS_TYPE_DEFINE(TextFieldBase::__text, text);
    NGS_TYPE_DEFINE(BitmapMovieClip, mc);

    __text_ref_cst text;
    __mc_ref movieclip;
};

class Button : public Sprite{
public:
    NGS_TYPE_DEFINE(Button, this);
    NGS_TYPE_DEFINE(TextFieldBase, label);
    NGS_TYPE_DEFINE(BitmapMovieClip, mc);
    using callback = std::function<_TYP VOID(__this_ref)>;
public:
    template<class FontMessage>
    Button(
        __label::__text_ref_cst text,
        __mc_ref movieclip,
        FontMessage font
    ):
        _label_o(*New(new TextField< FontMessage>(text))),
        _mc_o(movieclip)
    {
        _mc_o.Stop();
        AddChild(_mc_o);
        AddChild(_label_o);

        Normal();
    }
    template<class FontMessage>
    Button(const ButtonDef<FontMessage>& config) :
        __this(
            config.text,
            config.movieclip,
            FontMessage{}
        )
    {}

    ~Button() override{
        RemoveChildren();
        Delete(&_label_o); 
        Delete(&_mc_o);
    }
    _TYP VOID Update() { _mc_o.Update(); }

    __label_ref Text() { return _label_o; }
    __label_ref_cst Text()const { return _label_o; }

    _TYP VOID Normal() { _mc_o.GoTo((int)ButtonFrameLabel::NORMAL + 1); }
    _TYP VOID Hover() { _mc_o.GoTo((int)ButtonFrameLabel::HOVER + 1); }
    _TYP VOID Press() { _mc_o.GoTo((int)ButtonFrameLabel::PRESS + 1); }
    _TYP VOID Release() { _mc_o.GoTo((int)ButtonFrameLabel::RELEASE + 1); }
    _TYP VOID Unenable() { _mc_o.GoTo((int)ButtonFrameLabel::UNENABLE + 1); }

    static _TYP VOID OnNormal(__this_ref self) { self.Normal(); }
    static _TYP VOID OnHover(__this_ref self) { self.Hover(); }
    static _TYP VOID OnPress(__this_ref self) { self.Press(); }
    static _TYP VOID OnRelease(__this_ref self) { self.Release(); }
    static _TYP VOID OnUnenable(__this_ref self) { self.Unenable(); }
public:
    callback onPress = nullptr;
    callback onRelease = nullptr;
private:
    __label_ref _label_o;
    __mc_ref _mc_o;

};

NGS_END

#endif // !__HEAD_Button_Module
