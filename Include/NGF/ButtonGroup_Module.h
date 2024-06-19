//==========================================================================================================
// @file	:	ButtonGroup_Module
// @author	:	NAGISA
// @data	:	2023/2/19 14:28:52
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_ButtonGroup_Module
#define __HEAD_ButtonGroup_Module

#include "NGS/NGS.h"
#include "NGF/Button.h"

NGS_BEGIN

struct ButtonGroupDef
{
    NGS_TYPE_DEFINE(EventDispatcher, dispatcher);
    NGS_TYPE_DEFINE(std::wstring, type);
    NGS_TYPE_DEFINE(Sprite, sprite);

    __dispatcher_ref dispatcher;
    __type_ref_cst pressType;
    __type_ref_cst releaseType;
    __sprite_ref sprite;
};

class ButtonGroup : public ButtonBase<ButtonGroup> , private DeleteCopy{
public:
    NDA_DEFAULT_TYPE;
    NGS_TYPE_DEFINE(ButtonGroup, this);
    NGS_TYPE_DEFINE(Button, btn);
    NGS_TYPE_DEFINE(Sprite, sprite);
    NGS_TYPE_DEFINE(std::vector<__btn_ptr>, btns);
    NGS_TYPE_DEFINE(ButtonBase<__this>, base);
    using callback = std::function<_TYP VOID(__btn_ref)>;

public:
    ButtonGroup(
        __dispatcher_ref dispatcher,
        __type_ref_cst pressType,
        __type_ref_cst releaseType,
        __sprite_ref sprite
    ) :
        __base(dispatcher,pressType,releaseType),
        offset(0, 0),
        start(0, 0),
        _sprite(sprite),
        _btns_o(),
        _select(0)
    {}
    ButtonGroup(const ButtonGroupDef& config):
        ButtonGroup(
            config.dispatcher,
            config.pressType,
            config.releaseType,
            config.sprite
        )
    {}

    ~ButtonGroup() {
        for (auto i : _btns_o) {
            _sprite.RemoveChild(*i);
            Delete(i);
        }
    }
    _TYP VOID Update() {
        for (auto i : _btns_o) {
            i->Update();
        }
    }
    template<class FontMessage>
    __btn_ref AddButton(
        __btn::__label::__text_ref_cst text,
        __btn::__mc_ref mc,
        callback onPress,
        callback onRelease
    ) {
        auto& btn = *New(new __btn(text, mc, FontMessage()));
        auto num = _btns_o.size();

        _btns_o.push_back(&btn);
        btn.onPress = onPress;
        btn.onRelease = onRelease;
        btn.X() = offset.x * num + start.x;
        btn.Y() = offset.y * num + start.y;
        _sprite.AddChild(btn);

        return btn;
    }
    template<class FontMessage>
    __btn_ref AddButton(
        const ButtonDef<FontMessage>& config,
        callback onPress,
        callback onRelease
    ) {
        return AddButton<FontMessage>(config.text, config.movieclip, onPress, onRelease);
    }

    __btn_ref Current() { return *_btns_o[_select]; }
    __btn_ref_cst Current()const { return *_btns_o[_select]; }

    _TYP VOID Next() {
        if (_select < _btns_o.size() - 1)_select++;
    }
    _TYP VOID Prev() {
        if (_select > 0)_select--;
    }
public:
    static _TYP VOID OnPress(__base::__dispatcher::__evt_ref e) {
        auto& self = e.CurrentTarget<__this>();
        auto& btn = self.Current();
        if(btn.onPress)btn.onPress(btn);
    }
    static _TYP VOID OnRelease(__base::__dispatcher::__evt_ref e) {
        auto& self = e.CurrentTarget<__this>();
        auto& btn = self.Current();
        if (btn.onRelease)btn.onRelease(btn);
    }
public:
    __vector offset;
    __vector start;
private:
    __sprite_ref _sprite;
    __btns _btns_o;
    __size _select;
};

NGS_END

#endif // !__HEAD_ButtonGroup_Module
