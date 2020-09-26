#include <cctest/cctest.h>
#include <cub/mem/SharedObject.h>
#include <cub/mem/SmartPtr.h>
#include <cub/base/Keywords.h>

USING_CUB_NS

namespace
{
    struct Foo : SharedObject
    {
        Foo() : destroyedNum(0)
        {
        }

        int getDestroyNum() const
        {
            return destroyedNum;
        }

		  SharedObject& getSharedObject() { return *this; }
        //IMPL_ROLE(SharedObject);

    private:
        OVERRIDE(void destroy())
        {
            destroyedNum++;
        }
        OVERRIDE(bool needDestroy())
        {
            return true;
        }

    private:
        int destroyedNum;
    };
}

FIXTURE(SmartPtrTest)
{
	TEST("should ref to the correct addr")
	{
		Foo foo;
		SmartPtr<Foo> pf(&foo);

		ASSERT_FALSE(pf.isNull());
		ASSERT_EQ(&foo, pf.raw());
	}

	TEST("should be equal when point to same addr")
	{
		Foo foo;
		SmartPtr<Foo> pf1(&foo);
		SmartPtr<Foo> pf2(&foo);

		ASSERT_TRUE(pf1 == pf2);
	}

	TEST("should increase ref when assign to smart ptr")
	{
		Foo foo;

		{
			SmartPtr<Foo> pf(&foo);
			ASSERT_EQ(1, foo.getRefCount());
			ASSERT_EQ(0, foo.getDestroyNum());
		}

		ASSERT_EQ(0, foo.getRefCount());
		ASSERT_EQ(1, foo.getDestroyNum());
	}

	TEST("should not destory when ref not equal zero")
	{
		Foo foo;

		SmartPtr<Foo> pf1(&foo);

		{
			SmartPtr<Foo> pf2(&foo);
			ASSERT_EQ(2, foo.getRefCount());
			ASSERT_EQ(0, foo.getDestroyNum());
		}

		ASSERT_EQ(1, foo.getRefCount());
		ASSERT_EQ(0, foo.getDestroyNum());
	}

	TEST("should add ref when smart ptr construct other smart ptr")
	{
		Foo foo;

		SmartPtr<Foo> pf1(&foo);

		{
			SmartPtr<Foo> pf2(pf1);
			ASSERT_EQ(2, foo.getRefCount());
			ASSERT_EQ(0, foo.getDestroyNum());
		}

		ASSERT_EQ(1, foo.getRefCount());
		ASSERT_EQ(0, foo.getDestroyNum());
	}

	TEST("should add ref when smart ptr assign to other smart ptr")
	{
		Foo foo;

		SmartPtr<Foo> pf1(&foo);

		{
			SmartPtr<Foo> pf2;
			pf2 = pf1;
			ASSERT_EQ(2, foo.getRefCount());
			ASSERT_EQ(0, foo.getDestroyNum());
		}

		ASSERT_EQ(1, foo.getRefCount());
		ASSERT_EQ(0, foo.getDestroyNum());
	}
};
