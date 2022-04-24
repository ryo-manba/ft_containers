#ifndef TESTER_HPP
#define TESTER_HPP

#include <string>

class Tester
{
public:
    Tester(void);
    Tester(const Tester& other);
    ~Tester(void);
    void run(bool result, std::string test_case);
    int get_retval(void) const;

private:
    int ret_;
};

#endif
