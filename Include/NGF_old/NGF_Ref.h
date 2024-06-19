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
 * NGF_Ref ���������ü�������Ļ��ࡣ
 * ���һ����̳��� Ref����ô�ڲ�ͬ�ĵط�������ʵ�������󽫱�ĺܼ򵥡�
 */
class NGF_Ref
{
public:
    /**
     * ���� Ref ���������Ȩ��
     *
     * �Ὣ Ref ��������ü��� +1��
     *
     * @see release, autorelease
     */
    void Retain();

    /**
     * �ͷ� Ref ���������Ȩ��
     *
     * �Ὣ Ref ��������ü��� -1��
     *
     * ������ü��������㣬������ý����ݻ�
     *
     * @see retain, autorelease
     */
    void Release();

    /**
     * ����һ֡�Զ��ͷ� Ref ���������Ȩ��
     *
     * �⽫���� �Զ��ͷ������ڴ�� ĩβ���õ����ü�����
     *
     * ������ü��������㣬������ý����ݻ١�
     *
     * @returns ������
     *
     * @see AutoreleasePool, retain, release
     */
    NGF_Ref* AutoRelease();

    /**
     * ���ü���
     *
     * @returns ���ü���
     */
    unsigned int GetReferenceCount() const;

protected:
    /**
     * ���캯��
     *
     * ���ü������ᱻ��Ϊ1
     */
    NGF_Ref();

public:
    /**
     * ��������
     */
    virtual ~NGF_Ref();

protected:
    /// ���ü���
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
 * NGF_StrictRef �����������г�Ա������ֵ��
 * ���һ����Ա������NGF_StrictRef�����õĻ�����ô�Ըó�Ա�������ڴ�����ǳ����㡣
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
    * @brief ������ã������ͷ��ڴ棩
    * 
    */
    VOID Release();
    /**
    * @brief ���ã����������ڴ棩
    *
    */
    VOID Reference(auto& point);
    /**
    * @brief ȡ���õ�ֵ
    *
    */
    auto& Value() const ;

    /**
    * @brief ���������ö���֮���ƶ�����
    * 
    */
    VOID Move(NGF_StrictRef<T,IsArray>& other);

    /**
    * @brief ��ȡ�ڲ�ָ�루����ֻ���ͷ��ڴ��ʱ����ã�
    */
    PT GetPointer() const{ return _point; }

    /**
    * @brief �ͷ�������ָ����ڴ棬���������
    */
    VOID Delete();

    T& operator[](SIZE_T index);
    const T& operator[](SIZE_T index)const;
    
    auto operator ->() const;

    operator BOOL()const { return _point != nullptr; }
    operator auto&() const {
        Assert_Dynamic(_point != nullptr, TEXT("��δ��������!"));
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
    Assert_Dynamic(_point == nullptr, TEXT("���ֶ�����Delete�ͷ��ڴ棡"));
}
template<class T, BOOL IsArray>
inline VOID NGF_StrictRef<T,IsArray>::Release()
{
    Assert_Dynamic(_point != nullptr, TEXT("NGF_StrictRef��δ�󶨱���������Delete��"));
    _point = nullptr;
}

template<class T, BOOL IsArray>
inline VOID NGF_StrictRef<T, IsArray>::Reference(auto& point) {
    Assert_Dynamic(_point == nullptr,TEXT("�������ö��󣬲����ٴ����ã�"));
    if constexpr (IsArray)
        _point = point;
    else
        _point = &point;
}

template<class T, BOOL IsArray>
inline auto& NGF_StrictRef<T, IsArray>::Value() const{
    Assert_Dynamic(_point != nullptr,TEXT("��δ��������!"));
    if constexpr (IsArray)
        return _point;
    else
        return *_point;
}

template<class T, BOOL IsArray>
inline VOID NGF_StrictRef<T, IsArray>::Move(NGF_StrictRef<T, IsArray>& other)
{
    Assert_Dynamic(_point == nullptr, TEXT("�������ö��󣬲����ٴ����ã�"));
    Assert_Dynamic(other._point != nullptr, TEXT("�����ƶ�ʧ�ܣ���������Ƿ���������"));
    _point = other._point;
    other._point = nullptr;
}

template<class T, BOOL IsArray>
inline VOID NGF_StrictRef<T, IsArray>::Delete()
{
    Assert_Dynamic(_point != nullptr, TEXT("��δ��������!"));
    if constexpr (IsArray)
        NGF_Free<T>(_point);
    else
        NGF_Free<T>(_point);
    Release();
}

template<class T, BOOL IsArray>
inline auto NGF_StrictRef<T, IsArray>::operator->() const {
    Assert_Dynamic(_point != nullptr, TEXT("��δ��������!"));
    if constexpr (IsArray)
        return &_point;
    else
        return _point;
}

template<class T, BOOL IsArray>
inline T& NGF_StrictRef<T, IsArray>::operator[](SIZE_T index) {
    Assert_Static(IsArray, TEXT("�����ò������飡"));
    return *(_point + index);
}

template<class T, BOOL IsArray>
inline const T& NGF_StrictRef<T, IsArray>::operator[](SIZE_T index) const{
    Assert_Static(IsArray, TEXT("�����ò������飡"));
    return *(_point + index);
}

NGF_END

#endif // !__HEAD_NGF_Ref
