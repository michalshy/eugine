#ifndef JOBSYSTEM_HPP
#define JOBSYSTEM_HPP

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

class JobSystem
{
    std::priority_queue<Job, std::vector<Job>, std::greater<Priority>> jobQueue;
public:
    JobSystem();
    ~JobSystem();
private:

};

#endif