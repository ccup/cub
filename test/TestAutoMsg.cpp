#include <cctest/cctest.h>
#include <cub/mem/AutoMsg.h>

USING_CUB_NS

namespace
{
    struct LargeMsg
    {
        U8 msgBuff[16 * 1024];
    };
}

FIXTURE(AutoMsgTest)
{
	TEST("should alloc auto msg not in stack")
	{
	    AutoMsg<LargeMsg> msg;

	    ASSERT_TRUE(MsgAllocator::withIn(msg.getPointer()));
	}
};


