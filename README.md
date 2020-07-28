# memory-allocators
This repository is a custom dynamic memory manager that I developed for my ECS implementation. It is easy-to-use and has linear and pool allocator. The C++ version is C++17 and I used Boost.Test for unit testing. 

## Example Usage
```C++
MemoryManager::LinearAllocator linearAllocator(1000);

char* c1 = (char*)linearAllocator.Allocate(12, 8);
Datastructure *linear1 = MemoryManager::Allocate<Datastructure>(linearAllocator, 16,0,0,0);
Datastructure *linear2 = MemoryManager::Allocate<Datastructure>(linearAllocator,0,0,0,0);

linearAllocator.Free(c1);
linearAllocator.Free(linear1);
linearAllocator.Free(linear2);

MemoryManager::PoolAllocator poolAllocator(1000,10);
Datastructure *pool1 = MemoryManager::Allocate<Datastructure>(poolAllocator, 0, 0, 0, 0);
MemoryManager::Delete<Datastructure>(poolAllocator, pool1);
```
