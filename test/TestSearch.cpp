#include <cctest/cctest.h>
#include <cub/algo/search.h>
#include <cub/repo/array/ArraySize.h>

USING_CUB_NS

namespace
{
    int a[] = {1, 3, 5, 7};
}

FIXTURE(BinarySearchTest)
{
	TEST("should find correct when key is in the middle position")
	{
		int *r = binary_search(begin_a(a), end_a(a), 5);
		ASSERT_EQ(5, *r);
		ASSERT_EQ(2, position(a, r));
	}

	TEST("should return the end when key not find")
	{
		ASSERT_EQ(end_a(a), binary_search(begin_a(a), end_a(a), 6));
	}
};
