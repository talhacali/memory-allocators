#pragma once
#include <cstdint>
#include <utility>
#include <cassert>

namespace MemoryManager
{

	class IAllocator
	{
	public:
		IAllocator(const size_t memTotalSize);
		const size_t memorySize;
		size_t usedMemorySize;
		void* firstAddress;
		virtual void* Allocate(const size_t size, uint8_t alignment) = 0;
		virtual void Free(void* ptr) = 0;
	};

	inline size_t CalculatePadding(size_t address, uint8_t alignment)
	{
		return (~address + 1) & (alignment - 1);
	}

	template<class T, class... Args>
	inline T* Allocate(IAllocator& allocator, size_t alignment,Args&&... args)
	{
		if (alignment == 0)
		{
			return new (allocator.Allocate(sizeof(T), __alignof(T))) T(std::forward<Args>(args)...);
		}
		else
		{
			return new (allocator.Allocate(sizeof(T), alignment)) T(std::forward<Args>(args)...);
		}
		
	}

	template<class T>
	inline void Delete(IAllocator& allocator, T* ptr)
	{
		ptr->~T();
		allocator.Free(ptr);
	}
}

