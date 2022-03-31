#include <iostream>
#include <vector>

#include "timer.hpp"
#include "vector.hpp"

#ifdef FT
#define NAMESPACE ft
#else
#define NAMESPACE std
#endif

const int loops = 1e3;

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

void bm_assign(void)
{
    NAMESPACE::vector<int> v(loops);
    init_vector(v);

    Timer t("assign");
    for (int i = 0; i < loops; i++)
    {
        v.assign(i, i);
    }
}

void bm_push_back(void)
{
    NAMESPACE::vector<int> v;

    Timer t("push_back");
    for (int i = 0; i < loops; i++)
    {
        v.push_back(i);
    }
}

void bm_pop_back(void)
{
    NAMESPACE::vector<int> v(loops);
    init_vector(v);

    Timer t("pop_back");
    for (int i = 0; i < loops; i++)
    {
        v.pop_back();
    }
}

// TODO: 20倍以上
void bm_insert(void)
{
    NAMESPACE::vector<int> v;

    Timer t("insert");
    for (int i = 0; i < loops; i++)
    {
        v.insert(v.begin(), i);
    }
}

// TODO: 20倍以上
void bm_erase(void)
{
    NAMESPACE::vector<int> v(loops);
    init_vector(v);

    Timer t("erase");
    for (int i = 0; i < loops; i++)
    {
        v.erase(v.begin());
    }
}

void bm_swap(void)
{
    NAMESPACE::vector<int> v1(loops);
    NAMESPACE::vector<int> v2;
    init_vector(v1);

    Timer t("swap");
    for (int i = 0; i < loops; i++)
    {
        v1.swap(v2);
    }
}

void bm_clear(void)
{
    NAMESPACE::vector<int> v(loops);
    init_vector(v);

    Timer t("clear");
    for (int i = 0; i < loops; i++)
    {
        v.clear();
    }
}

void bm_operator(void)
{
    NAMESPACE::vector<int> v1(loops);
    NAMESPACE::vector<int> v2(loops);
    init_vector(v1);
    init_vector(v2);

    Timer t("operator");
    for (int i = 0; i < loops; i++)
    {
        static_cast<void>(v1 == v2);
        static_cast<void>(v1 != v2);
        static_cast<void>(v1 > v2);
        static_cast<void>(v1 >= v2);
        static_cast<void>(v1 < v2);
        static_cast<void>(v1 <= v2);
    }
}

void bm_get_allocator(void)
{
    NAMESPACE::vector<int> v;

    Timer t("get_allocator");
    for (int i = 0; i < loops; i++)
    {
        v.get_allocator();
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
    bm_resize();    // TODO: 20倍以上
    bm_capacity();
    bm_empty();
    bm_reserve();

    // element_access
    bm_indexer();
    bm_at();
    bm_front();
    bm_back();

    // modifiers
    bm_assign();
    bm_push_back();
    bm_pop_back();
    bm_insert();
    bm_erase();    // TODO: 20倍以上
    bm_swap();     // TODO: 20倍以上
    bm_clear();

    // operator
    bm_operator();

    // allocator
    bm_get_allocator();

    return 0;
}

int main(void)
{
    test_vector();
}
