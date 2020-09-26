#include <cctest/cctest.h>
#include <cub/repo/array/Array.h>

USING_CUB_NS

namespace
{
    struct PlainObject
    {
        int a;
        int b;
    };

    const int INVALID_VALUE = 0xFF;

    struct Object
    {
        Object() : value(INVALID_VALUE)
        {
        }

        Object(int value)
        :value(value)
        {
        }

        int getValue() const
        {
            return value;
        }

        void update(U8 v)
        {
            value = v;
        }

    private:
        U8 value;
    };
}

FIXTURE(ArrayTest)
{
	TEST("should define plain object array")
	{
	    Array<PlainObject, 2> objects;

	    objects[0].a = 1;
	    objects[1].b = 2;

	    ASSERT_EQ(2, objects.size());
	    ASSERT_EQ(1, objects[0].a);
	    ASSERT_EQ(2, objects[1].b);
	}

    TEST("should define object array with default constructor")
	{
	    Array<Object, 2> objects;

	    ASSERT_EQ(INVALID_VALUE, objects[0].getValue());
	    ASSERT_EQ(INVALID_VALUE, objects[1].getValue());
	}

	TEST("should define object array with para constructor")
	{
	    Array<Object, 2> objects(5);

	    ASSERT_EQ(5, objects[0].getValue());
	    ASSERT_EQ(5, objects[1].getValue());
	}

    TEST("should invoke unconst method of array elem")
	{
	    Array<Object, 2> objects(5);

	    objects[1].update(10);

	    ASSERT_EQ(5, objects[0].getValue());
	    ASSERT_EQ(10, objects[1].getValue());
	}

    TEST("should emplace a array elem")
	{
	    Array<Object, 2> objects;

	    objects.emplace(1, 5);

	    ASSERT_EQ(INVALID_VALUE, objects[0].getValue());
	    ASSERT_EQ(5, objects[1].getValue());
	}

    TEST("should use the iterator of array")
	{
	    typedef Array<Object, 2> ThisArray;
	    ThisArray objects;


	    ThisArray::Iterator i = objects.begin();
	    ASSERT_EQ(INVALID_VALUE, i->getValue());

	    objects[1].update(5);
	    i++;
	    ASSERT_EQ(5, i->getValue());

	    i->update(10);
	    ASSERT_EQ(10, objects[1].getValue());

	    ASSERT_NE(i, objects.end());
	    ASSERT_EQ(++i, objects.end());
	}

    TEST("should travel array")
	{
	    typedef Array<Object, 2> ThisArray;
	    ThisArray objects(10);

	    objects[1].update(5);

	    U32 sum = 0;
	    ARRAY_FOREACH(ThisArray, i, objects)
	    {
	        sum += i->getValue();
	    }
	    ASSERT_EQ(15, sum);
	}
};


