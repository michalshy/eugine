#ifndef TYPEDEF_HPP
#define TYPEDEF_HPP

using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;
using i8 = char;
using i16 = short;
using i32 = int;
using i64 = long long;

static void ZeroMemory(void* ptr, u32 size)
{
    u8* p = static_cast<u8*>(ptr);
    for(u32 i = 0; i < size; i++)
    {
        p[i] = 0;
    }
}

#endif // TYPEDEF_HPP