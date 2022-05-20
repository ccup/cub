#include <cub/sched/Executor.h>
#include <cub/algo/loop.h>

CUB_NS_BEGIN

Executor::Executor(size_t threadNum) : stop(false)
{
    for(size_t i = 0; i < threadNum; i++)
    {
        workers.emplace_back([this]{ threadRun(); });
    }
}

Executor::~Executor()
 {
     SYNCHRONIZED(tasksMutex)
     {
         stop = true;
     }
     condition.notify_all();

     for(std::thread &worker : workers)
     {
         worker.join();
     }
 }

void Executor::threadRun()
{
    while(true)
    {
        std::function<void()> task;

        SYNCHRONIZED(tasksMutex)
        {
            this->condition.wait(LOCKER(tasksMutex).getLocker(),
                [this]{ return this->stop || !this->tasks.empty(); });

            if(this->stop && this->tasks.empty()) return;
            task = std::move(this->tasks.front());
            this->tasks.pop();
        }

        task();
    }
}

CUB_NS_END
