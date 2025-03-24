#include "Eugine.hpp"



int main()
{
    Eugine eng;
    if(!eng.Boot())
        return -1;
    eng.Engine();
    return 0;
}
