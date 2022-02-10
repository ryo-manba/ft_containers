#include <iostream>
#include <vector>

#include "Color.hpp"
#include "debug.hpp"
#include "vector.hpp"
#include "tester.hpp"

/************************/
// leaks
#ifdef LEAK
__attribute__((destructor)) static void destructor()
{
    system("leaks -q a.out");
}
#endif
/************************/

int test_vector(void);
int test_stack(void);

int main(void)
{
    int res = 0;

//    res += test_vector();
    res += test_stack();
    return res;
}
