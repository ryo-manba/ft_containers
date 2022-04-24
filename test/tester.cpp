#include "tester.hpp"

#include <iostream>

#include "color.hpp"

Tester::Tester()
    : ret_(0)
{
}
Tester::Tester(const Tester& other)
    : ret_(other.get_retval())
{
}
Tester::~Tester()
{
}

void Tester::run(bool result, std::string test_case)
{
    if (result == true)
    {
        std::cout << GREEN << "[OK]" << RESET;
    }
    else
    {
        std::cout << RED << "[KO]" << RESET;
    }
    std::cout << " : " << YELLOW << test_case << RESET << std::endl;

    if (result == false)
        ret_ += 1;
}

int Tester::get_retval(void) const
{
    return ret_;
}
