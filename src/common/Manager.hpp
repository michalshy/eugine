#ifndef MANAGER_HPP
#define MANAGER_HPP

class Manager
{
public:
    Manager() = default;
    virtual bool startUp() = 0;
    virtual bool shutDown() = 0;
    virtual ~Manager(){};
};

#endif // MANAGER_HPP