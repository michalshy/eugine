#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#if defined (_WIN64)
    #define EUGINE_WIN64
#elif defined (_WIN32)
    #define EUGINE_WIN32
#elif defined (__METAL__)
    #define EUGINE_MAC
#elif defined (__linux__)
    #define EUGINE_LINUX
#endif

#endif