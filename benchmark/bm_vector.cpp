#include "timer.hpp"
#include "vector.hpp"
#include <vector>

#include <iostream>

#ifdef FT
  #define NAMESPACE ft
#else
  #define NAMESPACE std
#endif

const int loops = 1e5;

void bm_constructor(void)
{
    for (int i = 0; i < loops; i++)
    {
        NAMESPACE::vector<int> v;
    }
}

void bm_operator_equal(void)
{
    NAMESPACE::vector<int> v1;
    NAMESPACE::vector<int> v2;
    for (int i = 0; i < loops; i++)
    {
        v1 = v2;
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
    Timer timer;

    print_title();

    // constructer
    timer.run(bm_constructor, "constructor");
    timer.run(bm_operator_equal, "operator_equal");

/*
    // Iterators
    timer.run(bm_iterator(), "bm_iterator");
    timer.run(bm_const_iterator(), "bm_const_iterator");
    timer.run(bm_reverse_iterator(), "bm_reverse_iterator");
    timer.run(bm_const_reverse_iterator(), "bm_const_reverse_iterator");

    // capacities;
    timer.run(bm_size(), "bm_size");
    timer.run(bm_max_size(), "bm_max_size");
    timer.run(bm_resize(), "bm_resize");
    timer.run(bm_capacity(), "bm_capacity");
    timer.run(bm_empty(), "bm_empty");
    timer.run(bm_reserve(), "bm_reserve");

    // element_access
    timer.run(bm_indexer(), "bm_indexer");
    timer.run(bm_at(), "bm_at");
    timer.run(bm_front(), "bm_front");
    timer.run(bm_back(), "bm_back");

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
