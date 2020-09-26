#include <cctest/cctest.h>
#include <cub/base/BaseTypes.h>
#include <cub/mem/StructWrapper.h>

USING_CUB_NS

namespace
{
    struct PlainMsg
    {
        U32 id;
        U32 transNum;
    };

    STRUCT_WRAPPER(DomainEvent, PlainMsg)
    {
        enum
        {
            MIN_ID = 0,
            MAX_ID = 20,
        };

        bool isValid() const
        {
            return (MIN_ID <= id) && (id <= MAX_ID);
        }
    };
}

FIXTURE(StructWrapperTest)
{
	TEST("should use the method when wrappered")
	{
	    PlainMsg msg{2, 4};

	    DomainEvent& event = DomainEvent::by(msg);

	    ASSERT_TRUE(event.isValid());
	    ASSERT_EQ(4, event.transNum);
	}
};


