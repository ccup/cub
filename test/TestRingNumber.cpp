#include <cctest/cctest.h>
#include <cub/repo/number/RingNumber.h>

USING_CUB_NS

FIXTURE(RingNumberTest)
{
	TEST("should compare equal when ring number init equal")
	{
		RingNumber<U8, 10> r1(1);
		RingNumber<U8, 10> r2(11);

		ASSERT_TRUE(r1 == r2);
	}

	TEST("should compare unequal when ring number init unequal")
	{
		RingNumber<U8, 10> r1(2);
		RingNumber<U8, 10> r2(11);

		ASSERT_FALSE(r1 == r2);
	}

	TEST("should compare equal when ring number add to equal")
	{
		RingNumber<U8, 10> r1(2);
		RingNumber<U8, 10> r2(11);

		ASSERT_TRUE(r1 == (++r2));
	}

	TEST("should compare equal when ring number move to equal")
	{
		RingNumber<U8, 10> r1(4);
		RingNumber<U8, 10> r2(11);

		ASSERT_TRUE((r1 << 2) == (r2 >> 11));
	}
};
