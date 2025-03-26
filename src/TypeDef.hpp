#ifndef TYPEDEF_HPP
#define TYPEDEF_HPP

#include "core/platform/Platform.hpp"

using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;
using i8 = char;
using i16 = short;
using i32 = int;
using i64 = long long;

#ifdef EUGINE_WIN64
    using usize = u64;
    using isize = i64;
#elif EUGINE_WIN32
    using usize = u32;
    using isize = i32;
#endif

#endif // TYPEDEF_HPP