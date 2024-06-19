//==========================================================================================================
// @file	:	NGS_Bases_Module
// @author	:	NAGISA
// @data	:	2023/2/9 0:07:51
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Bases_Module
#define __HEAD_NGS_Bases_Module

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_STL_Macro.h" 

NGS_BEGIN

template<class This>
class TypeDefined {
public:
    NGS_TYPE_DEFINE(This, this);
};

template<class Derived>
class Singleton {
public:
    static Derived& I() {
        static Derived instance;
        return instance;
    }
    static Derived* Instance() { return &I(); }
};

class DeleteCopy {
public:
    DeleteCopy() = default;
    DeleteCopy(const DeleteCopy&) = delete;
    DeleteCopy& operator=(const DeleteCopy&) = delete;
};

#ifdef _DEBUG

class Debugger : public TypeDefined<Debugger>{
public:
    Debugger() {
        if (!_outputConstructMessage)return;
        std::cout << typeid(this).name() << ": " << _TYP PTR(this) << ": Construct" << std::endl;
    }
    Debugger(__this_ref_cst) {
        if (!_outputConstructMessage)return;
        std::cout << typeid(this).name() << ": " << _TYP PTR(this) << ": Construct Copy" << std::endl;
    }
    Debugger(__this&&) noexcept{
        if (!_outputConstructMessage)return;
        std::cout << typeid(this).name() << ": " << _TYP PTR(this) << ": Construct Move" << std::endl;
    }
    virtual ~Debugger() {
        _destoryed = TRUE;
        if (!_outputConstructMessage)return;
        std::cout << typeid(this).name() << ": " << _TYP PTR(this) << ": Destory" << std::endl;
    }
private:
    _TYP BOOL _destoryed = FALSE;
    _TYP BOOL _outputConstructMessage;
};

#endif // _DEBUG

NGS_END

#endif // !__HEAD_NGS_Bases_Module
