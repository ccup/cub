#include <cctest/cctest.h>
#include <cub/repo/list/List.h>
#include <cub/repo/list/ListElem.h>
#include <cub/base/NullPtr.h>

USING_CUB_NS

namespace
{
    struct Foo : ListElem<Foo>
    {
        Foo(int a) : x(a)
        {
        }

        int getValue() const
        {
            return x;
        }

    private:
        int x;
    };
}

FIXTURE(ListTest)
{
	TEST("should be empty when init")
	{
		ASSERT_TRUE(__IS_NULL(elems.getFirst()));
	    ASSERT_TRUE(__IS_NULL(elems.getLast()));
	    ASSERT_TRUE(elems.isEmpty());
	    ASSERT_EQ(0, elems.size());
	}

	TEST("should be get elem when list is not empty")
	{
	    Foo elem(1);

	    elems.pushBack(elem);

	    ASSERT_FALSE(elems.isEmpty());
	    ASSERT_EQ(1, elems.size());
	    ASSERT_EQ(&elem, elems.getFirst());
	    ASSERT_EQ(&elem, elems.getLast());

	    Foo* first = elems.popFront();
	    ASSERT_EQ(1, first->getValue());
	    ASSERT_TRUE(elems.isEmpty());
	}

	TEST("should travel the list")
	{
	    Foo elem1(1), elem2(2), elem3(3);

	    elems.pushBack(elem1);
	    elems.pushBack(elem2);
	    elems.pushBack(elem3);

	    int i = 1;
	    LIST_FOREACH(Foo, elem, elems)
	    {
	        ASSERT_EQ(i++, elem->getValue());
	    }
	}

	TEST("should point to the correct addr when get next")
	{
	    Foo elem(1);
	    elems.pushBack(elem);

	    ASSERT_EQ(&elem, elems.begin().getValue());
	    ASSERT_NE(&elem, elems.end().getValue());
	    List<Foo>::Iterator p = elems.begin();
	    ASSERT_EQ(elems.end(), elems.getNext(p));
	}

    List<Foo> elems;
};


