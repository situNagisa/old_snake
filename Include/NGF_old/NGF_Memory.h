//==========================================================================================================
// @file	:	NGF_Memory
// @author	:	NAGISA
// @data	:	2022/12/24 10:54:44
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGF_Memory
#define __HEAD_NGF_Memory

#include "NGF/NGF_Defined.h"
#include "NGF/NGF_Utils.h"
#include <map>
#include <functional>



NGF_BEGIN

class NGF_MemoryAllocator
{
	using MAP = std::map<PVOID, SIZE_T>;

public:
	static NGF_MemoryAllocator* Instance() {
		static NGF_MemoryAllocator _instance;
		return &_instance;
	}
private:
	NGF_MemoryAllocator();
public:
	~NGF_MemoryAllocator();

#ifdef _DEBUG

	UINT64 GetAllocBytes() { return _allocBytes; };
	UINT64 GetFreeBytes() { return _freeBytes; };
	UINT64 GetUsingBytes() { return GetAllocBytes() - GetFreeBytes(); }

	VOID Normalize() {
		_allocBytes -= _freeBytes;
		_freeBytes = 0;
	}
	VOID Show() {
		std::cout << "----------------------------" << std::endl;
		std::cout << "已使用 " << GetUsingBytes() << " bytes 内存" << std::endl;
		for (auto& it : _map) {
			std::cout << "地址: " << it.first << "，占用 " << it.second << "bytes 内存，类型为：" << typeid(it.first).name() << std::endl;
		}
		std::cout << "----------------------------" << std::endl;
	}
	SIZE_T SizeOf(PVOID block) {
		Assert_Dynamic(!_map.contains(block), TEXT("并没有为相关地址申请内存"));
		return _map[block];
	}

#endif // _DEBUG

	PVOID Allocate(SIZE_T);
	VOID Free(PVOID);
private:
#ifdef _DEBUG

	UINT64 _allocBytes = 0;
	UINT64 _freeBytes = 0;

	MAP _map;

#endif // _DEBUG
};

/**
* 获取一个指针所指内存的字节数
*/
SIZE_T NGF_SizeOf(PVOID block);


/**
* 申请内存，不进行初始化
*/
template<typename T>
T* NGF_Allocate(SIZE_T length = 1) {
	T* block = reinterpret_cast<T*>(NGF_MemoryAllocator::Instance()->Allocate(sizeof(T) * length));
	
	return block;
}

/**
* 申请内存，并初始化
* 
*/
template<typename T, typename... Args>
T* NGF_CAllocate(SIZE_T length = 1, Args...args) {
	
	T* block = NGF_Allocate<T>(length);

	for (SIZE_T i = 0; i < length; i++)
		new(block + i)T(args...);

	return block;
}

/**
* 释放内存，自动调用析构函数
*/
template<typename T>
VOID NGF_Free(T* block) {
	SIZE_T couts = NGF_SizeOf(block) / sizeof(T);
	for (SIZE_T i = 0; i < couts; i++)
		block[i].~T();
	NGF_MemoryAllocator::Instance()->Free(static_cast<PVOID>(block));
}

NGF_END


#endif // !__HEAD_NGF_Memory
