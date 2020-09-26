#include <cctest/cctest.h>
#include <cub/base/BaseTypes.h>
#include <cub/dci/Unknown.h>
#include <cub/base/NullPtr.h>

USING_CUB_NS

namespace
{
   UNKNOWN_INTERFACE(Worker, 0x1234)
   {
       Worker() : produceNum(0)
       {
       }

       void produce()
       {
           produceNum++;
       }

       U32 getProduceNum() const
       {
           return produceNum;
       }

   private:
       U32 produceNum;
   };

   UNKNOWN_INTERFACE(SleepInfo, 0x2345)
   {
       SleepInfo() : sleeping(false)
       {
       }

       void sleep()
       {
           sleeping = true;
       }

       void wakeup()
       {
           sleeping = false;
       }

       bool isSleeping() const
       {
           return sleeping;
       }

   private:
       bool sleeping;
   };

   UNKNOWN_INTERFACE(ChargeInfo, 0x3521)
   {
       ChargeInfo() : percent(0)
       {
       }

       void charge()
       {
           percent = 100;
       }

       void cosume()
       {
           percent -= 10;
       }

       bool isNeedCharge() const
       {
           return percent == 0;
       }

   private:
       U8 percent;
   };

   struct Human : com::Unknown
                , private Worker
                , private SleepInfo
   {
       BEGIN_INTERFACE_TABLE()
           __HAS_INTERFACE(Worker)
           __HAS_INTERFACE(SleepInfo)
       END_INTERFACE_TABLE()
   };

   struct Robot : com::Unknown
                , private Worker
                , private ChargeInfo
   {
       BEGIN_INTERFACE_TABLE()
           __HAS_INTERFACE(Worker)
           __HAS_INTERFACE(ChargeInfo)
       END_INTERFACE_TABLE()
   };
}

FIXTURE(UnknownTest)
{
   TEST("should cast to the exist interface")
	{
	    Human human;
	    com::Unknown * unknown = &human;

	    Worker* worker = com::unknown_cast<Worker>(unknown);
	    ASSERT_TRUE(__NOT_NULL(worker));

	    worker->produce();
	    ASSERT_EQ(1, worker->getProduceNum());

	    SleepInfo * info = com::unknown_cast<SleepInfo>(unknown);
	    ASSERT_TRUE(__NOT_NULL(info));

	    info->sleep();
	    ASSERT_TRUE(info->isSleeping());

	    info->wakeup();
	    ASSERT_FALSE(info->isSleeping());
	}

   TEST("should return null when cast to unexist interface")
	{
	    Robot robot;
	    com::Unknown * unknown = &robot;

	    Worker* worker = com::unknown_cast<Worker>(unknown);
	    ASSERT_TRUE(__NOT_NULL(worker));

	    SleepInfo * info = com::unknown_cast<SleepInfo>(unknown);
	    ASSERT_TRUE(__IS_NULL(info));
	}
};


