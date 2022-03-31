#include <iostream>
#include <vector>

#include "timer.hpp"
#include "vector.hpp"

#ifdef FT
#define NAMESPACE ft
#else
#define NAMESPACE std
#endif

const int loops = 1e5;

void init_vector(NAMESPACE::vector<int> &v)
{
    for (int i = 0; i < loops; i++)
    {
        v[i] = i;
    }
}

void bm_constructor(void)
{
    Timer t("constructor");
    for (int i = 0; i < loops; i++)
    {
        NAMESPACE::vector<int> v;
    }
}

void bm_operator_equal(void)
{
    NAMESPACE::vector<int> v1;
    NAMESPACE::vector<int> v2;

    Timer t("operator_equal");
    for (int i = 0; i < loops; i++)
    {
        v1 = v2;
    }
}

void bm_iterator(void)
{
    NAMESPACE::vector<int> v(loops);
    init_vector(v);

    Timer t("iterator");
    for (NAMESPACE::vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        static_cast<void>(it);
    }
}

void bm_const_iterator(void)
{
    NAMESPACE::vector<int> v(loops);
    init_vector(v);

    Timer t("const_iterator");
    for (NAMESPACE::vector<int>::const_iterator it = v.begin(); it != v.end();
         it++)
    {
        static_cast<void>(it);
    }
}

void bm_reverse_iterator(void)
{
    NAMESPACE::vector<int> v(loops);
    init_vector(v);

    Timer t("reverse_iterator");
    for (NAMESPACE::vector<int>::reverse_iterator rit = v.rbegin();
         rit != v.rend(); rit++)
    {
        static_cast<void>(rit);
    }
}

void bm_const_reverse_iterator(void)
{
    NAMESPACE::vector<int> v(loops);
    init_vector(v);

    Timer t("const_reverse_iterator");
    for (NAMESPACE::vector<int>::const_reverse_iterator rit = v.rbegin();
         rit != v.rend(); rit++)
    {
        static_cast<void>(rit);
    }
}

void bm_size(void)
{
    NAMESPACE::vector<int> v(loops);

    Timer t("size");
    for (int i = 0; i < loops; i++)
    {
        v.size();
    }
}

void bm_max_size(void)
{
    NAMESPACE::vector<int> v;

    Timer t("max_size");
    for (int i = 0; i < loops; i++)
    {
        v.max_size();
    }
}

// TODO: 20倍以上かかる
void bm_resize(void)
{
    NAMESPACE::vector<int> v;

    Timer t("resize");
    for (int i = 0; i < 1000; i++)
    {
        v.resize(i);
    }
}


void bm_capacity(void)
{
    NAMESPACE::vector<int> v(loops);
    init_vector(v);

    Timer t("capacity");
    for (int i = 0; i < loops; i++)
    {
        v.capacity();
    }
}
void bm_empty(void)
{
    NAMESPACE::vector<int> v;

    Timer t("empty");
    for (int i = 0; i < loops; i++)
    {
        v.empty();
    }
}

void bm_reserve(void)
{
    NAMESPACE::vector<int> v;

    Timer t("reserve");
    for (int i = 0; i < loops; i++)
    {
        v.reserve(i);
    }
}

void bm_indexer(void)
{
    NAMESPACE::vector<int> v(loops);
    init_vector(v);

    Timer t("indexer");
    for (int i = 0; i < loops; i++)
    {
        v[i] = i;
    }
}

void bm_at(void)
{
    NAMESPACE::vector<int> v(loops);
    init_vector(v);

    Timer t("at");
    for (int i = 0; i < loops; i++)
    {
        v.at(i) = i;
    }
}

void bm_front(void)
{
    NAMESPACE::vector<int> v(loops);
    init_vector(v);

    Timer t("front");
    for (int i = 0; i < loops; i++)
    {
        v.front() = i;
    }
}

void bm_back(void)
{
    NAMESPACE::vector<int> v(loops);
    init_vector(v);

    Timer t("back");
    for (int i = 0; i < loops; i++)
    {
        v.back() = i;
    }
}

void print_title(void)
{
#ifdef FT
    std::cout << "===== BENCHMARK VECTOR FT =====" << std::endl;
#else
    std::cout << "===== BENCHMARK VECTOR STL =====" << std::endl;
#endif
}

int test_vector(void)
{
    print_title();

    // constructer
    bm_constructor();
    bm_operator_equal();

    // iterators
    bm_iterator();
    bm_const_iterator();
    bm_reverse_iterator();
    bm_const_reverse_iterator();

    // capacities;
    bm_size();
    bm_max_size();
    bm_resize();
    bm_capacity();
    bm_empty();
    bm_reserve();

    // element_access
    bm_indexer();
    bm_at();
    bm_front();
    bm_back();

    /*

        // modifiers
        timer.run(bm_assign(), "bm_assign");
        timer.run(bm_push_back(), "bm_push_back");
        timer.run(bm_pop_back(), "bm_pop_back");
        timer.run(bm_insert(), "bm_insert");
        timer.run(bm_erase(), "bm_erase");
        timer.run(bm_swap(), "bm_swap");
        timer.run(bm_clear(), "bm_clear");

        // operator
        timer.run(bm_operator(), "bm_operator");

        // allocator
        timer.run(bm_get_allocator(), "bm_get_allocator");
    */
    return 0;
}

int main(void)
{
    test_vector();
}
