//==========================================================================================================
// @file	:	Dialog_Module
// @author	:	NAGISA
// @data	:	2023/2/20 12:31:09
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Dialog_Module
#define __HEAD_Dialog_Module

#include "NGS/NGS.h"
#include "NDA/NDA.h"
#include "NGF/ButtonGroup.h"

NGS_BEGIN

template<class FontMessage>
struct DialogDef
{
    NDA_DEFAULT_TYPE;
    NGS_TYPE_DEFINE(TextFieldBase, textf);
    NGS_TYPE_DEFINE(__textf::__text, text);

    ButtonGroupDef btnGrpConfig;
    __text_ref_cst title;
    
    __num title_startX = 0;
    __num title_startY = 0;

    __num btn_startX = 0;
    __num btn_startY = 0;
    __num btn_gapX = 0;
    __num btn_gapY = 0;
};

class Dialog : public Sprite {
public:
    NGS_TYPE_DEFINE(Dialog, this);
    NGS_TYPE_DEFINE(TextFieldBase, textf);
    NGS_TYPE_DEFINE(__textf::__text, text);
    NGS_TYPE_DEFINE(ButtonGroup, btnGrp);
    NGS_TYPE_DEFINE(ButtonGroupDef, btnGrpDef);

public:
    template<class FontMessage>
    Dialog(DialogDef<FontMessage> config):
        _title_o(New(new TextField < FontMessage>(config.title))),
        _btns_o(
            New(new __btnGrp(
                config.btnGrpConfig.dispatcher,
                config.btnGrpConfig.pressType,
                config.btnGrpConfig.releaseType,
                *this
            ))
        )
    {
        _title_o->X() = config.title_startX;
        _title_o->Y() = config.title_startY;
        AddChild(*_title_o);
        _title_o->LevelCenter(TRUE);
        _title_o->VerticalCenter(TRUE);

        _btns_o->start.x = config.btn_startX;
        _btns_o->start.y = config.btn_startY;
        _btns_o->offset.x = config.btn_gapX;
        _btns_o->offset.y = config.btn_gapY;
    }

    ~Dialog() {
        RemoveChildren();
        Delete(_title_o);
        Delete(_btns_o);
    }
    
    NGS_GET_REF(Title, *_title_o);
    NGS_GET_REF(BtnGroup, *_btns_o);
    
    _TYP VOID Update() {
        _btns_o->Update();
    }
private:

private:
    __textf_ptr _title_o = nullptr;
    __btnGrp_ptr _btns_o = nullptr;
};

NGS_END

#endif // !__HEAD_Dialog_Module
