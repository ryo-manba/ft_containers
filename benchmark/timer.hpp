#ifndef TIMER_HPP
#define TIMER_HPP

#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>

class Timer
{
public:
    Timer(void);
    Timer(const Timer& other);
    ~Timer(void);

    void run(void (*func)(void), const std::string& func_name) const;
private:
};

#endif
