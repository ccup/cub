#include <cctest/cctest.h>
#include <cub/algo/range.h>
#include <cub/base/StaticAssert.h>
#include <type_traits>

namespace
{
    int arr[] = {-1, -2, 3, 4};
    std::vector<int> v1 {-1, -2, 3, 4};
    const std::vector<int> v2 {-1, -2, 3, 4};
}

#define STATIC_ASSERT_TYPE(expect_type, expr) \
	STATIC_ASSERT((std::is_same<expect_type, decltype(expr)>::value))

#define STATIC_ASSERT_SAME_TYPE(expect_type, actual_type) \
    STATIC_ASSERT_TRUE((std::is_same<expect_type, actual_type>::value))

#define STATIC_ASSERT_RVALUE_REF(expr) \
    STATIC_ASSERT_TRUE(std::is_rvalue_reference<decltype(expr)>::value)

#define STATIC_ASSERT_LVALUE_REF(expr) \
    STATIC_ASSERT_TRUE(std::is_lvalue_reference<decltype(expr)>::value)

FIXTURE(AlgorithmTest)
{
   TEST("find support non const container")
    {
        auto found = cub::find(v1, 3);

        STATIC_ASSERT_TYPE(std::vector<int>::iterator, found);
        ASSERT_EQ(3, *found);
    }

    TEST("find support const container")
    {
        auto found = cub::find(v2, 3);

        STATIC_ASSERT_TYPE(std::vector<int>::const_iterator, found);
        ASSERT_EQ(3, *found);
    }

    TEST("find_if support non const container")
    {
        auto found = cub::find_if(v1, [](int e) { return e > 0; });

        STATIC_ASSERT_TYPE(std::vector<int>::iterator, found);
        ASSERT_EQ(3, *found);
    }

    TEST("find_if support const container")
    {
        auto found = cub::find_if(v2, [](int e) { return e > 0; });

        STATIC_ASSERT_TYPE(std::vector<int>::const_iterator, found);
        ASSERT_EQ(3, *found);
    }

    TEST("map")
    {
        std::vector<int> v;
        cub::map(v1, std::back_inserter(v), [](int e) { return e > 0 ? e : -e; });

        ASSERT_EQ(1, v[0]);
        ASSERT_EQ(2, v[1]);
        ASSERT_EQ(3, v[2]);
        ASSERT_EQ(4, v[3]);
    }

    TEST("reduce")
    {
        auto sum = cub::reduce(arr, 0, [](int& sum, int e) { sum += e; });

        ASSERT_EQ(4, sum);
    }

    TEST("filter")
    {
        std::vector<int> v;
        cub::filter(arr, std::back_inserter(v), [](int e) { return e > 0; });

        ASSERT_EQ(3, v[0]);
        ASSERT_EQ(4, v[1]);
    }

    TEST("each")
    {
        auto sum = 0;
        cub::each(arr, [&sum](int e) { sum += e; });

        ASSERT_EQ(4, sum);
    }
};
