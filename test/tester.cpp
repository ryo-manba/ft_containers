#include "tester.hpp"

#include <iostream>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

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
