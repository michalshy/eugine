#include "Idk.hpp"

int main()
{
    Idk eng;
    if(!eng.init())
        return -1;
    eng.run();
    return 0;
}