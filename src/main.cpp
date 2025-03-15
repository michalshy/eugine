#include "Eugine.hpp"

int main()
{
    Eugine eng;
    if(!eng.init())
        return -1;
    eng.run();
    return 0;
}