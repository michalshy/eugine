#ifndef JOBSYSTEMUTILS_HPP
#define JOBSYSTEMUTILS_HPP

#include "TypeDef.hpp"
#include <thread>

#ifdef EUGINE_WIN64
    #include <windows.h>
#endif
static u32 GetCoreCount()
{
    //Try C++11
    //may return 0 when not able to detect
    u32 processor_count = std::thread::hardware_concurrency();
    
    //Try different methods
    #ifdef EUGINE_WIN64
        SYSTEM_INFO sysinfo;
        GetSystemInfo(&sysinfo);
        return sysinfo.dwNumberOfProcessors;
    #elif EUGINE_WIN32
        SYSTEM_INFO sysinfo;
        GetSystemInfo(&sysinfo);
        return sysinfo.dwNumberOfProcessors;
    #elif EUGINE_MAC
        int mib[4];
        int numCPU;
        std::size_t len = sizeof(numCPU); 
        
        /* set the mib for hw.ncpu */
        mib[0] = CTL_HW;
        mib[1] = HW_AVAILCPU;  // alternatively, try HW_NCPU;
        
        /* get the number of CPUs from the system */
        sysctl(mib, 2, &numCPU, &len, NULL, 0);
        
        if (numCPU < 1) 
        {
            mib[1] = HW_NCPU;
            sysctl(mib, 2, &numCPU, &len, NULL, 0);
            if (numCPU < 1)
                numCPU = 1;
        }
        return numCPU;
    #elif EUGINE_LINUX
        return sysconf(_SC_NPROCESSORS_ONLN);
    #endif
    return 1;
}



#endif