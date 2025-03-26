#include "Eugine.hpp"
#include "diagnostic/logger/Logger.hpp"

Logger logger;

int main()
{
    Eugine eng;
    if(!eng.Boot())
        return -1;
    eng.Engine();
    return 0;
}
