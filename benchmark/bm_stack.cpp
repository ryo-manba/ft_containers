#include <iostream>
#include <stack>

#include "stack.hpp"
#include "timer.hpp"

#ifdef FT
#define NAMESPACE ft
#else
#define NAMESPACE std
#endif

const int loops = 1000;

void print_title(void)
{
#ifdef FT
    std::cout << "===== BENCHMARK STACK FT =====" << std::endl;
#else
    std::cout << "===== BENCHMARK STACK STL =====" << std::endl;
#endif
}

void init_stack(NAMESPACE::stack<int> &sta)
{
    for (int i = 0; i < loops; i++)
    {
        sta.push(i);
    }
}

static void bm_constructor(void)
{
    Timer t("stack::constructor");
    for (int i = 0; i < loops; i++)
    {
        NAMESPACE::stack<int> sta;
    }
}

static void bm_operator_equal(void)
{
    NAMESPACE::stack<int> sta1;
    NAMESPACE::stack<int> sta2;

    Timer t("stack::operator_equal");
    for (int i = 0; i < loops; i++)
    {
        sta1 = sta2;
    }
}

static void bm_size(void)
{
    NAMESPACE::stack<int> sta;
    init_stack(sta);

    Timer t("stack::size");
    for (int i = 0; i < loops; i++)
    {
        sta.size();
    }
}

static void bm_empty(void)
{
    NAMESPACE::stack<int> sta;

    Timer t("stack::empty");
    for (int i = 0; i < loops; i++)
    {
        sta.empty();
    }
}

static void bm_top(void)
{
    NAMESPACE::stack<int> sta;
    init_stack(sta);

    Timer t("stack::top");
    for (int i = 0; i < loops; i++)
    {
        sta.top() = i;
    }
}

static void bm_push(void)
{
    NAMESPACE::stack<int> sta;

    Timer t("stack::push");
    for (int i = 0; i < loops; i++)
    {
        sta.push(i);
    }
}

static void bm_pop(void)
{
    NAMESPACE::stack<int> sta;
    init_stack(sta);

    Timer t("stack::pop");
    for (int i = 0; i < loops; i++)
    {
        sta.pop();
    }
}

static void bm_operator_cmp(void)
{
    NAMESPACE::stack<int> sta1;
    NAMESPACE::stack<int> sta2;
    init_stack(sta1);
    init_stack(sta2);

    Timer t("stackoperator_cmp");
    for (int i = 0; i < loops; i++)
    {
        static_cast<void>(sta1 == sta2);
        static_cast<void>(sta1 != sta2);
        static_cast<void>(sta1 > sta2);
        static_cast<void>(sta1 >= sta2);
        static_cast<void>(sta1 < sta2);
        static_cast<void>(sta1 <= sta2);
    }
}

void bm_stack(void)
{
    print_title();

    bm_constructor();
    bm_operator_equal();

    // Capacity
    bm_size();
    bm_empty();

    // Element access
    bm_top();

    // Modifiers
    bm_push();
    bm_pop();

    // Non-member functions
    bm_operator_cmp();
}
