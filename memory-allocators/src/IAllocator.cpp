#include "..\include\IAllocator.h"

namespace MemoryManager
{
	IAllocator::IAllocator(const size_t memTotalSize) : memorySize(memTotalSize), firstAddress(0), usedMemorySize(0)
	{

	}
}


