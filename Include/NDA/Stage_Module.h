//==========================================================================================================
// @file	:	Stage_Module
// @author	:	NAGISA
// @data	:	2023/1/27 20:15:45
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Stage_Module
#define __HEAD_Stage_Module

#include "NGS/NGS.h"
#include "NDA/DisplayObject.h"
#include "NDA/Bitmap.h"
#include "NDA/Sprite.h"

NGS_BEGIN

class Stage :public Sprite {
public:
    NGS_TYPE_DEFINE(DisplayObjectContainer, container);
    NGS_TYPE_DEFINE(DisplayObject, display);
    NGS_TYPE_DEFINE(BitmapData, bitmapdata);
    NGS_TYPE_DEFINE(Stage, this);

    static _TYP VOID Render(__this_ref stage,__bitmapdata_ref canvas) {
        _TraverseDisplayList(stage, stage.Matrix(), stage.Position(), canvas);
    }
private:
    /**
    * @brief �Ӹ�����������ȱ�����ʾ�б�������
    * 
    * @param draw_callback ���ƻص��������յ��Ĳ���Ϊ��1)������Ҫ���Ƶ���ʾ����. 2)����ʾ�������ǰ���ڵ��������ڸ��¸�����3)����ʾ�����ȫ�־��󣬷���ֵΪ���ջ��ƺ����ʾ�����ȫ��Bounds
    * @param container ָ�������������Ӹ�������ʼ������ʾ����
    * @param base_matrix �����󣨰����������ľ���
    */
    static _TYP VOID _TraverseDisplayList(
        __container_ref_cst container, 
        __matrix_ref_cst base_matrix,
        __vector_ref_cst offset,
        __bitmapdata_ref canvas
    ){
        for (__size i = 0, len = container.GetNumChildren(); i < len; ++i) {
            __display_ptr child = container[i];

            if (!child->Visible())continue;//���ö�����ʾ��ֱ������

            __vector display_off = child->Position();
            display_off <<= base_matrix;
            display_off += offset;

            __matrix&& cur_matrix = child->Matrix() << base_matrix;//����任����

            _TYP BOOL needResize = child->NeedResize();
            if (needResize)child->Resize();//����ʽˢ������

            //����
            if ((child->NeedRedraw() || needResize)) {
                if (child->Drawable()) {
                    auto t = cur_matrix;
                    t.Translate(display_off.x, display_off.y);
                    child->RefreshArea(_DrawDisplayObject(*child, child->RefreshArea(),  t, canvas));
                }
                //������Redraw��ԭ������ʱû�뵽��ô���ŵĴ�����һ֡ˢ�����������
                //child->Redraw();
            }

            if (child->IsContainer()) {
                auto p_container = reinterpret_cast<__container_ptr_cst>(child);

                _TraverseDisplayList(*p_container, cur_matrix, display_off, canvas);
            }
        }
    }
    /**
    * @brief ������ʾ����
    *
    * @param display ��Ҫ���Ƶ���ʾ����
    * @param refreshArea ����ʾ�������ǰ���ڵ��������ڸ��¸�����
    * @param matrix ����ʾ�����ȫ�־���
    * @param cavans ��������Ļ���
    * 
    * @return ���ջ��ƺ����ʾ�����ȫ��Bounds
    */
    static __rect _DrawDisplayObject(
        __display_ref_cst display, 
        __rect_ref_cst refreshArea,
        __matrix_ref_cst matrix,
        __bitmapdata_ref canvas
    ) {
        __rect_cst global_rect = display.Bounds() << matrix;
        canvas.Draw(display, global_rect ,matrix);

        return global_rect;
    }
public:
    Stage()
    {
        _SetStage(this);
    }
private:


private:
    

};

NGS_END

#endif // !__HEAD_Stage_Module
