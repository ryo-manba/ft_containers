#include <iostream>
#include <vector>

#include "timer.hpp"
#include "vector.hpp"

#ifdef FT
#define NAMESPACE ft
#else
#define NAMESPACE std
#endif

const int loops = 1000;

static void print_title(void)
{
#ifdef FT
    std::cout << "===== BENCHMARK VECTOR FT =====" << std::endl;
#else
    std::cout << "===== BENCHMARK VECTOR STL =====" << std::endl;
#endif
}

static void init_vector(NAMESPACE::vector<int> &v)
{
    for (int i = 0; i < loops; i++)
    {
        v[i] = i;
    }
}

// Member functions
static void bm_constructor_default(void)
{
    Timer t("vector::constructor_default");
    for (int i = 0; i < loops; i++)
    {
        NAMESPACE::vector<int> v;
    }
}

static void bm_constructor_range(void)
{
    NAMESPACE::vector<int> vec(loops);
    init_vector(vec);

    Timer t("vector::constructor_range");
    for (int i = 0; i < loops; i++)
    {
        NAMESPACE::vector<int> v(vec.begin(), vec.end());
    }
}

static void bm_constructor_copy(void)
{
    NAMESPACE::vector<int> vec(loops);
    init_vector(vec);

    Timer t("vector::constructor_copy");
    for (int i = 0; i < loops; i++)
    {
        NAMESPACE::vector<int> v(vec);
    }
}

static void bm_constructor_fill(void)
{
    Timer t("vector::constructor_fill");
    for (int i = 0; i < loops; i++)
    {
        NAMESPACE::vector<int> v(i, i);
    }
}

static void bm_operator_equal(void)
{
    NAMESPACE::vector<int> v1;
    NAMESPACE::vector<int> v2;

    Timer t("vector::operator_equal");
    for (int i = 0; i < loops; i++)
    {
        v1 = v2;
    }
}

static void bm_assign(void)
{
    NAMESPACE::vector<int> v;

    Timer t("vector::assign");
    for (int i = 0; i < loops; i++)
    {
        v.assign(i, i);
    }
}

static void bm_get_allocator(void)
{
    NAMESPACE::vector<int> v;

    Timer t("vector::get_allocator");
    for (int i = 0; i < loops; i++)
    {
        v.get_allocator();
    }
}

// Element access
static void bm_at(void)
{
    NAMESPACE::vector<int> v(loops);
    init_vector(v);

    Timer t("vector::at");
    for (int i = 0; i < loops; i++)
    {
        v.at(i) = i;
    }
}

static void bm_operator_at(void)
{
    NAMESPACE::vector<int> v(loops);
    init_vector(v);

    Timer t("vector::operator_at");
    for (int i = 0; i < loops; i++)
    {
        v[i] = i;
    }
}

static void bm_front(void)
{
    NAMESPACE::vector<int> v(loops);
    init_vector(v);

    Timer t("vector::front");
    for (int i = 0; i < loops; i++)
    {
        v.front() = i;
    }
}

static void bm_back(void)
{
    NAMESPACE::vector<int> v(loops);
    init_vector(v);

    Timer t("vector::back");
    for (int i = 0; i < loops; i++)
    {
        v.back() = i;
    }
}

static void bm_data(void)
{
    NAMESPACE::vector<int> v(loops);
    init_vector(v);

    Timer t("vector::data");
    for (int i = 0; i < loops; i++)
    {
        v.data();
    }
}

// Iterators
static void bm_iterator(void)
{
    NAMESPACE::vector<int> v(loops);
    init_vector(v);

    Timer t("vector::iterator");
    for (NAMESPACE::vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        static_cast<void>(it);
    }
}

static void bm_const_iterator(void)
{
    NAMESPACE::vector<int> v(loops);
    init_vector(v);

    Timer t("vector::const_iterator");
    for (NAMESPACE::vector<int>::const_iterator it = v.begin(); it != v.end();
         it++)
    {
        static_cast<void>(it);
    }
}

static void bm_reverse_iterator(void)
{
    NAMESPACE::vector<int> v(loops);
    init_vector(v);

    Timer t("vector::reverse_iterator");
    for (NAMESPACE::vector<int>::reverse_iterator rit = v.rbegin();
         rit != v.rend(); rit++)
    {
        static_cast<void>(rit);
    }
}

static void bm_const_reverse_iterator(void)
{
    NAMESPACE::vector<int> v(loops);
    init_vector(v);

    Timer t("vector::const_reverse_iterator");
    for (NAMESPACE::vector<int>::const_reverse_iterator rit = v.rbegin();
         rit != v.rend(); rit++)
    {
        static_cast<void>(rit);
    }
}

// Capacity
static void bm_empty(void)
{
    NAMESPACE::vector<int> v;

    Timer t("vector::empty");
    for (int i = 0; i < loops; i++)
    {
        v.empty();
    }
}

static void bm_size(void)
{
    NAMESPACE::vector<int> v(loops);

    Timer t("vector::size");
    for (int i = 0; i < loops; i++)
    {
        v.size();
    }
}

static void bm_max_size(void)
{
    NAMESPACE::vector<int> v;

    Timer t("vector::max_size");
    for (int i = 0; i < loops; i++)
    {
        v.max_size();
    }
}

static void bm_reserve(void)
{
    NAMESPACE::vector<int> v;

    Timer t("vector::reserve");
    for (int i = 0; i < loops; i++)
    {
        v.reserve(i);
    }
}

static void bm_capacity(void)
{
    NAMESPACE::vector<int> v(loops);
    init_vector(v);

    Timer t("vector::capacity");
    for (int i = 0; i < loops; i++)
    {
        v.capacity();
    }
}

// Modifiers
static void bm_clear(void)
{
    NAMESPACE::vector<int> v(loops);
    init_vector(v);

    Timer t("vector::clear");
    for (int i = 0; i < loops; i++)
    {
        v.clear();
    }
}

// beginへのinsertはstlの場合にmoveを利用しているので20倍は実現できない。
static void bm_insert(void)
{
    NAMESPACE::vector<int> v;

    Timer t("vector::insert");
    for (int i = 0; i < loops; i++)
    {
        v.insert(v.end(), i);
    }
}

static void bm_erase(void)
{
    NAMESPACE::vector<int> v(loops);
    init_vector(v);

    Timer t("vector::erase");
    for (int i = 0; i < loops; i++)
    {
        v.erase(v.end() - 1);
    }
}

static void bm_push_back(void)
{
    NAMESPACE::vector<int> v;

    Timer t("vector::push_back");
    for (int i = 0; i < loops; i++)
    {
        v.push_back(i);
    }
}

static void bm_pop_back(void)
{
    NAMESPACE::vector<int> v(loops);
    init_vector(v);

    Timer t("vector::pop_back");
    for (int i = 0; i < loops; i++)
    {
        v.pop_back();
    }
}

static void bm_resize(void)
{
    NAMESPACE::vector<int> v;

    Timer t("vector::resize");
    for (int i = 0; i < loops; i++)
    {
        v.resize(i);
    }
}

static void bm_swap(void)
{
    NAMESPACE::vector<int> v1(loops);
    NAMESPACE::vector<int> v2;
    init_vector(v1);

    Timer t("vector::swap");
    for (int i = 0; i < loops; i++)
    {
        v1.swap(v2);
    }
}

// Non-member functions
static void bm_operator_cmp(void)
{
    NAMESPACE::vector<int> v1(loops);
    NAMESPACE::vector<int> v2(loops);
    init_vector(v1);
    init_vector(v2);

    Timer t("vector::operator_cmp");
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

static void bm_std_swap(void)
{
    NAMESPACE::vector<int> v1(loops);
    NAMESPACE::vector<int> v2;
    init_vector(v1);

    Timer t("vector::std_swap");
    for (int i = 0; i < loops; i++)
    {
        std::swap(v1, v2);
    }
}

void bm_vector(void)
{
    print_title();

    // Memver functions
    bm_constructor_default();
    bm_constructor_range();
    bm_constructor_copy();
    bm_constructor_fill();
    bm_operator_equal();
    bm_assign();
    bm_get_allocator();

    // Element access
    bm_at();
    bm_operator_at();
    bm_front();
    bm_back();
    bm_data();

    // Iterators
    bm_iterator();
    bm_const_iterator();
    bm_reverse_iterator();
    bm_const_reverse_iterator();

    // Element access
    bm_empty();
    bm_size();
    bm_max_size();
    bm_reserve();
    bm_capacity();

    // Modifiers
    bm_clear();
    bm_insert();
    bm_erase();
    bm_push_back();
    bm_pop_back();
    bm_resize();
    bm_swap();

    // Non-member functions
    bm_operator_cmp();
    bm_std_swap();
}
