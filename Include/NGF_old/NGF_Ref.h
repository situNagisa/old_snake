//==========================================================================================================
// @file	:	NGF_Ref
// @author	:	NAGISA
// @data	:	2022/12/24 10:55:06
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGF_Ref
#define __HEAD_NGF_Ref

#include "NGF/NGF_Defined.h"
#include "NGF/NGF_Memory.h"
#include "NGF/NGF_Utils.h"



NGF_BEGIN

/**
 * NGF_Ref 是用于引用计数管理的基类。
 * 如果一个类继承自 Ref，那么在不同的地方共享其实例化对象将变的很简单。
 */
class NGF_Ref
{
public:
    /**
     * 保留 Ref 对象的所有权。
     *
     * 会将 Ref 对象的引用计数 +1。
     *
     * @see release, autorelease
     */
    void Retain();

    /**
     * 释放 Ref 对象的所有权。
     *
     * 会将 Ref 对象的引用计数 -1。
     *
     * 如果引用计数减到零，则该引用将被摧毁
     *
     * @see retain, autorelease
     */
    void Release();

    /**
     * 在下一帧自动释放 Ref 对象的所有权。
     *
     * 这将减少 自动释放引用内存池 末尾引用的引用计数。
     *
     * 如果引用计数减到零，则该引用将被摧毁。
     *
     * @returns 该引用
     *
     * @see AutoreleasePool, retain, release
     */
    NGF_Ref* AutoRelease();

    /**
     * 引用计数
     *
     * @returns 引用计数
     */
    unsigned int GetReferenceCount() const;

protected:
    /**
     * 构造函数
     *
     * 引用计数将会被设为1
     */
    NGF_Ref();

public:
    /**
     * 析构函数
     */
    virtual ~NGF_Ref();

protected:
    /// 引用计数
    unsigned int _referenceCount;

    friend class AutoreleasePool;

#if CC_ENABLE_SCRIPT_BINDING
public:
    /// object id, ScriptSupport need public _ID
    unsigned int        _ID;
    /// Lua reference id
    int                 _luaID;
    /// scriptObject, support for swift
    void* _scriptObject;

    /**
     When true, it means that the object was already rooted.
     */
    bool _rooted;
#endif

    // Memory leak diagnostic data (only included when CC_REF_LEAK_DETECTION is defined and its value isn't zero)
#if CC_REF_LEAK_DETECTION
public:
    static void printLeaks();
#endif
};


/**
 * NGF_StrictRef 用于引用类中成员变量的值，
 * 如果一个成员变量是NGF_StrictRef的引用的话，那么对该成员变量的内存管理会非常方便。
 */
template<class T,BOOL IsArray>
class NGF_StrictRef {
    using PT = T*;
    using PCT = const PT;
    using RT = T&;
    using RCT = const RT;

private:
    PT _point;

public:
    NGF_StrictRef() :
        _point(nullptr)
    {

    }

    NGF_StrictRef(const NGF_StrictRef<T, IsArray>&) = delete;
    NGF_StrictRef<T,IsArray>& operator=(const NGF_StrictRef<T, IsArray>&) = delete;

    ~NGF_StrictRef();

    /**
    * @brief 解除引用（不会释放内存）
    * 
    */
    VOID Release();
    /**
    * @brief 引用（不会申请内存）
    *
    */
    VOID Reference(auto& point);
    /**
    * @brief 取引用的值
    *
    */
    auto& Value() const ;

    /**
    * @brief 在两个引用对象之间移动引用
    * 
    */
    VOID Move(NGF_StrictRef<T,IsArray>& other);

    /**
    * @brief 获取内部指针（建议只在释放内存的时候调用）
    */
    PT GetPointer() const{ return _point; }

    /**
    * @brief 释放所引用指针的内存，并解除引用
    */
    VOID Delete();

    T& operator[](SIZE_T index);
    const T& operator[](SIZE_T index)const;
    
    auto operator ->() const;

    operator BOOL()const { return _point != nullptr; }
    operator auto&() const {
        Assert_Dynamic(_point != nullptr, TEXT("还未进行引用!"));
        if constexpr (IsArray)
            return _point;
        else
            return *_point;
    }

private:

};

template<class T, BOOL IsArray>
inline NGF_StrictRef<T,IsArray>::~NGF_StrictRef()
{
    Assert_Dynamic(_point == nullptr, TEXT("请手动调用Delete释放内存！"));
}
template<class T, BOOL IsArray>
inline VOID NGF_StrictRef<T,IsArray>::Release()
{
    Assert_Dynamic(_point != nullptr, TEXT("NGF_StrictRef还未绑定变量，不可Delete！"));
    _point = nullptr;
}

template<class T, BOOL IsArray>
inline VOID NGF_StrictRef<T, IsArray>::Reference(auto& point) {
    Assert_Dynamic(_point == nullptr,TEXT("已有引用对象，不可再次引用！"));
    if constexpr (IsArray)
        _point = point;
    else
        _point = &point;
}

template<class T, BOOL IsArray>
inline auto& NGF_StrictRef<T, IsArray>::Value() const{
    Assert_Dynamic(_point != nullptr,TEXT("还未进行引用!"));
    if constexpr (IsArray)
        return _point;
    else
        return *_point;
}

template<class T, BOOL IsArray>
inline VOID NGF_StrictRef<T, IsArray>::Move(NGF_StrictRef<T, IsArray>& other)
{
    Assert_Dynamic(_point == nullptr, TEXT("已有引用对象，不可再次引用！"));
    Assert_Dynamic(other._point != nullptr, TEXT("引用移动失败，请检查参数是否已有引用"));
    _point = other._point;
    other._point = nullptr;
}

template<class T, BOOL IsArray>
inline VOID NGF_StrictRef<T, IsArray>::Delete()
{
    Assert_Dynamic(_point != nullptr, TEXT("还未进行引用!"));
    if constexpr (IsArray)
        NGF_Free<T>(_point);
    else
        NGF_Free<T>(_point);
    Release();
}

template<class T, BOOL IsArray>
inline auto NGF_StrictRef<T, IsArray>::operator->() const {
    Assert_Dynamic(_point != nullptr, TEXT("还未进行引用!"));
    if constexpr (IsArray)
        return &_point;
    else
        return _point;
}

template<class T, BOOL IsArray>
inline T& NGF_StrictRef<T, IsArray>::operator[](SIZE_T index) {
    Assert_Static(IsArray, TEXT("该引用不是数组！"));
    return *(_point + index);
}

template<class T, BOOL IsArray>
inline const T& NGF_StrictRef<T, IsArray>::operator[](SIZE_T index) const{
    Assert_Static(IsArray, TEXT("该引用不是数组！"));
    return *(_point + index);
}

NGF_END

#endif // !__HEAD_NGF_Ref
