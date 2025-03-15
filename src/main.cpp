#include "Eugine.hpp"

int main()
{
    Eugine eng;
    if(!eng.boot())
        return -1;
    eng.loop();
    return 0;
}