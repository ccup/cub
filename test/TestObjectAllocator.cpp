#include <cctest/cctest.h>
#include <cub/mem/ObjectAllocator.h>
#include <cub/algo/loop.h>

USING_CUB_NS

namespace
{
    struct Foo
    {
        Foo(int a) : x(a)
        {
        }

        int getValue() const
        {
            return x;
        }

        DECL_OPERATOR_NEW();

    private:
        int x;
    };

    const U16 MAX_SLOT_NUM = 2;
}

DEF_OBJ_ALLOCATOR(Foo, MAX_SLOT_NUM);

FIXTURE(ObjectAllocatorTest)
{
	TEST("should have correct free slot when init")
	{
	    ASSERT_EQ(MAX_SLOT_NUM, FooAllocator.getFreeSlotNum());
	}

	TEST("should alloc OK when has free slot")
	{
	    Foo* foo = new Foo(3);
	    ASSERT_TRUE(__NOT_NULL(foo));
	    ASSERT_EQ(MAX_SLOT_NUM - 1, FooAllocator.getFreeSlotNum());

	    delete foo;
	    ASSERT_EQ(MAX_SLOT_NUM, FooAllocator.getFreeSlotNum());
	}

	TEST("should not alloc when has no free slot")
	{
	    Foo* foos[MAX_SLOT_NUM] = {__null_ptr};

	    FOR_EACH_0(i, MAX_SLOT_NUM)
	    {
	        foos[i] = new Foo(0);
	    }

	    Foo* foo = new Foo(0);
	    ASSERT_TRUE(__IS_NULL(foo));

	    FOR_EACH_0(i, MAX_SLOT_NUM)
	    {
	    	ASSERT_TRUE(__NOT_NULL(foos[i]));
	        delete foos[i];
	    }

	    foo = new Foo(0);
	    ASSERT_TRUE(__NOT_NULL(foo));
	    delete foo;
	}
};