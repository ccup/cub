#include <cctest/cctest.h>
#include <cub/utils/TypeId.h>

USING_CUB_NS

namespace
{
    struct Empty
    {
    };

	using EmptyAlas = Empty;

	struct None {
	};
}

FIXTURE(TypeIdTest)
{
	TEST("should compare basic type")
	{
		ASSERT_EQ(TypeIdOf<int>(), TypeIdOf<int>());
		ASSERT_NE(TypeIdOf<int>(), TypeIdOf<float>());
	}

    TEST("should compare struct type")
	{
		ASSERT_EQ(TypeIdOf<Empty>(), TypeIdOf<Empty>());
		ASSERT_EQ(TypeIdOf<Empty>(), TypeIdOf<EmptyAlas>());
		ASSERT_NE(TypeIdOf<Empty>(), TypeIdOf<None>());
	}

	TEST("should compare pointer type")
	{
		ASSERT_EQ(TypeIdOf<Empty*>(), TypeIdOf<Empty*>());
		ASSERT_NE(TypeIdOf<Empty*>(), TypeIdOf<None*>());
	}

	TEST("should compare reference type")
	{
		ASSERT_EQ(TypeIdOf<Empty&>(), TypeIdOf<Empty&>());
		ASSERT_NE(TypeIdOf<Empty&>(), TypeIdOf<None&>());
	}

	TEST("should compare const type")
	{
		ASSERT_EQ(TypeIdOf<const Empty>(), TypeIdOf<const Empty>());
		ASSERT_NE(TypeIdOf<const Empty>(), TypeIdOf<Empty>());
		ASSERT_NE(TypeIdOf<const Empty>(), TypeIdOf<const None>());
	}

	TEST("should compare container type")
	{
		ASSERT_EQ(TypeIdOf<std::vector<int>>(), TypeIdOf<std::vector<int>>());
		ASSERT_NE(TypeIdOf<std::vector<int>>(), TypeIdOf<std::vector<float>>());
	}
};


