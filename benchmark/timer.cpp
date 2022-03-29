#include "timer.hpp"

Timer::Timer(void) {}
Timer::Timer(const Timer& other){ static_cast<void>(other); }
Timer::~Timer(void){}

void Timer::run(void (*func)(void), const std::string& func_name) const
{
    std::cout << std::setw(25) <<  std::left << func_name;
    clock_t start_time = clock();
    func();
    clock_t end_time = clock();
    std::cout << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;
}
