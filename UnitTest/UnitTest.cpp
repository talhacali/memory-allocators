#define BOOST_TEST_MODULE MemoryAllocatorsUnitTest

#include <boost/test/unit_test.hpp>
#include "LinearAllocator.h"
#include "PoolAllocator.h"

BOOST_AUTO_TEST_SUITE(linear_allocator_suite)

class Struct1
{

public:
    Struct1(int _i1,int _i2,int _i3) : i1(_i1),i2(_i2),i3(_i3){}
    int i1;
    int i2;
    int i3;
};

BOOST_AUTO_TEST_CASE(alignment_test)
{
    MemoryManager::LinearAllocator linearAllocator(1000);

    char* c1 = (char*)linearAllocator.Allocate(12, 8);
    Struct1 *s1 = MemoryManager::Allocate<Struct1>(linearAllocator, 16,0,0,0);
    Struct1 *s2 = MemoryManager::Allocate<Struct1>(linearAllocator,0,0,0,0);
    
    size_t address_of_c1 = (size_t)c1;
    size_t address_of_s1 = (size_t)s1;
    size_t address_of_s2 = (size_t)s2;

    BOOST_CHECK(address_of_c1 % 8 == 0);
    BOOST_CHECK(address_of_s1 % 16 == 0);
    BOOST_CHECK(address_of_s2 %  __alignof(Struct1) == 0);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(pool_allocator_suite)

BOOST_AUTO_TEST_CASE(node_number_test)
{
    MemoryManager::PoolAllocator poolAllocator1(1000,10);
    MemoryManager::PoolAllocator poolAllocator2(1009, 10);

    BOOST_CHECK(poolAllocator1.GetNodeNumber() == 100);
    BOOST_CHECK(poolAllocator2.GetNodeNumber() == 100);

    BOOST_CHECK(poolAllocator1.GetNumberOfAllocs() == poolAllocator1.GetNodeNumber());
    BOOST_CHECK(poolAllocator2.GetNumberOfAllocs() == poolAllocator2.GetNodeNumber());
}

BOOST_AUTO_TEST_SUITE_END()