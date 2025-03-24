#ifndef HASH_HPP
#define HASH_HPP

#include "TypeDef.hpp"
#include <string>

//lower letter s is required
static u64 ComputeHash(std::string const& s) 
{
    const u64 p = 31;
    const int m = 1e9 + 9;
    u64 hash_value = 0;
    u64 p_pow = 1;
    for(char c : s)
    {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}

#endif