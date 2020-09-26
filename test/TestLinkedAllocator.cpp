#include <cctest/cctest.h>
#include <cub/mem/LinkedAllocator.h>
#include <cub/repo/array/ArraySize.h>

USING_CUB_NS

namespace
{
    int array[] = {0, 1, 2, 3, 4};
}

FIXTURE(LinkedAllocatorTest)
{
    LinkedAllocatorTest()
    : allocator(array, MAX_ALLOC_NUM)
    {
    }

    TEST("should has free slot num when init")
    {
    	ASSERT_TRUE(allocator.isBusyListEmpty());
    	ASSERT_FALSE(allocator.isFreeListEmpty());
    }

    TEST("should alloc ok when has free slots")
    {
        for(int i = 0; i < MAX_ALLOC_NUM; i++)
        {
            const int* x = allocator.alloc();
            ASSERT_TRUE(__NOT_NULL(x));
            ASSERT_EQ(i, *x);
        }

        const int* x = allocator.alloc();
        ASSERT_TRUE(__IS_NULL(x));
    }

    TEST("should alloc ok when free slots")
    {
        for(int i = 0; i < MAX_ALLOC_NUM - 1; i++)
        {
            allocator.alloc();
        }

        const int* x = allocator.alloc();
        ASSERT_TRUE(__NOT_NULL(x));

        const int *y = allocator.alloc();
        ASSERT_TRUE(__IS_NULL(y));

        ASSERT_EQ(CUB_SUCCESS, allocator.dealloc(*x));

        y = allocator.alloc();
        ASSERT_TRUE(__NOT_NULL(y));
        ASSERT_EQ(2, *y);
    }

    const static int MAX_ALLOC_NUM = 3;
    LinkedAllocator<int, ARR_SIZE(array)> allocator;
};


