#include <cctest/cctest.h>
#include <cub/mem/TransData.h>
#include <stdlib.h>

USING_CUB_NS

namespace
{
    static unsigned int alloc_blocks = 0;

    struct ObjectInfo
    {
        ObjectInfo() : value(0xFF) {}
        ObjectInfo(int value) : value(value) {}

        int getValue() const
        {
            return value;
        }

        bool operator==(const ObjectInfo& rhs) const
        {
            return value == rhs.value;
        }

        bool operator!=(const ObjectInfo& rhs) const
        {
            return value != rhs.value;
        }

        void* operator new(size_t size)
        {
            alloc_blocks++;
            return ::malloc(size);
        }

        void operator delete(void* p)
        {
            if(p != 0)
            {
                if(alloc_blocks == 0) 
                {
                    return;
                }

                alloc_blocks--;
                ::free(p);
            }
        }
    private:
        int value;
    };

    struct Object
    {
        Object() : info(0) {}
        Object(int value) : info(new ObjectInfo(value)) {}

        Object& operator=(const Object& rhs)
        {
            info = rhs.info;
            return *this;
        }

        Status copyTo(Object& rhs)
        {
            CUB_ASSERT_VALID_PTR(info);

            if (rhs.info == 0) rhs.info = new ObjectInfo(*info);
            else *rhs.info = *info;

            return CUB_SUCCESS;
        }

        void reset()
        {
            delete info;
            info = 0;
        }

        bool operator==(const Object& rhs) const
        {
            if(info == 0 && rhs.info == 0) return true;

            if(info != 0 && rhs.info != 0)
            {
                return *info == *rhs.info;
            }

            return false;
        }

        bool operator!=(const Object& rhs) const
        {
            return !(*this == rhs);
        }

        int getValue() const
        {
            return info == 0 ? 0xFF : info->getValue();
        }

    private:
        ObjectInfo *info;
    };

}

FIXTURE(TestInitTransData)
{
    TransData<Object> data;

    TEST("the state should be correct for an uninitialized trans data")
    {
        assertInit();
    }

    TEST("should in NEW state after updating")
    {
        data.update(Object(2));

        assertUpdated();
    }

    TEST("should in NEW state after force updating")
    {
        data.forceUpdate();
        data.update(Object(2));

        assertUpdated();
    }

    TEST("should in ACTIVE state after updating then confirming")
    {
        data.update(Object(2));
        data.confirm();

        ASSERT_TRUE(data.isStable());

        ASSERT_TRUE(data.isPresent());
        ASSERT_EQ(2, data->getValue());

        ASSERT_FALSE(data.isOldPresent());
        ASSERT_FALSE(data.isChanged());
        ASSERT_TRUE(data.isChanged(true));
        ASSERT_EQ(1, alloc_blocks);
    }

    TEST("should return to INIT after updating then reverting")
    {
        data.update(Object(2));
        data.revert();

        assertInit();
    }

    TEST("touch should have no effect")
    {
        data.touch();

        assertInit();
    }

    TEST("release should have no effect")
    {
        data.release();

        assertInit();
    }

    TEST("reset should have no effect")
    {
        data.reset();

        assertInit();
    }

    TEST("should not allow to modify")
    {
        ASSERT_NE(CUB_SUCCESS, data.modify());

        assertInit();
    }

    void assertInit()
    {
    	ASSERT_TRUE(data.isStable());

    	ASSERT_FALSE(data.isPresent());
    	ASSERT_FALSE(data.isOldPresent());
    	ASSERT_FALSE(data.isChanged());
    	ASSERT_FALSE(data.isChanged(true));
        ASSERT_EQ(0, alloc_blocks);
    }

    void assertUpdated()
    {
    	ASSERT_FALSE(data.isStable());

    	ASSERT_TRUE(data.isPresent());
        ASSERT_EQ(2, data->getValue());

        ASSERT_FALSE(data.isOldPresent());
        ASSERT_TRUE(data.isChanged());
        ASSERT_TRUE(data.isChanged(true));
        ASSERT_EQ(1, alloc_blocks);
    }
};



//////////////////////////////////////////////////////////////////////////
FIXTURE(TestActiveTransData)
{
    TransData<Object> data;

    BEFORE
    {
        data.update(Object(2));
        data.confirm();
    }

    void assertInit()
    {
        ASSERT_TRUE(data.isStable());

        ASSERT_FALSE(data.isPresent());
        ASSERT_FALSE(data.isOldPresent());
        ASSERT_FALSE(data.isChanged());
        ASSERT_FALSE(data.isChanged(true));
        ASSERT_EQ(0, alloc_blocks);
    }

    void update()
    {
        data.update(Object(3));

        ASSERT_FALSE(data.isStable());

        ASSERT_TRUE(data.isPresent());
        ASSERT_EQ(3, data->getValue());

        ASSERT_TRUE(data.isOldPresent());
        ASSERT_EQ(2, data.getOldValue().getValue());

        ASSERT_TRUE(data.isChanged());
        ASSERT_TRUE(data.isChanged(true));
        ASSERT_EQ(2, alloc_blocks);
    }

	TEST("after reset should return to idle")
	{
		data.reset();
		assertInit();
	}

	TEST("should in MODIFIED state after updating")
	{
		update();
	}

	TEST("should in MODIFIED state after force updating")
	{
		data.forceUpdate();
		update();
	}

	TEST("should in ACTIVE state after updating and confirming")
	{
		data.update(Object(3));
		data.confirm();

		ASSERT_TRUE(data.isStable());

		ASSERT_TRUE(data.isPresent());
		ASSERT_EQ(3, data->getValue());

		ASSERT_FALSE(data.isOldPresent());

		ASSERT_FALSE(data.isChanged());
		ASSERT_TRUE(data.isChanged(true));
		ASSERT_EQ(1, alloc_blocks);
	}

	TEST("should not be changed after updating a identical value")
	{
		data.update(Object(2));

		ASSERT_FALSE(data.isStable());

		ASSERT_TRUE(data.isPresent());
		ASSERT_EQ(2, data->getValue());

		ASSERT_TRUE(data.isOldPresent());
		ASSERT_EQ(2, data->getValue());

		ASSERT_FALSE(data.isChanged());
		ASSERT_TRUE(data.isChanged(true));
		ASSERT_EQ(2, alloc_blocks);
	}

	TEST("should be able to modify")
	{
		ASSERT_EQ(CUB_SUCCESS, data.modify());

		ASSERT_FALSE(data.isStable());

		ASSERT_TRUE(data.isPresent());
		ASSERT_EQ(2, data->getValue());

		ASSERT_TRUE(data.isOldPresent());
		ASSERT_EQ(2, data->getValue());

		ASSERT_FALSE(data.isChanged());
		ASSERT_TRUE(data.isChanged(true));
		ASSERT_EQ(2, alloc_blocks);
	}

	TEST("should in ACTIVE state after updating and reverting")
	{
		data.update(Object(3));
		data.revert();

		ASSERT_TRUE(data.isStable());

		ASSERT_TRUE(data.isPresent());
		ASSERT_EQ(2, data->getValue());

		ASSERT_FALSE(data.isOldPresent());

		ASSERT_FALSE(data.isChanged());
		ASSERT_TRUE(data.isChanged(true));
		ASSERT_EQ(1, alloc_blocks);
	}

	TEST("should in TOUCHED state after touch")
	{
		data.touch();

		ASSERT_FALSE(data.isStable());

		ASSERT_TRUE(data.isPresent());
		ASSERT_EQ(2, data->getValue());

		ASSERT_FALSE(data.isOldPresent());

		ASSERT_TRUE(data.isChanged());
		ASSERT_TRUE(data.isChanged(true));
		ASSERT_EQ(1, alloc_blocks);
	}

	TEST("should in RELEASED state after release")
	{
		data.release();

		ASSERT_FALSE(data.isStable());

		ASSERT_FALSE(data.isPresent());

		ASSERT_TRUE(data.isOldPresent());
		ASSERT_EQ(2, data.getOldValue().getValue());

		ASSERT_TRUE(data.isChanged());
		ASSERT_FALSE(data.isChanged(true));
		ASSERT_EQ(1, alloc_blocks);

		data.confirm();

		assertInit();
	}

};

//////////////////////////////////////////////////////////////////////////
FIXTURE(TestTouchTransData)
{
    TransData<Object> data;

    BEFORE
    {
        data.update(Object(2));
        data.confirm();
        data.touch();
    }

    void assertInit()
    {
        ASSERT_TRUE(data.isStable());

        ASSERT_FALSE(data.isPresent());
        ASSERT_FALSE(data.isOldPresent());
        ASSERT_FALSE(data.isChanged());
        ASSERT_FALSE(data.isChanged(true));
        ASSERT_EQ(0, alloc_blocks);
    }


	TEST("should be in shadow state")
	{
		ASSERT_FALSE(data.isStable());

		ASSERT_TRUE(data.isPresent());
		ASSERT_EQ(2, data->getValue());

		ASSERT_FALSE(data.isOldPresent());

		ASSERT_TRUE(data.isChanged());
		ASSERT_TRUE(data.isChanged(true));
		ASSERT_EQ(1, alloc_blocks);

		data.confirm();

		ASSERT_TRUE(data.isStable());

		ASSERT_TRUE(data.isPresent());
		ASSERT_EQ(2, data->getValue());

		ASSERT_FALSE(data.isOldPresent());

		ASSERT_FALSE(data.isChanged());
		ASSERT_TRUE(data.isChanged(true));
		ASSERT_EQ(1, alloc_blocks);
	}

	TEST("should not allow modify")
	{
		ASSERT_NE(CUB_SUCCESS, data.modify());

		ASSERT_FALSE(data.isStable());

		ASSERT_TRUE(data.isPresent());
		ASSERT_EQ(2, data->getValue());

		ASSERT_FALSE(data.isOldPresent());

		ASSERT_TRUE(data.isChanged());
		ASSERT_TRUE(data.isChanged(true));
		ASSERT_EQ(1, alloc_blocks);
	}

	TEST("should be in shadow state after updating")
	{
		data.update(Object(2));

		ASSERT_FALSE(data.isStable());

		ASSERT_TRUE(data.isPresent());
		ASSERT_EQ(2, data->getValue());

		ASSERT_TRUE(data.isOldPresent());
		ASSERT_EQ(2, data.getOldValue().getValue());

		ASSERT_TRUE(data.isChanged());
		ASSERT_TRUE(data.isChanged(true));
		ASSERT_EQ(2, alloc_blocks);
	}

	TEST("should use new data after updating")
	{
		data.update(Object(3));

		ASSERT_FALSE(data.isStable());

		ASSERT_TRUE(data.isPresent());
		ASSERT_EQ(3, data->getValue());

		ASSERT_TRUE(data.isOldPresent());
		ASSERT_EQ(2, data.getOldValue().getValue());

		ASSERT_TRUE(data.isChanged());
		ASSERT_TRUE(data.isChanged(true));
		ASSERT_EQ(2, alloc_blocks);
	}

	TEST("should in ACTIVE state after confirm")
	{
		data.confirm();

		ASSERT_TRUE(data.isStable());

		ASSERT_TRUE(data.isPresent());
		ASSERT_EQ(2, data->getValue());

		ASSERT_FALSE(data.isOldPresent());

		ASSERT_FALSE(data.isChanged());
		ASSERT_TRUE(data.isChanged(true));
		ASSERT_EQ(1, alloc_blocks);
	}

	TEST("should in ACTIVE state after reverting")
	{
		data.revert();

		ASSERT_TRUE(data.isStable());

		ASSERT_TRUE(data.isPresent());
		ASSERT_EQ(2, data->getValue());

		ASSERT_FALSE(data.isOldPresent());

		ASSERT_FALSE(data.isChanged());
		ASSERT_TRUE(data.isChanged(true));
		ASSERT_EQ(1, alloc_blocks);
	}

	TEST("should in RELEASED state after releasing")
	{
		data.release();

		ASSERT_FALSE(data.isStable());

		ASSERT_FALSE(data.isPresent());

		ASSERT_TRUE(data.isOldPresent());
		ASSERT_EQ(2, data.getOldValue().getValue());

		ASSERT_TRUE(data.isChanged());
		ASSERT_FALSE(data.isChanged(true));
		ASSERT_EQ(1, alloc_blocks);

		data.confirm();
		assertInit();
	}

	TEST("should in ACTIVE state after releasing and reverting")
	{
		data.release();
		data.revert();

		ASSERT_TRUE(data.isStable());

		ASSERT_TRUE(data.isPresent());
		ASSERT_EQ(2, data->getValue());

		ASSERT_FALSE(data.isOldPresent());

		ASSERT_FALSE(data.isChanged());
		ASSERT_TRUE(data.isChanged(true));
		ASSERT_EQ(1, alloc_blocks);
	}

	TEST("should in IDLE state after reset")
	{
		data.reset();
		assertInit();
	}
};

//////////////////////////////////////////////////////////////////////////
FIXTURE(TestReleaseTransData)
{
    TransData<Object> data;

    BEFORE
    {
        data.update(Object(2));
        data.confirm();
        data.release();
    }

    void assertInit()
    {
    	ASSERT_TRUE(data.isStable());

    	ASSERT_FALSE(data.isPresent());
    	ASSERT_FALSE(data.isOldPresent());
    	ASSERT_FALSE(data.isChanged());
    	ASSERT_FALSE(data.isChanged(true));
        ASSERT_EQ(0, alloc_blocks);
    }

	TEST("should in IDLE state after reseting")
	{
		data.reset();
		assertInit();
	}

	TEST("should in IDLE state after confirming")
	{
		data.confirm();
		assertInit();
	}

	TEST("should in ACTIVE state after reverting")
	{
		data.revert();

		ASSERT_TRUE(data.isStable());

		ASSERT_TRUE(data.isPresent());
		ASSERT_EQ(2, data->getValue());

		ASSERT_FALSE(data.isOldPresent());

		ASSERT_FALSE(data.isChanged());
		ASSERT_TRUE(data.isChanged(true));
		ASSERT_EQ(1, alloc_blocks);
	}

	TEST("should in RELEASED state")
	{
		ASSERT_FALSE(data.isStable());

		ASSERT_FALSE(data.isPresent());

		ASSERT_TRUE(data.isOldPresent());
		ASSERT_EQ(2, data.getOldValue().getValue());

		ASSERT_TRUE(data.isChanged());
		ASSERT_FALSE(data.isChanged(true));
		ASSERT_EQ(1, alloc_blocks);
	}

	TEST("should in SHADOWN state after updating")
	{
		data.update(Object(2));

		ASSERT_FALSE(data.isStable());

		ASSERT_TRUE(data.isPresent());
		ASSERT_EQ(2, data->getValue());

		ASSERT_TRUE(data.isOldPresent());
		ASSERT_EQ(2, data.getOldValue().getValue());

		ASSERT_TRUE(data.isChanged());
		ASSERT_TRUE(data.isChanged(true));
		ASSERT_EQ(2, alloc_blocks);
	}

	TEST("should use new value state after updating")
	{
		data.update(Object(3));

		ASSERT_FALSE(data.isStable());

		ASSERT_TRUE(data.isPresent());
		ASSERT_EQ(3, data->getValue());

		ASSERT_TRUE(data.isOldPresent());
		ASSERT_EQ(2, data.getOldValue().getValue());

		ASSERT_TRUE(data.isChanged());
		ASSERT_TRUE(data.isChanged(true));
		ASSERT_EQ(2, alloc_blocks);
	}

	TEST("should in ACTIVE state after updating and reverting")
	{
		data.update(Object(3));
		data.revert();

		ASSERT_TRUE(data.isStable());

		ASSERT_TRUE(data.isPresent());
		ASSERT_EQ(2, data->getValue());

		ASSERT_FALSE(data.isOldPresent());

		ASSERT_FALSE(data.isChanged());
		ASSERT_TRUE(data.isChanged(true));
		ASSERT_EQ(1, alloc_blocks);
	}

	TEST("should not allow modify")
	{
		ASSERT_NE(CUB_SUCCESS, data.modify());
	}

	TEST("should have no effect for touching")
	{
		data.touch();

		ASSERT_FALSE(data.isStable());

		ASSERT_FALSE(data.isPresent());

		ASSERT_TRUE(data.isOldPresent());
		ASSERT_EQ(2, data.getOldValue().getValue());

		ASSERT_TRUE(data.isChanged());
		ASSERT_FALSE(data.isChanged(true));
		ASSERT_EQ(1, alloc_blocks);
	}

	TEST("should have no effect for releasing")
	{
		data.release();

		ASSERT_FALSE(data.isStable());

		ASSERT_FALSE(data.isPresent());

		ASSERT_TRUE(data.isOldPresent());
		ASSERT_EQ(2, data.getOldValue().getValue());

		ASSERT_TRUE(data.isChanged());
		ASSERT_FALSE(data.isChanged(true));
		ASSERT_EQ(1, alloc_blocks);
	}
};
