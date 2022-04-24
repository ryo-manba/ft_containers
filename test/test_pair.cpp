#include <iostream>
#include <string>
#include <utility>

#include "pair.hpp"
#include "tester.hpp"

template <typename STD, typename FT>
int pair_comp(const STD& st, const FT& ft)
{
    if (st.first != ft.first) return 1;
    if (st.second != ft.second) return 1;
    return 0;
}

static bool test_constructor(void)
{
    std::pair<int, float> std_p1;
    ft::pair<int, float> ft_p1;
    if (pair_comp(std_p1, ft_p1)) return false;

    std::pair<int, double> std_p2(42, 3.1415);
    ft::pair<int, double> ft_p2(42, 3.1415);
    if (pair_comp(std_p2, ft_p2)) return false;

    std::pair<char, int> std_p3(std_p2);
    ft::pair<char, int> ft_p3(ft_p2);
    if (pair_comp(std_p3, ft_p3)) return false;
    return true;
}

static bool test_operator_equal(void)
{
    std::pair<int, int> std_p1(42, -42);
    ft::pair<int, int> ft_p1(42, -42);

    std::pair<int, int> std_p2 = std_p1;
    ft::pair<int, int> ft_p2   = ft_p1;
    if (pair_comp(std_p2, ft_p2)) return false;
    return true;
}

static bool test_operator_cmp(void)
{
    ft::pair<int, int> ft_p1(42, 42);
    ft::pair<int, int> ft_p2(42, -42);
    ft::pair<int, int> ft_p3(-42, 42);

    std::pair<int, int> std_p1(42, 42);
    std::pair<int, int> std_p2(42, -42);
    std::pair<int, int> std_p3(-42, 42);

    if ((ft_p1 == ft_p2) != (std_p1 == std_p2)) return false;
    if ((ft_p1 != ft_p2) != (std_p1 != std_p2)) return false;
    if ((ft_p1 < ft_p2) != (std_p1 < std_p2)) return false;
    if ((ft_p1 <= ft_p2) != (std_p1 <= std_p2)) return false;
    if ((ft_p1 > ft_p2) != (std_p1 > std_p2)) return false;
    if ((ft_p1 >= ft_p2) != (std_p1 >= std_p2)) return false;

    if ((ft_p1 == ft_p3) != (std_p1 == std_p3)) return false;
    if ((ft_p1 != ft_p3) != (std_p1 != std_p3)) return false;
    if ((ft_p1 < ft_p3) != (std_p1 < std_p3)) return false;
    if ((ft_p1 <= ft_p3) != (std_p1 <= std_p3)) return false;
    if ((ft_p1 > ft_p3) != (std_p1 > std_p3)) return false;
    if ((ft_p1 >= ft_p3) != (std_p1 >= std_p3)) return false;

    return true;
}

static bool test_make_pair(void)
{
    std::pair<int, int> std_p;
    ft::pair<int, int> ft_p;

    for (int i = 0; i < 5; ++i)
    {
        std_p = std::make_pair(i, i);
        ft_p  = ft::make_pair(i, i);
        if (pair_comp(std_p, ft_p)) return false;
    }
    return true;
}

int test_pair(void)
{
    Tester tester;
    std::cout << "==========[TEST PAIR]==========" << std::endl;

    tester.run(test_constructor(), "test_constructor");
    tester.run(test_operator_equal(), "test_operator_equal");
    tester.run(test_operator_cmp(), "test_operator_cmp");
    tester.run(test_make_pair(), "test_make_pair");
    return tester.get_retval();
}
