//==========================================================================================================
// @file	:	Snake_Vector
// @author	:	NAGISA
// @data	:	2023/1/19 11:28:22
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Snake_Vector
#define __HEAD_Snake_Vector

#include "NGS/NGS.h"
#include "Snake/Snake_Memory.h"

USE_NGS_TYPE

template<class _Ty,UINT16 _Size>
class Vector {
private:
    using _this                 = Vector<_Ty,_Size>;
    using _this_ptr             = _this*;
    using _this_ptr_cst         = const _this*;
    using _this_ref             = _this&;
    using _this_ref_cst         = const _this&;

    using _data_typ            = _Ty;
    using _data_typ_ptr        = _data_typ*;
    using _data_typ_ptr_cst    = const _data_typ*;
    using _data_typ_ref        = _data_typ&;
    using _data_typ_ref_cst    = const _data_typ&;

    using _size = UINT16;

public:
    Vector() = default;

    NGS_INLINE _data_typ_ref operator[](_size index) { return _data[index]; }
    NGS_INLINE _data_typ_ref_cst operator[](_size index)const { return _data[index]; }

    //懒得写左右值引用了，能用就行
    NGS_INLINE _data_typ_ref Push(_data_typ_ref_cst data) {
        _data[_length] = data;
        _length++;
        return _data[_length - 1];
    }
    //缺析构
    NGS_INLINE _data_typ Pop() {
        _length--;
        return _data[_length];
    }
    VOID Insert(_data_typ_ref_cst data,_size index) {
        if (index >= _length) {
            Push(data);
            return;
        }
        const _size rest = _length - index;
        if NGS_CONSTEXPR(sizeof(_data_typ) % 4) {
            MemoryMove(_data + index, _data + index + 1, rest);
        } else {
            //指针加速
            MemoryMove<UINT32>(reinterpret_cast<UINT32*>(_data + index), reinterpret_cast<UINT32*>(_data + index + 1), rest);
        }
        _data[index] = data;
        _length++;
    }
    _data_typ Erase(_size index) {
        if (index >= _length - 1) {
            return Pop();
        }
        _data_typ temp = _data[index];
        const _size rest = _length - index - 1;
        if NGS_CONSTEXPR(sizeof(_data_typ) % 4) {
            MemoryMove(_data + index + 1, _data + index, rest);
        } else {
            //指针加速
            MemoryMove<UINT32>(reinterpret_cast<UINT32*>(_data + index + 1), reinterpret_cast<UINT32*>(_data + index), rest);
        }
        _length--;
        return temp;
    }
    //缺LastIndexOf,startIndex参数
    _size IndexOf(_data_typ_ref_cst data) const{
        for (_size i = 0; i < _length; i++)
        {
            if (_data[i] == data)return i;
        }
        return -1;
    }

    NGS_INLINE _size GetLength()const { return _length; }
    NGS_INL_CSTEXPR _size GetCapacity()const {return _Size;}

    NGS_INLINE BOOL IsFull()const { return _length == _Size; }
    NGS_INLINE BOOL IsEmpty()const { return !_length; }
private:
    _size _length = 0;
    _data_typ _data[_Size];
};
#endif // !__HEAD_Snake_Vector
