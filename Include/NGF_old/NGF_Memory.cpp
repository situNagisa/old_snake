//==========================================================================================================
// @file	:	NGF_Memory
// @author	:	NAGISA
// @data	:	2022/12/24 11:02:31
// @brief	:	
//==========================================================================================================


#include "NGF/NGF_Memory.h"
#include <memory>
#include <iostream>

#define NGF_IS_SHOW_ALLOCATE_MESSAGE FALSE

NGF_BEGIN

SIZE_T NGF_SizeOf(PVOID block) {
	return _msize(block);
}

NGF_MemoryAllocator::NGF_MemoryAllocator()
{
}

NGF_MemoryAllocator::~NGF_MemoryAllocator()
{
#ifdef _DEBUG
	_allocBytes = _freeBytes = 0;
#endif // _DEBUG
}

PVOID NGF_MemoryAllocator::Allocate(SIZE_T size)
{
	PVOID block = malloc(size);
	
#ifdef _DEBUG

	_map[block] = size;
	_allocBytes += size;

#endif // _DEBUG	

#if NGF_IS_SHOW_ALLOCATE_MESSAGE
	std::cout << "申请" << size << " bytes内存，地址：" << block << std::endl;

#endif // NGF_IS_SHOW_ALLOCATE_MESSAGE

	return block;
}
VOID NGF_MemoryAllocator::Free(PVOID block)
{
#ifdef _DEBUG

	SIZE_T size = NGF_SizeOf(block);

	Assert_Dynamic(_map.contains(block), TEXT("ERROR！正在释放未分配的内存"));
	Assert_Dynamic(_map[block] == size, TEXT("ERROR::???,未知错误，释放的内存与记录的内存不等"));

#endif // _DEBUG

#if NGF_IS_SHOW_ALLOCATE_MESSAGE
	std::cout << "释放" << size << " bytes内存，地址：" << block << " 数据类型：" << typeid(block).name() << std::endl;

#endif // NGF_IS_SHOW_ALLOCATE_MESSAGE

	free(block);

#ifdef _DEBUG

	_map.erase(block);
	_freeBytes += size;

#endif // _DEBUG
}

NGF_END