#include "tester.hpp"
#include "Color.hpp"
#include <iostream>

Tester::Tester() : ret_(0) {}
Tester::Tester(const Tester& other) : ret_(other.getRet()) {}
Tester::~Tester()  {}

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

int Tester::getRet(void) const
{
    return ret_;
}
