#include "JobSystem.hpp"
#include "JobSystemUtils.hpp"
#include <cstdio>

JobSystem::JobSystem(){ 
    status = 1;
    threadCount = GetCoreCount();
    workerThreads = new std::thread[threadCount];
    for (u32 i = 0; i < threadCount; ++i) {
        workerThreads[i] = std::thread(&JobSystem::WorkerLoop, this, i);
    }
}

JobSystem::~JobSystem(){ 
    for (u32 i = 0; i < threadCount; ++i) {
        workerThreads[i].join();
    }
    delete [] workerThreads;
 }

void JobSystem::WorkerLoop(u32 i) {
    while(status != 0)
    {
        printf("Running core %d\n", i);
        //sleep
        std::this_thread::sleep_for(std::chrono::milliseconds(900));
    }
}
