#include <cctest/cctest.h>
#include <cub/mem/Maybe.h>

USING_CUB_NS

FIXTURE(MaybeTest)
{
	TEST("should be unpresent when init")
	{
	    Maybe<int> x;

	    ASSERT_FALSE(x.isPresent());
	}

	TEST("should be present when update")
	{
	    Maybe<int> x;

	    x.update(5);

	    ASSERT_TRUE(x.isPresent());
	    ASSERT_EQ(5, *x);
	}

	TEST("should be present when force effective")
	{
	    Maybe<int> x;

	    x.forceEffective();

	    ASSERT_TRUE(x.isPresent());
	    ASSERT_EQ(0, *x);
	}

	TEST("should compare unequal when not effective")
	{
	    Maybe<int> x;
	    Maybe<int> y(2);

	    ASSERT_FALSE(x == y);
	}

	TEST("should compare equal when effective")
	{
	    Maybe<int> x;
	    Maybe<int> y(2);

	    x.update(2);

	    ASSERT_TRUE(x == y);
	}
};


