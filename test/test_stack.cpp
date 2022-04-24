#include <deque>
#include <iostream>
#include <stack>
#include <vector>

#include "debug.hpp"
#include "stack.hpp"
#include "tester.hpp"

template <typename STD, typename FT>
static bool stack_comp(const STD& st, const FT& ft)
{
    if (st.size() != ft.size()) return 1;

    STD st_copy(st);
    FT ft_copy(ft);
    const size_t sz = st.size();
    for (size_t i = 0; i < sz; ++i)
    {
        if (st_copy.top() != ft_copy.top()) return 1;
        st_copy.pop();
        ft_copy.pop();
    }
    return 0;
}

static const size_t sz = 5;

template <class T>
void init_base(T& base)
{
    for (size_t i = 0; i < sz; i++)
    {
        base.push_back(i);
    }
}

static bool test_constructor(void)
{
    std::stack<int> std_sta1;
    ft::stack<int> ft_sta1;
    if (stack_comp(std_sta1, ft_sta1)) return false;

    std::deque<int> deq;
    ft::vector<int> vec;
    init_base(deq);
    init_base(vec);

    std::stack<int> std_sta2(deq);
    ft::stack<int> ft_sta2(vec);
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
    init_base(deq);
    init_base(vec);

    std::stack<int> std_sta1(deq);
    ft::stack<int> ft_sta1(vec);
    if (stack_comp(std_sta1, ft_sta1)) return false;

    std::stack<int> std_sta2;
    ft::stack<int> ft_sta2;
    std_sta2 = std_sta1;
    ft_sta2  = ft_sta1;
    if (stack_comp(std_sta2, ft_sta2)) return false;

    return true;
}

static bool test_top(void)
{
    std::stack<int> std_sta;
    ft::stack<int> ft_sta;

    for (size_t i = 0; i < sz; ++i)
    {
        std_sta.push(i);
        ft_sta.push(i);
        if (std_sta.top() != ft_sta.top()) return false;
    }

    for (size_t i = 0; i < sz; ++i)
    {
        if (std_sta.top() != ft_sta.top()) return false;
        std_sta.pop();
        ft_sta.pop();
    }

    return true;
}

static bool test_empty(void)
{
    std::stack<int> std_sta;
    ft::stack<int> ft_sta;
    if (std_sta.empty() != ft_sta.empty()) return false;

    for (size_t i = 0; i < sz; ++i)
    {
        std_sta.push(i);
        ft_sta.push(i);
    }
    if (std_sta.empty() != ft_sta.empty()) return false;

    for (size_t i = 0; i < sz; ++i)
    {
        std_sta.pop();
        ft_sta.pop();
    }
    if (std_sta.empty() != ft_sta.empty()) return false;

    return true;
}

static bool test_size(void)
{
    std::stack<int> std_sta;
    ft::stack<int> ft_sta;
    if (std_sta.size() != ft_sta.size()) return false;

    for (size_t i = 0; i < sz; ++i)
    {
        std_sta.push(i);
        ft_sta.push(i);
    }
    if (std_sta.size() != ft_sta.size()) return false;

    for (size_t i = 0; i < sz; ++i)
    {
        std_sta.pop();
        ft_sta.pop();
    }
    if (std_sta.size() != ft_sta.size()) return false;

    return true;
}

static bool test_push(void)
{
    std::stack<int> std_sta;
    ft::stack<int> ft_sta;

    for (size_t i = 0; i < sz; ++i)
    {
        std_sta.push(i);
        ft_sta.push(i);
        if (stack_comp(std_sta, ft_sta)) return false;
    }
    return true;
}

static bool test_pop(void)
{
    std::stack<int> std_sta;
    ft::stack<int> ft_sta;

    for (size_t i = 0; i < sz; ++i)
    {
        std_sta.push(i);
        ft_sta.push(i);
    }

    for (size_t i = 0; i < sz; ++i)
    {
        if (stack_comp(std_sta, ft_sta)) return false;
        std_sta.pop();
        ft_sta.pop();
    }
    return true;
}

static bool test_operator_cmp(void)
{
    std::deque<int> deq;
    ft::vector<int> vec;
    init_base(deq);
    init_base(vec);

    ft::stack<int> ft_sta1(vec);
    ft::stack<int> ft_sta2(vec);
    ft::stack<int> ft_sta3;

    std::stack<int> std_sta1(deq);
    std::stack<int> std_sta2(deq);
    std::stack<int> std_sta3;

    if ((ft_sta1 == ft_sta2) != (std_sta1 == std_sta2)) return false;
    if ((ft_sta1 != ft_sta2) != (std_sta1 != std_sta2)) return false;
    if ((ft_sta1 < ft_sta2) != (std_sta1 < std_sta2)) return false;
    if ((ft_sta1 <= ft_sta2) != (std_sta1 <= std_sta2)) return false;
    if ((ft_sta2 > ft_sta1) != (std_sta2 > std_sta1)) return false;
    if ((ft_sta1 >= ft_sta2) != (std_sta1 >= std_sta2)) return false;

    if ((ft_sta1 == ft_sta3) != (std_sta1 == std_sta3)) return false;
    if ((ft_sta1 != ft_sta3) != (std_sta1 != std_sta3)) return false;
    if ((ft_sta1 < ft_sta3) != (std_sta1 < std_sta3)) return false;
    if ((ft_sta1 <= ft_sta3) != (std_sta1 <= std_sta3)) return false;
    if ((ft_sta1 > ft_sta3) != (std_sta1 > std_sta3)) return false;
    if ((ft_sta1 >= ft_sta3) != (std_sta1 >= std_sta3)) return false;

    return true;
}

int test_stack(void)
{
    std::cout << "==========[TEST STACK]==========" << std::endl;
    Tester tester;

    // Member functions
    tester.run(test_constructor(), "test_constructor");
    tester.run(test_operator_equal(), "test_operator_equal");

    // Element access
    tester.run(test_top(), "test_top");

    // Capacity
    tester.run(test_empty(), "test_empty");
    tester.run(test_size(), "test_size");

    // Modifilers
    tester.run(test_push(), "test_push");
    tester.run(test_pop(), "test_pop");

    // Non-member functions
    tester.run(test_operator_cmp(), "test_operator_cmp");
    return tester.get_retval();
}
