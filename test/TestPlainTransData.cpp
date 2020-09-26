#include <cctest/cctest.h>
#include <cub/mem/PlainTransData.h>

USING_CUB_NS

namespace
{
    struct Foo
    {
       int a, b;
    };
}

FIXTURE(PlainTransDataTest)
{
	BEFORE
	{
		foo.a = 10;
		foo.b = 20;
	}

	const int* getConstPointer() const
	{
	  return intData.operator->();
	}

	const int& getConstReference() const
	{
	  return *intData;
	}

	void enableModifiable()
	{
	   intData.update(10);
	   intData.confirm();
	   intData.modify();
	}

	PlainTransData<int> intData;
	PlainTransData<Foo> fooData;

	Foo foo;

	TEST("an uninitialized trans data should be invalid")
	{
		ASSERT_FALSE(intData.isPresent());
	}

	TEST("an uninitialized trans data should be null if accessed by pointer")
	{
		ASSERT_TRUE(0 == intData.operator->());
	}

	TEST("an uninitialized trans data should be null if accessed by a constant pointer")
	{
		ASSERT_TRUE(0 == getConstPointer());
	}

	TEST("once set value it should become valid")
	{
		intData.update(10);
		ASSERT_TRUE(intData.isPresent());
	}

	TEST("once set value it should be able to be accessed by reference")
	{
		intData.update(10);
		ASSERT_TRUE(10 == getConstReference());
	}

	TEST("if revert a updated value should become invalid")
	{
		intData.update(10);
		intData.revert();

		ASSERT_FALSE(intData.isPresent());
	}

	TEST("before a updated value is confirmed if it reverted should become invalid again")
	{
		intData.update(10);
		intData.update(20);
		intData.revert();

		ASSERT_FALSE(intData.isPresent());
	}

	TEST("once a updated value is confirmed it should will become valid")
	{
		intData.update(10);
		intData.confirm();

		ASSERT_TRUE(intData.isPresent());
	}

	TEST("a confirmed value can not be reverted")
	{
		intData.update(10);
		intData.confirm();
		intData.revert();

		ASSERT_TRUE(intData.isPresent());
		ASSERT_TRUE(10 == (*intData));
	}

	TEST("a confirmed value can be updated again")
	{
		intData.update(10);
		intData.confirm();
		intData.update(20);

		ASSERT_TRUE(intData.isPresent());
		ASSERT_TRUE(20 == (*intData));
	}

	TEST("if a confirmed value is updated again then reverting should be able to rollback")
	{
		intData.update(10);
		intData.confirm();
		intData.update(20);
		intData.revert();

		ASSERT_TRUE(intData.isPresent());
		ASSERT_TRUE(10 == (*intData));
	}

	TEST("once a confirmed value is reset it should become invalid")
	{
		intData.update(10);
		intData.confirm();
		intData.reset();

		ASSERT_FALSE(intData.isPresent());
	}

	TEST("an unstable data should not be able to be modified")
	{
		intData.update(10);

		ASSERT_NE(CUB_SUCCESS, intData.modify());
	}

	TEST("a stable data should be able to be modified")
	{
		intData.update(10);
		intData.confirm();

		ASSERT_EQ(CUB_SUCCESS, intData.modify());
	}

	TEST("after clone for modification it is value keep unchanged")
	{
		enableModifiable();
		ASSERT_EQ(10, *intData);
	}

	TEST("after clone for modification should be able modify actually")
	{
		enableModifiable();
		(*intData) = 20;

		ASSERT_EQ(20, *intData);
	}

	TEST("after modification if revert should roll back")
	{
		enableModifiable();
		(*intData) = 20;
		intData.revert();

		ASSERT_EQ(10, *intData);
	}

	TEST("for an uninitialized trans data its old value should be invalid")
	{
		ASSERT_FALSE(fooData.isOldPresent());
	}

	TEST("for an initialized trans data its old value is still be invalid")
	{
		fooData.update(foo);
		ASSERT_FALSE(fooData.isOldPresent());
	}

	TEST("for an initialized PlainTransData after confirmation its old value is still be invalid")
	{
		fooData.update(foo);
		fooData.confirm();

		ASSERT_FALSE(fooData.isOldPresent());
	}

	TEST("after confirmation if update again its old value should be valid")
	{
		fooData.update(foo);
		fooData.confirm();

		foo.a = 1;
		foo.b = 2;

		fooData.update(foo);

		ASSERT_TRUE(fooData.isOldPresent());
	}

	TEST("after confirmation if update again its old value should be the previous one")
	{
		fooData.update(foo);
		fooData.confirm();

		foo.a = 1;
		foo.b = 2;

		fooData.update(foo);

		ASSERT_EQ(10, fooData.getOldValue().a);
		ASSERT_EQ(20, fooData.getOldValue().b);
	}

	TEST("after confirmation if update again its new value should be the new one")
	{
		fooData.update(foo);
		fooData.confirm();

		foo.a = 1;
		foo.b = 2;

		fooData.update(foo);

		ASSERT_EQ(1, fooData->a);
		ASSERT_EQ(2, fooData->b);
	}
};
