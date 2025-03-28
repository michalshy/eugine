#ifndef JOBSYSTEM_HPP
#define JOBSYSTEM_HPP

#include "TypeDef.hpp"
#include <atomic>
#include <thread>
#include <queue>

enum class Priority
{
    LOW,
    MEDIUM,
    HIGH,
    CRITICAL
};

struct Job {
    void (*entry)(void*);
    Priority priority;
    void* params[];
};

struct AtomicCounter {
    std::atomic<u32> counter;
    AtomicCounter() : counter(0) {}
    AtomicCounter(u32 initial) : counter(initial) {}
};

class JobSystem
{
    std::thread* workerThreads;
    std::atomic<u8> status;
    u32 threadCount;
    std::priority_queue<Job, std::vector<Job>, std::greater<Priority>> jobQueue;
public:
    JobSystem();

    void KickJob();

    ~JobSystem();
private:
    void WorkerLoop(u32 i);
};

#endif