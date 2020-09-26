#include <cctest/cctest.h>
#include <cub/algo/bound.h>
#include <cub/repo/array/ArraySize.h>

USING_CUB_NS

namespace
{
    int a[] = {1, 3, 5, 7};
}

FIXTURE(UpperBoundTest)
{
	TEST("should find the upper bound in middle position correct")
	{
	    ASSERT_EQ(2, upper_bound(a, ARR_SIZE(a), 4));
	}

	TEST("should find the upper bound in left edge position correct")
	{
	    ASSERT_EQ(0, upper_bound(a, ARR_SIZE(a), 0));
	}

	TEST("should find the upper bound in last position correct")
	{
	    ASSERT_EQ(3, upper_bound(a, ARR_SIZE(a), 7));
	}

	TEST("should find the upper bound out of right position correct")
	{
	    ASSERT_EQ(3, upper_bound(a, ARR_SIZE(a), 8));
	}
};

FIXTURE(LowerBoundTest)
{
	TEST("should find the upper bound in middle position correct")
	{
	    ASSERT_EQ(1, lower_bound(a, ARR_SIZE(a), 4));
	}

	TEST("should find the upper bound in right edge position correct")
	{
	    ASSERT_EQ(3, lower_bound(a, ARR_SIZE(a), 8));
	}

	TEST("should find the upper bound in left edge position correct")
	{
	    ASSERT_EQ(0, lower_bound(a, ARR_SIZE(a), 1));
	}

	TEST("should find the upper bound out of left edge position correct")
	{
	    ASSERT_EQ(0, lower_bound(a, ARR_SIZE(a), 0));
	}
};


