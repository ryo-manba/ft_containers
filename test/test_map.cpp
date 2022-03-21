#include <iostream>
#include <map>

#include "Color.hpp"
#include "debug.hpp"
#include "map.hpp"
#include <vector>
#include <utility>
#include "tester.hpp"
#include "pair.hpp"

template <class STD, class FT>
bool map_comp(const STD& st, const FT& ft)
{
    if (st.size() != ft.size()) return 1;

    typename STD::const_iterator st_it = st.begin();
    typename FT::const_iterator ft_it = ft.begin();
    for (; st_it != st.end(); ++st_it, ++ft_it)
    {
    #ifdef DEBUG
        std::cout << "-------------------" << std::endl;
        std::cout << "[st] first  : " << (*st_it).first << "\n"
                  << "     second : " << (*st_it).second << std::endl;
        std::cout << "[ft] first  : " << (*ft_it).first << "\n"
                  << "     second : " << (*ft_it).second << std::endl;
        std::cout << "-------------------" << std::endl;
    #endif
        if ((*st_it).first != (*ft_it).first) return 1;
        if ((*st_it).second != (*ft_it).second) return 1;
    }
    return 0;
}

static bool test_constructor(void)
{
    // default constructor
    std::map<std::string, int> std_mp1;
    ft::map<std::string, int> ft_mp1;
    if (map_comp(std_mp1, ft_mp1)) return false;

    std::vector<std::pair<std::string, int> > std_vec;
    std::vector<ft::pair<std::string, int> > ft_vec;
    std_vec.push_back(std::make_pair("aaa", 1));
    std_vec.push_back(std::make_pair("zzz", 2));
    std_vec.push_back(std::make_pair("abc", 3));
    ft_vec.push_back(ft::make_pair("aaa", 1));
    ft_vec.push_back(ft::make_pair("zzz", 2));
    ft_vec.push_back(ft::make_pair("abc", 3));

    // range constructor[first, last]
    std::map<std::string, int> std_mp2(std_vec.begin(), std_vec.end());
    ft::map<std::string, int> ft_mp2(ft_vec.begin(), ft_vec.end());
    if (map_comp(std_mp2, ft_mp2)) return false;

    // copy constructer
    std::map<std::string, int> std_mp3(std_mp2);
    ft::map<std::string, int> ft_mp3(ft_mp2);
    if (map_comp(std_mp3, ft_mp3)) return false;

    return true;
}

static bool test_operator_equal(void)
{
    std::vector<std::pair<std::string, int> > std_vec;
    std::vector<ft::pair<std::string, int> > ft_vec;
    std_vec.push_back(std::make_pair("aaa", 1));
    std_vec.push_back(std::make_pair("zzz", 2));
    std_vec.push_back(std::make_pair("abc", 3));
    ft_vec.push_back(ft::make_pair("aaa", 1));
    ft_vec.push_back(ft::make_pair("zzz", 2));
    ft_vec.push_back(ft::make_pair("abc", 3));

    std::map<std::string, int> std_mp1(std_vec.begin(), std_vec.end());
    ft::map<std::string, int> ft_mp1(ft_vec.begin(), ft_vec.end());

    std::map<std::string, int> std_mp2 = std_mp1;
    ft::map<std::string, int> ft_mp2 = ft_mp1;

    if (map_comp(std_mp2, ft_mp2)) return false;
    return true;
}

static bool test_iterator(void)
{
    std::vector<std::pair<std::string, int> > std_vec;
    std::vector<ft::pair<std::string, int> > ft_vec;
    std_vec.push_back(std::make_pair("aaa", 1));
    std_vec.push_back(std::make_pair("zzz", 2));
    std_vec.push_back(std::make_pair("abc", 3));
    ft_vec.push_back(ft::make_pair("aaa", 1));
    ft_vec.push_back(ft::make_pair("zzz", 2));
    ft_vec.push_back(ft::make_pair("abc", 3));

    std::map<std::string, int> std_mp(std_vec.begin(), std_vec.end());
    ft::map<std::string, int> ft_mp(ft_vec.begin(), ft_vec.end());

    std::map<std::string, int>::iterator std_it = std_mp.begin();
    std::map<std::string, int>::iterator std_ite = std_mp.end();

    ft::map<std::string, int>::iterator ft_it = ft_mp.begin();
    ft::map<std::string, int>::iterator ft_ite = ft_mp.end();

    // keyはconstなので代入不可
    for (; std_it != std_ite; ++std_it)
    {
        (*std_it).second = 42;
    }
    for (; ft_it != ft_ite; ++ft_it)
    {
        (*ft_it).second = 42;
    }
    if (map_comp(std_mp, ft_mp)) return false;
    return true;
}

static bool test_const_iterator(void)
{
    std::vector<std::pair<std::string, int> > std_vec;
    std::vector<ft::pair<std::string, int> > ft_vec;
    std_vec.push_back(std::make_pair("aaa", 1));
    std_vec.push_back(std::make_pair("zzz", 2));
    std_vec.push_back(std::make_pair("abc", 3));
    ft_vec.push_back(ft::make_pair("aaa", 1));
    ft_vec.push_back(ft::make_pair("zzz", 2));
    ft_vec.push_back(ft::make_pair("abc", 3));

    const std::map<std::string, int> std_mp(std_vec.begin(), std_vec.end());
    const ft::map<std::string, int> ft_mp(ft_vec.begin(), ft_vec.end());

    std::map<std::string, int>::const_iterator std_it = std_mp.begin();
    std::map<std::string, int>::const_iterator std_ite = std_mp.end();

    ft::map<std::string, int>::const_iterator ft_it = ft_mp.begin();
    ft::map<std::string, int>::const_iterator ft_ite = ft_mp.end();

    for (; std_it != std_ite; ++std_it)
    {
        std_vec.push_back(*std_it);
    }
    for (; ft_it != ft_ite; ++ft_it)
    {
        ft_vec.push_back(*ft_it);
    }
    const std::map<std::string, int> std_mp2(std_vec.begin(), std_vec.end());
    const ft::map<std::string, int> ft_mp2(ft_vec.begin(), ft_vec.end());

    if (map_comp(std_mp2, ft_mp2)) return false;
    return true;
}

static bool test_reverse_iterator(void)
{
    std::vector<std::pair<std::string, int> > std_vec;
    std::vector<ft::pair<std::string, int> > ft_vec;
    std_vec.push_back(std::make_pair("aaa", 1));
    std_vec.push_back(std::make_pair("zzz", 2));
    std_vec.push_back(std::make_pair("abc", 3));
    ft_vec.push_back(ft::make_pair("aaa", 1));
    ft_vec.push_back(ft::make_pair("zzz", 2));
    ft_vec.push_back(ft::make_pair("abc", 3));

    std::map<std::string, int> std_mp(std_vec.begin(), std_vec.end());
    ft::map<std::string, int> ft_mp(ft_vec.begin(), ft_vec.end());

    std::map<std::string, int>::reverse_iterator std_rit = std_mp.rbegin();
    std::map<std::string, int>::reverse_iterator std_rite = std_mp.rend();

    ft::map<std::string, int>::reverse_iterator ft_rit = ft_mp.rbegin();
    ft::map<std::string, int>::reverse_iterator ft_rite = ft_mp.rend();

    // keyはconstなので代入不可
    for (; std_rit != std_rite; ++std_rit)
    {
        (*std_rit).second = 42;
    }
    for (; ft_rit != ft_rite; ++ft_rit)
    {
        (*ft_rit).second = 42;
    }
    if (map_comp(std_mp, ft_mp)) return false;
    return true;
}

static bool test_const_reverse_iterator(void)
{
    std::vector<std::pair<std::string, int> > std_vec;
    std::vector<ft::pair<std::string, int> > ft_vec;
    std_vec.push_back(std::make_pair("aaa", 1));
    std_vec.push_back(std::make_pair("zzz", 2));
    std_vec.push_back(std::make_pair("abc", 3));
    ft_vec.push_back(ft::make_pair("aaa", 1));
    ft_vec.push_back(ft::make_pair("zzz", 2));
    ft_vec.push_back(ft::make_pair("abc", 3));

    const std::map<std::string, int> std_mp(std_vec.begin(), std_vec.end());
    const ft::map<std::string, int> ft_mp(ft_vec.begin(), ft_vec.end());

    std::map<std::string, int>::const_reverse_iterator std_rit = std_mp.rbegin();
    std::map<std::string, int>::const_reverse_iterator std_rite = std_mp.rend();

    ft::map<std::string, int>::const_reverse_iterator ft_rit = ft_mp.rbegin();
    ft::map<std::string, int>::const_reverse_iterator ft_rite = ft_mp.rend();

    for (; std_rit != std_rite; ++std_rit)
    {
        std_vec.push_back(*std_rit);
    }
    for (; ft_rit != ft_rite; ++ft_rit)
    {
        ft_vec.push_back(*ft_rit);
    }
    const std::map<std::string, int> std_mp2(std_vec.begin(), std_vec.end());
    const ft::map<std::string, int> ft_mp2(ft_vec.begin(), ft_vec.end());

    if (map_comp(std_mp2, ft_mp2)) return false;
    return true;
}



int test_map(void)
{
    Tester tester;
    std::cout << "-----[TEST MAP]-----" << std::endl;

    // constructer
    tester.run(test_constructor(), "test_constructor");
    tester.run(test_operator_equal(), "test_operator_equal");

    // Iterators
    tester.run(test_iterator(), "test_iterator");
    tester.run(test_const_iterator(), "test_const_iterator");
    tester.run(test_reverse_iterator(), "test_reverse_iterator");
    tester.run(test_const_reverse_iterator(), "test_const_reverse_iterator");
/*
    // capacities;
    tester.run(test_size(), "test_size");
    tester.run(test_max_size(), "test_max_size");
    tester.run(test_resize(), "test_resize");
    tester.run(test_capacity(), "test_capacity");
    tester.run(test_empty(), "test_empty");
    tester.run(test_reserve(), "test_reserve");

    // element_access
    tester.run(test_indexer(), "test_indexer");
    tester.run(test_at(), "test_at");
    tester.run(test_front(), "test_front");
    tester.run(test_back(), "test_back");

    // modifiers
    tester.run(test_assign(), "test_assign");
    tester.run(test_push_back(), "test_push_back");
    tester.run(test_pop_back(), "test_pop_back");
    tester.run(test_insert(), "test_insert");
    tester.run(test_erase(), "test_erase");
    tester.run(test_swap(), "test_swap");
    tester.run(test_clear(), "test_clear");

    // operator
    tester.run(test_operator(), "test_operator");

    // allocator
    tester.run(test_get_allocator(), "test_get_allocator");
*/
    return tester.getRet();
}
