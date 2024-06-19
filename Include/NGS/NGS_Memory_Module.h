//==========================================================================================================
// @file	:	NGS_Memory_Module
// @author	:	NAGISA
// @data	:	2023/1/26 14:36:41
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Memory_Module
#define __HEAD_NGS_Memory_Module

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_Bases.h"
#include "NGS/NGS_STL_Macro.h"


NGS_BEGIN

class Allocator : public Singleton<Allocator> ,public TypeDefined<Allocator>
{
public:
    NGS_TYPE_DEFINE(_TYP SIZE_T32, size);
    NGS_TYPE_DEFINE(_TYP UINT64, bytes);

#ifdef _DEBUG
    NGS_TYPE_DEFINE(std::type_info, std_info);

    struct TypeInfo{
        const std::type_info* std_info = nullptr;
        __size size = 0;
    };
    NGS_TYPE_DEFINE(TypeInfo, info);
    using __map = std::map<_TYP PVOID, __info>;
#endif

private:
    friend class Singleton<__this>;
    Allocator() {};
public:

    template<typename T = _TYP BYTE>
    T* Allocate(__size count = 1) {
        auto block = reinterpret_cast<T*>(malloc(count * sizeof(T)));
        _RecordAllocate(block, count);
        return block;
    }
    _TYP VOID Free(_TYP PVOID block,__size count = 1) {
        _RecordFree(block, count);
        free(block);
    }

    template<typename T, typename... Args>
    T* Construct(Args&&...args) {
        T* block = Allocate<T>();
        new(block)T(std::forward<Args>(args)...);
        return block;
    }

    template<typename T>
    _TYP VOID Destory(T* block) {
        block->~T();
        Free(block);
    }

    template<typename T, typename... Args>
    T* ConstructArray(__size count,Args&&...args) {
        T* block = Allocate<T>(count);
        for (__size i = 0; i < count; i++)
            new(block + i)T(std::forward<Args>(args)...);
        
        return block;
    }

    template<typename T>
    _TYP VOID DestoryArray(T* block) {
        __size count = SizeOf(block) / sizeof(T);
        for (__size i = 0; i < count; i++)
            block[i].~T();
        Free(block, count);
    }

    template<typename T>
    T* New(T* block, __size count = 1) {
        _RecordAllocate(block, count);
        return block;
    }

    template<typename T>
    _TYP VOID Delete(T* block) { Destory(block); }

    template<typename T>
    _TYP VOID DeleteArray(T* block) { DestoryArray(block); }

    _TYP VOID Show() {
#ifdef _DEBUG
        std::cout << "----------------------------" << std::endl;
        std::cout << "已使用 " << _cur_used << " bytes 内存" << std::endl;
        std::cout << "相比上次增长了 " << (_TYP INT64)_cur_used - _show_record << " bytes 内存" << std::endl;
        std::cout << "程序最大占用 " << _max_used << " bytes 内存" << std::endl;
        _show_record = _cur_used;
        /*for (auto& it : _map) {
            std::cout << "地址: " << it.first << "，占用 " << it.second << "bytes 内存，类型为：" << typeid(it.first).name() << std::endl;
        }*/
        std::cout << "----------------------------" << std::endl;
#endif  //_DEBUG
    }

private:
    template<class T>
    _TYP VOID _RecordAllocate(T* block, __size count) {
#ifdef _DEBUG
        __info info;
        info.size = count * sizeof(T);
        info.std_info = &typeid(T);
        _map[block] = info;
        _cur_used += info.size;

        if (_cur_used > _max_used)_max_used = _cur_used;

        if (count == 1) {
            std::cout << "申请" << info.size << " bytes内存，地址：" << block << "  类型：" << info.std_info->name() << std::endl;
        } else {
            std::cout << "申请" << info.size << " bytes内存，地址：" << block << "  类型：" << info.std_info->name() << "[" << count << "]" << std::endl;
        }
#endif
    }
    _TYP VOID _RecordFree(_TYP PVOID block,__size count = 1) {
#ifdef _DEBUG
        __info info = _map[block];
        _map.erase(block);
        _cur_used -= info.size;

        if (count == 1) {
            std::cout << "释放" << info.size << " bytes内存，地址：" << block << "  类型：" << info.std_info->name() << std::endl;
        } else {
            std::cout << "释放" << info.size << " bytes内存，地址：" << block << "  类型：" << info.std_info->name() << "[" << count << "]" << std::endl;
        }
#endif
    }
#ifdef _DEBUG
    _TYP INT64 _show_record = 0;
    __bytes _max_used = 0;
    __bytes _cur_used = 0;

    __map _map;
#endif
};


NGS_EXPORT NGS_INLINE
_TYP VOID 
MemorySet(_TYP PVOID dst, _TYP BYTE value, _TYP SIZE_T32 size) {memset(dst, value, size);}

template<_CPT UnsignedIntegral UINT>
NGS_EXPORT NGS_CONSTEXPR
_TYP VOID
MemorySet(UINT* dst, UINT value, _TYP SIZE_T32 size) {
#pragma omp parallel for
    for (_TYP INT64 i = 0; i < size; i++)
        dst[i] = value;
}

NGS_EXPORT NGS_INLINE
_TYP VOID
MemoryCopy(_TYP PVOID dst, _TYP PCVOID src, _TYP SIZE_T32 size) { memcpy(dst, src, size); }

NGS_EXPORT NGS_INLINE
_TYP VOID 
MemoryMove(_TYP PVOID dst, _TYP PCVOID src, _TYP SIZE_T32 size) {memmove(dst, src, size);}

//实现基础逻辑，交换整形数据（最大可达八字节，即unsigned long long)
template<_CPT UnsignedIntegral UINT>
_TYP VOID
MemorySwap(UINT& a, UINT& b) {
    a ^= b;
    b ^= a;
    a ^= b;
}
//实现n个整数类型的数据交换
template<_TYP SIZE_T16 N,_CPT UnsignedIntegral UINT>
_TYP VOID
MemorySwap(UINT* a, UINT* b) {
    //可用OpenMP或模板For优化这个for循环
    for (_TYP SIZE_T16 i = 0; i < N; i++) {
        MemorySwap(a[i], b[i]);
    }
}
//同上，支持动态填写size参数，缺点是不能用For模板进行优化循环
template<_CPT UnsignedIntegral UINT>
_TYP VOID
MemorySwap(UINT* a, UINT* b,_TYP SIZE_T16 size) {
    for (_TYP SIZE_T16 i = 0; i < size; i++){
        MemorySwap(a[i], b[i]);
    }
}

//Different 不同类型约束，此次确保T不为void
//接口
template<_CPT Different<_TYP VOID> T>
NGS_EXPORT
_TYP VOID
MemorySwap(T* a, T* b) {
    NGS_CONSTEXPR auto rate = sizeof(T) / (sizeof(_TYP UINT64));
    NGS_CONSTEXPR auto modulo = sizeof(T) % (sizeof(_TYP UINT64));

    if NGS_CONSTEXPR(rate)
        //交换数据前rate * 8个字节
        MemorySwap<rate>(reinterpret_cast<_TYP PUINT64>(a), reinterpret_cast<_TYP PUINT64>(b));
    if NGS_CONSTEXPR(modulo)
        //交换剩下没交换的字节
        MemorySwap<modulo>(reinterpret_cast<_TYP PBYTE>(a), reinterpret_cast<_TYP PBYTE>(b));
}

NGS_EXPORT NGS_INLINE
_TYP VOID
ByteInverse(_TYP PBYTE p, _TYP SIZE_T16 size) {
    for (_TYP SIZE_T16 i = 0,len = size / 2; i < len; i++)
        MemorySwap(p + i, p + (size - 1 - i));
}

template<_CPT Integral T>
NGS_EXPORT NGS_INLINE
_TYP VOID
ByteInverse(T& p) { ByteInverse(_TYP PBYTE(&p), sizeof(T)); }

NGS_EXPORT NGS_INLINE
_TYP SIZE_T32
SizeOf(_TYP PVOID block) { return _msize(block); }

NGS_END

#endif // !__HEAD_NGS_Memory_Module
