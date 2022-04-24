#include "tester.hpp"

#ifdef LEAK
__attribute__((destructor)) static void destructor()
{
    system("leaks -q a.out");
}
#endif

int test_vector(void);
int test_stack(void);
int test_pair(void);
int test_map(void);

int main(void)
{
    int res = 0;

    res += test_vector();
    res += test_stack();
    res += test_pair();
    res += test_map();
    return res;
}
