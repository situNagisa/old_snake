//==========================================================================================================
// @file	:	StageCtrl
// @author	:	NAGISA
// @data	:	2023/1/30 20:22:05
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_StageCtrl_Module
#define __HEAD_StageCtrl_Module

#include "NGS/NGS.h"
#include "NDA/NDA.h"

NGS_BEGIN

/**
* 
* 
* @note ����˳��
* @note ���캯��
* @note Build
* @note (AddChild(IStage.Display()))
* @note AfterBuild
* @note Destory
* @note ��������
* 
* 
*/
class IStage {
public:
    NGS_TYPE_DEFINE(DisplayObject, display);
public:
    virtual ~IStage() = 0 {};

    virtual __display_ref Display() = 0;
    /**
    * @brief ������������ӵ���ʾ�б�֮ǰ��
    */
    virtual _TYP VOID Build() = 0;
    /**
    * @brief ������������ӵ���ʾ�б�֮��
    */
    virtual _TYP VOID AfterBuild() = 0;

    virtual _TYP VOID Update() {}

    virtual _TYP VOID Destory() = 0;
};

class StageCtrl {
public:
    NGS_TYPE_DEFINE(Sprite, sprite);
    NGS_TYPE_DEFINE(IStage, I_stage);

    NGS_INL_CSTEXPR static const _TYP FLAG
        SHOULD_BE_DESTORY = bit(0)
        ;
public:
    StageCtrl(__sprite_ref mainStage):
        _mainStage(mainStage),
        _current_o(nullptr)
    {}
    ~StageCtrl() {
        if (_current_o)_DestoryCurStage();
    }
    /**
    * @brief �л�������
    * @param stg �������󣬼����ӿڣ�Istage
    * @param sameChange ���л����ĳ����뵱ǰ������ͬʱ���Ƿ�ҲҪ�л�
    */
    _TYP BOOL GoStage(__I_stage_ref stage, _TYP BOOL sameChange = FALSE) {
        //if (!sameChange) {
        //    //�����жϣ������õ�RTTI������Ϊ��
        //    
        //}

        if (_current_o)_DestoryCurStage();
        _NewStage(&stage);
        return TRUE;
    }


    __I_stage_ref CurrentStage() { return *_current_o; }
    __I_stage_ref_cst CurrentStage()const { return *_current_o; }
private:
    _TYP VOID _DestoryCurStage() {
        _current_o->Destory();
        _mainStage.RemoveChild(_current_o->Display());
        Delete(_current_o);
        _current_o = nullptr;
        Allocator::I().Show();
    }
    _TYP VOID _NewStage(__I_stage_ptr newStage) {
        _current_o = newStage;
        _current_o->Build();
        _mainStage.AddChild(_current_o->Display());
        _current_o->AfterBuild();
        Allocator::I().Show();

    }
private:
    _TYP FLAG _flag = 0;
    __sprite_ref _mainStage;
    __I_stage_ptr _current_o;
};

NGS_END

#endif // !__HEAD_StageCtrl_Module
