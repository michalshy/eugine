#include "Eugine.hpp"



int main()
{
    Eugine eng;
    if(!eng.boot())
        return -1;
    eng.engine();
    return 0;

    return 0;
}
