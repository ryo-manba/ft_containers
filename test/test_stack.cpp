#include <deque>
#include <iostream>
#include <stack>
#include <vector>

#include "Color.hpp"
#include "debug.hpp"
#include "stack.hpp"
#include "tester.hpp"

template <typename STD, typename FT>
static bool stack_comp(const STD& st, const FT& ft)
{
    if (st.size() != ft.size()) return 1;

    STD st_copy     = st;
    FT ft_copy      = ft;
    const size_t sz = st.size();
    for (size_t i = 0; i < sz; ++i)
    {
        if (st_copy.top() != ft_copy.top()) return 1;
        st_copy.pop();
        ft_copy.pop();
    }
    return 0;
}

static bool test_constructor(void)
{
    std::stack<int> std_sta1;
    ft::stack<int> ft_sta1;
    if (stack_comp(std_sta1, ft_sta1)) return false;

    std::deque<int> deq;
    ft::vector<int> vec;
    for (size_t i = 0; i < 5; ++i)
    {
        deq.push_back(i);
        vec.push_back(i);
    }
    std::stack<int> std_sta2(deq);    // overload (2)
    ft::stack<int> ft_sta2(vec);      // overload (2)
    if (stack_comp(std_sta2, ft_sta2)) return false;

    std::stack<int> std_sta3(std_sta2);
    ft::stack<int> ft_sta3(ft_sta2);
    if (stack_comp(std_sta3, ft_sta3)) return false;
    return true;
}

static bool test_operator_equal(void)
{
    std::deque<int> deq;
    ft::vector<int> vec;
    for (size_t i = 0; i < 5; ++i)
    {
        deq.push_back(i);
        vec.push_back(i);
    }
    std::stack<int> std_sta1(deq);
    ft::stack<int> ft_sta1(vec);
    if (stack_comp(std_sta1, ft_sta1)) return false;

    std::stack<int> std_sta2 = std_sta1;
    ft::stack<int> ft_sta2   = ft_sta1;
    if (stack_comp(std_sta2, ft_sta2)) return false;
    return true;
}

static bool test_empty()
{
    std::stack<int> std_sta;
    ft::stack<int> ft_sta;

    if (std_sta.empty() != ft_sta.empty()) return false;

    for (size_t i = 0; i < 5; ++i)
    {
        std_sta.push(i);
        ft_sta.push(i);
    }
    if (std_sta.empty() != ft_sta.empty()) return false;

    for (size_t i = 0; i < 5; ++i)
    {
        std_sta.pop();
        ft_sta.pop();
    }
    if (std_sta.empty() != ft_sta.empty()) return false;
    return true;
}

static bool test_size()
{
    std::stack<int> std_sta;
    ft::stack<int> ft_sta;

    if (std_sta.size() != ft_sta.size()) return false;

    for (size_t i = 0; i < 5; ++i)
    {
        std_sta.push(i);
        ft_sta.push(i);
    }
    if (std_sta.size() != ft_sta.size()) return false;

    for (size_t i = 0; i < 5; ++i)
    {
        std_sta.pop();
        ft_sta.pop();
    }
    if (std_sta.size() != ft_sta.size()) return false;
    return true;
}

static bool test_top()
{
    std::stack<int> std_sta;
    ft::stack<int> ft_sta;

    for (size_t i = 0; i < 5; ++i)
    {
        std_sta.push(i);
        ft_sta.push(i);
        if (std_sta.top() != ft_sta.top()) return false;
    }

    for (size_t i = 0; i < 5; ++i)
    {
        if (std_sta.top() != ft_sta.top()) return false;
        std_sta.pop();
        ft_sta.pop();
    }
    return true;
}

static bool test_push()
{
    std::stack<int> std_sta;
    ft::stack<int> ft_sta;

    for (size_t i = 0; i < 5; ++i)
    {
        std_sta.push(i);
        ft_sta.push(i);
        if (stack_comp(std_sta, ft_sta)) return false;
    }
    return true;
}

static bool test_pop()
{
    std::stack<int> std_sta;
    ft::stack<int> ft_sta;

    for (size_t i = 0; i < 5; ++i)
    {
        std_sta.push(i);
        ft_sta.push(i);
    }

    for (size_t i = 0; i < 5; ++i)
    {
        if (stack_comp(std_sta, ft_sta)) return false;
        std_sta.pop();
        ft_sta.pop();
    }
    return true;
}

static bool test_operator()
{
    ft::stack<int> ft_sta1;
    ft::stack<int> ft_sta2;
    ft::stack<int> ft_sta3;

    for (size_t i = 0; i < 5; ++i)
    {
        ft_sta1.push(i);
        ft_sta2.push(i);
        ft_sta3.push(i + i);
    }

    if (!(ft_sta1 == ft_sta2)) return false;
    if (ft_sta1 != ft_sta2) return false;
    if (ft_sta1 < ft_sta2) return false;
    if (!(ft_sta1 <= ft_sta2)) return false;
    if (ft_sta2 > ft_sta1) return false;
    if (!(ft_sta1 >= ft_sta2)) return false;

    if (ft_sta1 == ft_sta3) return false;
    if (!(ft_sta1 != ft_sta3)) return false;
    if (!(ft_sta1 < ft_sta3)) return false;
    if (!(ft_sta1 <= ft_sta3)) return false;
    if (ft_sta1 > ft_sta3) return false;
    if (ft_sta1 >= ft_sta3) return false;

    return true;
}

int test_stack(void)
{
    std::cout << "-----[TEST STACK]-----" << std::endl;
    Tester tester;

    // construct
    tester.run(test_constructor(), "test_constructor");
    tester.run(test_operator_equal(), "test_operator_equal");
    tester.run(test_empty(), "test_empty");
    tester.run(test_size(), "test_size");
    tester.run(test_top(), "test_top");
    tester.run(test_push(), "test_push");
    tester.run(test_pop(), "test_pop");
    tester.run(test_operator(), "test_operator");
    return tester.getRet();
}