#include <iostream>
#include <map>
#include <utility>

#include "map.hpp"
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
    std::cout << "===== BENCHMARK MAP FT =====" << std::endl;
#else
    std::cout << "===== BENCHMARK MAP STL =====" << std::endl;
#endif
}

void init_map(NAMESPACE::map<int, int>& mp)
{
    for (int i = 0; i < loops; i++)
    {
        mp[i] = i;
    }
}

static void bm_constructor(void)
{
    Timer t("map::constructor");

    for (int i = 0; i < loops; i++)
    {
        NAMESPACE::map<int, int> mp;
    }
}

static void bm_operator_equal(void)
{
    NAMESPACE::map<int, int> mp1;
    NAMESPACE::map<int, int> mp2;

    init_map(mp1);
    init_map(mp2);

    Timer t("map::operator_equal");
    for (int i = 0; i < loops; i++)
    {
        mp1 = mp2;
    }
}

static void bm_get_allocator(void)
{
    NAMESPACE::map<int, int> mp;
    Timer t("map::get_allocater");

    for (int i = 0; i < loops; i++)
    {
        mp.get_allocator();
    }
}

// iterators
static void bm_iterator(void)
{
    NAMESPACE::map<int, int> mp;
    init_map(mp);

    Timer t("map::iterator");
    for (NAMESPACE::map<int, int>::iterator it = mp.begin(); it != mp.end();
         it++)
    {
        static_cast<void>(it);
    }
}

static void bm_const_iterator(void)
{
    NAMESPACE::map<int, int> mp;
    init_map(mp);

    Timer t("map::const_iterator");
    for (NAMESPACE::map<int, int>::const_iterator it = mp.begin();
         it != mp.end(); it++)
    {
        static_cast<void>(it);
    }
}

static void bm_reverse_iterator(void)
{
    NAMESPACE::map<int, int> mp;
    init_map(mp);

    Timer t("map::reverse_iterator");
    for (NAMESPACE::map<int, int>::reverse_iterator rit = mp.rbegin();
         rit != mp.rend(); rit++)
    {
        static_cast<void>(rit);
    }
}

static void bm_const_reverse_iterator(void)
{
    NAMESPACE::map<int, int> mp;
    init_map(mp);

    Timer t("map::const_reverse_iterator");
    for (NAMESPACE::map<int, int>::const_reverse_iterator rit = mp.rbegin();
         rit != mp.rend(); rit++)
    {
        static_cast<void>(rit);
    }
}

static void bm_operator_at(void)
{
    NAMESPACE::map<int, int> mp;
    Timer t("map::operator_at");

    for (int i = 0; i < loops; i++)
    {
        mp[i] = i;
    }
}

static void bm_at(void)
{
    NAMESPACE::map<int, int> mp;
    init_map(mp);

    Timer t("map::at");
    for (int i = 0; i < loops; i++)
    {
        mp.at(i) = i;
    }
}

// capacities
static void bm_empty(void)
{
    NAMESPACE::map<int, int> mp;
    Timer t("map::empty");

    for (int i = 0; i < loops; i++)
    {
        mp.empty();
    }
}

static void bm_size(void)
{
    NAMESPACE::map<int, int> mp;
    Timer t("map::size");

    for (int i = 0; i < loops; i++)
    {
        mp.size();
    }
}

static void bm_max_size(void)
{
    NAMESPACE::map<int, int> mp;
    Timer t("map::max_size");

    for (int i = 0; i < loops; i++)
    {
        mp.max_size();
    }
}

// modifiers
static void bm_clear(void)
{
    NAMESPACE::map<int, int> mp;
    Timer t("map::clear");

    for (int i = 0; i < loops; i++)
    {
        mp.clear();
    }
}

static void bm_insert(void)
{
    NAMESPACE::map<int, int> mp;
    NAMESPACE::pair<int, int> p(42, 42);

    Timer t("map::insert");
    for (int i = 0; i < loops; i++)
    {
        mp.insert(p);
    }
}

static void bm_erase(void)
{
    NAMESPACE::map<int, int> mp;
    init_map(mp);

    Timer t("map::erase");
    for (int i = 0; i < loops; i++)
    {
        mp.erase(i);
    }
}

static void bm_swap(void)
{
    NAMESPACE::map<int, int> mp1;
    NAMESPACE::map<int, int> mp2;
    init_map(mp1);

    Timer t("map::swap");
    for (int i = 0; i < loops; i++)
    {
        mp1.swap(mp2);
    }
}

// lookup
static void bm_count(void)
{
    NAMESPACE::map<int, int> mp;
    Timer t("map::count");

    for (int i = 0; i < loops; i++)
    {
        mp.count(i);
    }
}

static void bm_find(void)
{
    NAMESPACE::map<int, int> mp;
    init_map(mp);

    Timer t("map::find");
    for (int i = 0; i < loops; i++)
    {
        mp.find(i);
    }
}

static void bm_equal_range(void)
{
    NAMESPACE::map<int, int> mp;
    init_map(mp);

    Timer t("map::equal_range");
    for (int i = 0; i < loops; i++)
    {
        mp.equal_range(i);
    }
}

static void bm_lower_bound(void)
{
    NAMESPACE::map<int, int> mp;
    init_map(mp);

    Timer t("map::lower_bound");
    for (int i = 0; i < loops; i++)
    {
        mp.lower_bound(i);
    }
}

static void bm_upper_bound(void)
{
    NAMESPACE::map<int, int> mp;
    init_map(mp);

    Timer t("map::upper_bound");
    for (int i = 0; i < loops; i++)
    {
        mp.upper_bound(i);
    }
}

// observers
static void bm_key_comp(void)
{
    NAMESPACE::map<int, int> mp;
    Timer t("map::key_comp");

    for (int i = 0; i < loops; i++)
    {
        mp.key_comp();
    }
}

static void bm_value_comp(void)
{
    NAMESPACE::map<int, int> mp;
    Timer t("map::value_comp");

    for (int i = 0; i < loops; i++)
    {
        mp.value_comp();
    }
}

// non-member functions

static void bm_operator_cmp(void)
{
    NAMESPACE::map<int, int> mp1;
    NAMESPACE::map<int, int> mp2;
    init_map(mp1);
    init_map(mp2);

    Timer t("mapoperator_cmp");
    for (int i = 0; i < loops; i++)
    {
        static_cast<void>(mp1 == mp2);
        static_cast<void>(mp1 != mp2);
        static_cast<void>(mp1 > mp2);
        static_cast<void>(mp1 >= mp2);
        static_cast<void>(mp1 < mp2);
        static_cast<void>(mp1 <= mp2);
    }
    std::map<int, int> mp;
}

static void bm_std_swap(void)
{
    NAMESPACE::map<int, int> mp1;
    NAMESPACE::map<int, int> mp2;
    init_map(mp1);
    init_map(mp2);

    Timer t("map::std_swap");
    for (int i = 0; i < loops; i++)
    {
        std::swap(mp1, mp2);
    }
}

void bm_map(void)
{
    print_title();

    bm_constructor();
    bm_operator_equal();
    bm_get_allocator();

    // iterators
    bm_iterator();
    bm_const_iterator();
    bm_reverse_iterator();
    bm_const_reverse_iterator();

    // element_access
    bm_operator_at();
    bm_at();

    // capacities;
    bm_empty();
    bm_size();
    bm_max_size();

    // modifiers
    bm_clear();
    bm_insert();
    bm_erase();
    bm_swap();

    // lookup
    bm_count();
    bm_find();
    bm_equal_range();
    bm_lower_bound();
    bm_upper_bound();

    // observers
    bm_key_comp();
    bm_value_comp();

    // non-member functions
    bm_operator_cmp();
    bm_std_swap();
}
