#include <cctest/cctest.h>
#include <cub/mem/StructObject.h>
#include <cub/base/BaseTypes.h>

USING_CUB_NS

namespace
{
    struct Msg
    {
        U32 id;
        U32 transNum;
    };
}

FIXTURE(StructObjectTest)
{

	TEST("should be zero when init")
	{
		StructObject<Msg> msg;
		ASSERT_EQ(0, msg.id);
		ASSERT_EQ(0, msg.transNum);

		memset(&msg, 0xff, sizeof(msg));
		ASSERT_EQ(0xffffffff, msg.id);
		ASSERT_EQ(0xffffffff, msg.transNum);
	}

	TEST("should be used as pointer")
	{
		StructObject<Msg> msg;
		ASSERT_EQ(0, msg->id);
		ASSERT_EQ(0, msg->transNum);

		memset(msg.getPointer(), 0x0ff, sizeof(msg));
		ASSERT_EQ(0xffffffff, (*msg).id);
		ASSERT_EQ(0xffffffff, (*msg).transNum);
	}
};
