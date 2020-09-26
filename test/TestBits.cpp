#include <cctest/cctest.h>
#include <cub/algo/bits.h>

USING_CUB_NS

FIXTURE(BitsTest)
{
	TEST("should calc the correct bit mask by macro")
	{
	    ASSERT_EQ(0, BIT_MASK(0));
	    ASSERT_EQ(1, BIT_MASK(1));
	    ASSERT_EQ(3, BIT_MASK(2));
	    ASSERT_EQ(0x7F, BIT_MASK(7));
	    ASSERT_EQ(0xFF, BIT_MASK(8));
	    ASSERT_EQ(0x7FFF, BIT_MASK(15));
	    ASSERT_EQ(0xFFFF, BIT_MASK(16));
	    ASSERT_EQ(0x7FFFFFFF, BIT_MASK(31));
	    ASSERT_EQ(0xFFFFFFFF, BIT_MASK(32));
	    ASSERT_EQ(0x7FFFFFFFFFFFFFFF, BIT_MASK(63));
	}

	TEST("should calc the correct bit mask by template function")
	{
	    ASSERT_EQ(0, bit_mask<U8>(0));
	    ASSERT_EQ(1, bit_mask<U8>(1));
	    ASSERT_EQ(0x3, bit_mask<U8>(2));
	    ASSERT_EQ(0x7F, bit_mask<U8>(7));
	    ASSERT_EQ(0xFF, bit_mask<U8>(8));
	    ASSERT_EQ(0x7FFF, bit_mask<U16>(15));
	    ASSERT_EQ(0xFFFF, bit_mask<U16>(16));
	    ASSERT_EQ(0x7FFFFFFF, bit_mask<U32>(31));
	    ASSERT_EQ(0xFFFFFFFF, bit_mask<U64>(32));
	    ASSERT_EQ(0x7FFFFFFFFFFFFFFF, bit_mask<U64>(63));
	}

	TEST("should get the bits value by macro")
	{
	    ASSERT_EQ(0x2, GET_BITS_VALUE(0xaa, 2, 2));
	    ASSERT_EQ(0x1, GET_BITS_VALUE(0xaa, 3, 2));
	    ASSERT_EQ(0x5, GET_BITS_VALUE(0xaa, 3, 3));
	    ASSERT_EQ(0x1, GET_BITS_VALUE(0xaa, 7, 4));
	    ASSERT_EQ(0xc, GET_BITS_VALUE(0xccaaaaaaaaaaaaaa, 60, 4));
	}

	TEST("should get the bits value by template function")
	{
	    ASSERT_EQ(0x2, bit_value(0xaa, 2, 2));
	    ASSERT_EQ(0x1, bit_value(0xaa, 3, 2));
	    ASSERT_EQ(0x5, bit_value(0xaa, 3, 3));
	    ASSERT_EQ(0x1, bit_value(0xaa, 7, 4));

	    ASSERT_EQ(0xc, bit_value(0xccaaaaaaaaaaaaaa, 60, 4));
	}

	TEST("should get the given bit value by macro")
	{
		ASSERT_FALSE(IS_BIT_ON(0xaa, 2));
		ASSERT_TRUE(IS_BIT_ON(0xccaaaaaaaaaaaaaa, 63));
	}

	TEST("should get the given bit value by template function")
	{
		ASSERT_FALSE(is_bit_on(0xaa, 2));
	    ASSERT_TRUE(is_bit_on(0xccaaaaaaaaaaaaaa, 63));
	}
};


