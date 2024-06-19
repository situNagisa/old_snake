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
    * @brief 从根容器深度优先遍历显示列表，并绘制
    * 
    * @param draw_callback 绘制回调函数，收到的参数为：1)传入需要绘制的显示对象. 2)该显示对象绘制前所在的区域（用于更新该区域）3)该显示对象的全局矩阵，返回值为最终绘制后该显示对象的全局Bounds
    * @param container 指定根容器，将从根容器开始遍历显示对象
    * @param base_matrix 根矩阵（包含根容器的矩阵）
    */
    static _TYP VOID _TraverseDisplayList(
        __container_ref_cst container, 
        __matrix_ref_cst base_matrix,
        __vector_ref_cst offset,
        __bitmapdata_ref canvas
    ){
        for (__size i = 0, len = container.GetNumChildren(); i < len; ++i) {
            __display_ptr child = container[i];

            if (!child->Visible())continue;//若该对象不显示则直接跳过

            __vector display_off = child->Position();
            display_off <<= base_matrix;
            display_off += offset;

            __matrix&& cur_matrix = child->Matrix() << base_matrix;//矩阵变换叠加

            _TYP BOOL needResize = child->NeedResize();
            if (needResize)child->Resize();//懒汉式刷新区域

            //绘制
            if ((child->NeedRedraw() || needResize)) {
                if (child->Drawable()) {
                    auto t = cur_matrix;
                    t.Translate(display_off.x, display_off.y);
                    child->RefreshArea(_DrawDisplayObject(*child, child->RefreshArea(),  t, canvas));
                }
                //不调用Redraw的原因是暂时没想到怎么优雅的处理上一帧刷新区域的问题
                //child->Redraw();
            }

            if (child->IsContainer()) {
                auto p_container = reinterpret_cast<__container_ptr_cst>(child);

                _TraverseDisplayList(*p_container, cur_matrix, display_off, canvas);
            }
        }
    }
    /**
    * @brief 绘制显示对象
    *
    * @param display 需要绘制的显示对象
    * @param refreshArea 该显示对象绘制前所在的区域（用于更新该区域）
    * @param matrix 该显示对象的全局矩阵
    * @param cavans 绘制所需的画布
    * 
    * @return 最终绘制后该显示对象的全局Bounds
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
