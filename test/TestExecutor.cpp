#include <cctest/cctest.h>
#include <cub/sched/Executor.h>

USING_CUB_NS

namespace
{
    int fib(int n)
    {
        if(n == 0) return 0;
        return n + fib(n-1);
    }

    struct Fib
    {
        Fib(int n) : n(n)
        {
        }

        int operator()() const
        {
            return fib(n);
        }

    private:
        int n;
    };
}


FIXTURE(ExecutorTest)
{
    Executor executor{2};

    TEST("should execute normal function")
	{
	    auto result = executor.execute(fib, 5);
	    ASSERT_EQ(15, result.get());
	}

	TEST("should execute lambda")
	{
	    const int num = 5;
	    auto result = executor.execute([=](){ return fib(num); });
	    ASSERT_EQ(15, result.get());
	}

	TEST("should execute functor")
	{
	    auto result = executor.execute(Fib(5));
	    ASSERT_EQ(15, result.get());
	}

	TEST("should execute muti task concurrently")
	{
	    auto result1 = executor.execute(Fib(5));
	    auto result2 = executor.execute(Fib(6));

	    ASSERT_EQ(15, result1.get());
	    ASSERT_EQ(21, result2.get());
	}
};


