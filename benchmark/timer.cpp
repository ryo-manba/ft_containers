#include "timer.hpp"

#define BEST_POS 33

Timer::Timer(const std::string& test_case)
 : test_case_(test_case)
{
    start_time_ = clock();
}
Timer::Timer(const Timer& other){ static_cast<void>(other); }
Timer::~Timer(void)
{
    std::cout << std::setw(BEST_POS) <<  std::left << test_case_;
    clock_t end_time = clock();
    std::cout << static_cast<double>(end_time - start_time_) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;
}

void Timer::run(void (*func)(void), const std::string& func_name) const
{
    std::cout << std::setw(BEST_POS) <<  std::left << func_name;
    clock_t start_time = clock();
    func();
    clock_t end_time = clock();
    std::cout << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;
}
