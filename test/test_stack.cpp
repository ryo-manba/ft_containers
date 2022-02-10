#include <iostream>
#include <stack>
#include <deque>
#include <vector>

#include "Color.hpp"
#include "debug.hpp"
#include "stack.hpp"
#include "tester.hpp"

template<typename STD, typename FT>
bool stack_comp(const STD& st, const FT& ft)
{
    if (st.size() != ft.size()) return 1;

    STD st_copy = st;
    FT  ft_copy = ft;
    const size_t sz = st.size();
    for (size_t i = 0; i < sz; ++i)
    {
        if (st_copy.top() != ft_copy.top()) return 1;
        st_copy.pop();
        ft_copy.pop();
    }
    return 0;
}

static bool test_constructorator(void)
{
    std::stack<int> std_sta1;
    ft::stack<int> ft_sta1;
    if (stack_comp(std_sta1, ft_sta1)) return false;

    std::stack<int> std_sta2(std_sta1);
    ft::stack<int> ft_sta2(ft_sta1);
    if (stack_comp(std_sta2, ft_sta2)) return false;

    std::deque<int> deq;
    ft::vector<int> vec;
    rep(i,5)
    {
        deq.push_back(i);
        vec.push_back(i);
    }
    std::stack<int> std_sta3(deq); // overload (2)
    ft::stack<int> ft_sta3(vec);   // overload (2)
    if (stack_comp(std_sta3, ft_sta3)) return false;
    return true;
}

int test_stack(void)
{
    Tester tester;
    std::cout << "-----[TEST STACK]-----" << std::endl;

    // construct
    tester.run(test_constructorator(), "test_constructorator");
    return tester.getRet();
}
