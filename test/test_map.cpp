#include <iostream>
#include <map>
#include <utility>
#include <vector>

#include "Color.hpp"
#include "debug.hpp"
#include "map.hpp"
#include "pair.hpp"
#include "tester.hpp"

/**
 * @return 完全一致 0, 一致しない場合 1
 */

template <class STD, class FT>
bool map_comp(const STD& st, const FT& ft)
{
    if (st.size() != ft.size()) return 1;

    typename STD::const_iterator st_it = st.begin();
    typename FT::const_iterator ft_it  = ft.begin();
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

std::map<std::string, int> init_std_map(void)
{
    std::vector<std::pair<std::string, int> > vec;
    vec.push_back(std::make_pair("aaa", 1));
    vec.push_back(std::make_pair("zzz", 2));
    vec.push_back(std::make_pair("abc", 3));

    std::map<std::string, int> mp(vec.begin(), vec.end());
    return mp;
}

ft::map<std::string, int> init_ft_map(void)
{
    std::vector<ft::pair<std::string, int> > vec;
    vec.push_back(ft::make_pair("aaa", 1));
    vec.push_back(ft::make_pair("zzz", 2));
    vec.push_back(ft::make_pair("abc", 3));

    ft::map<std::string, int> mp(vec.begin(), vec.end());
    return mp;
}

const std::map<std::string, int> init_const_std_map(void)
{
    std::vector<std::pair<std::string, int> > vec;
    vec.push_back(std::make_pair("aaa", 1));
    vec.push_back(std::make_pair("zzz", 2));
    vec.push_back(std::make_pair("abc", 3));

    const std::map<std::string, int> mp(vec.begin(), vec.end());
    return mp;
}

const ft::map<std::string, int> init_const_ft_map(void)
{
    std::vector<ft::pair<std::string, int> > vec;
    vec.push_back(ft::make_pair("aaa", 1));
    vec.push_back(ft::make_pair("zzz", 2));
    vec.push_back(ft::make_pair("abc", 3));

    const ft::map<std::string, int> mp(vec.begin(), vec.end());
    return mp;
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
    std::map<std::string, int> std_mp1 = init_std_map();
    ft::map<std::string, int> ft_mp1   = init_ft_map();

    std::map<std::string, int> std_mp2 = std_mp1;
    ft::map<std::string, int> ft_mp2   = ft_mp1;

    if (map_comp(std_mp2, ft_mp2)) return false;
    return true;
}

static bool test_iterator(void)
{
    std::map<std::string, int> std_mp = init_std_map();
    ft::map<std::string, int> ft_mp   = init_ft_map();

    std::map<std::string, int>::iterator std_it  = std_mp.begin();
    std::map<std::string, int>::iterator std_ite = std_mp.end();

    ft::map<std::string, int>::iterator ft_it  = ft_mp.begin();
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
    const std::map<std::string, int> std_mp = init_const_std_map();
    const ft::map<std::string, int> ft_mp   = init_const_ft_map();

    std::map<std::string, int>::const_iterator std_it  = std_mp.begin();
    std::map<std::string, int>::const_iterator std_ite = std_mp.end();

    ft::map<std::string, int>::const_iterator ft_it  = ft_mp.begin();
    ft::map<std::string, int>::const_iterator ft_ite = ft_mp.end();

    std::vector<std::pair<std::string, int> > std_vec;
    std::vector<ft::pair<std::string, int> > ft_vec;
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
    std::map<std::string, int> std_mp = init_std_map();
    ft::map<std::string, int> ft_mp   = init_ft_map();

    std::map<std::string, int>::reverse_iterator std_rit  = std_mp.rbegin();
    std::map<std::string, int>::reverse_iterator std_rite = std_mp.rend();

    ft::map<std::string, int>::reverse_iterator ft_rit  = ft_mp.rbegin();
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
    const std::map<std::string, int> std_mp = init_std_map();
    const ft::map<std::string, int> ft_mp   = init_ft_map();

    std::map<std::string, int>::const_reverse_iterator std_rit =
        std_mp.rbegin();
    std::map<std::string, int>::const_reverse_iterator std_rite = std_mp.rend();

    ft::map<std::string, int>::const_reverse_iterator ft_rit  = ft_mp.rbegin();
    ft::map<std::string, int>::const_reverse_iterator ft_rite = ft_mp.rend();

    std::vector<std::pair<std::string, int> > std_vec;
    std::vector<ft::pair<std::string, int> > ft_vec;
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

static bool test_empty(void)
{
    std::map<std::string, int> std_mp1;
    ft::map<std::string, int> ft_mp1;
    if (std_mp1.empty() != ft_mp1.empty()) return false;

    std::map<std::string, int> std_mp2 = init_std_map();
    ft::map<std::string, int> ft_mp2   = init_ft_map();
    if (std_mp2.empty() != ft_mp2.empty()) return false;

// TODO: clearテスト後に追加する
//    std_mp2.clear();
//    ft_mp2.clear();
//    if (std_mp2.empty() != ft_mp2.empty()) return false;
    return true;
}

static bool test_size(void)
{
    std::map<std::string, int> std_mp1;
    ft::map<std::string, int> ft_mp1;
    if (std_mp1.size() != ft_mp1.size()) return false;

    std::map<std::string, int> std_mp2 = init_std_map();
    ft::map<std::string, int> ft_mp2   = init_ft_map();
    if (std_mp2.size() != ft_mp2.size()) return false;

//TODO: insert, eraseテスト後に追加する
//    std_mp2.insert(std::make_pair("Key", 42));
//    ft_mp2.insert(ft::make_pair("Key", 42));
//    if (std_mp2.size() != ft_mp2.size()) return false;
//    std_mp2.erase("Key");
//    ft_mp2.erase("Key");
//    if (std_mp2.size() != ft_mp2.size()) return false;

    return true;
}

static bool test_max_size(void)
{
    std::map<std::string, int> std_mp1;
    ft::map<std::string, int> ft_mp1;
    if (std_mp1.max_size() != ft_mp1.max_size()) return false;

    std::map<int, int> std_mp2;
    ft::map<int, int> ft_mp2 ;
    if (std_mp2.max_size() != ft_mp2.max_size()) return false;

    std::map<long, char> std_mp3;
    ft::map<long, char> ft_mp3 ;
    if (std_mp3.max_size() != ft_mp3.max_size()) return false;

    return true;
}

// TODO: insert with hintを作成する
/*
static bool test_indexer(void)
{
    std::map<std::string, int> std_mp;
    ft::map<std::string, int> ft_mp;

    std_mp["aaa"] = 1;
    std_mp["zzz"] = 2;
    std_mp["abc"] = 3;

    ft_mp["aaa"] = 1;
    ft_mp["zzz"] = 2;
    ft_mp["abc"] = 3;
    if (map_comp(std_mp, ft_mp)) return false;

    if (std_mp["aaa"] != ft_mp["aaa"]) return false;
    if (std_mp["zzz"] != ft_mp["zzz"]) return false;
    if (std_mp["abc"] != ft_mp["abc"]) return false;

    return false;
}
*/

// TODO: 例外のテスト追加する
static bool test_at(void)
{
    std::map<std::string, int> std_mp = init_std_map();
    ft::map<std::string, int> ft_mp   = init_ft_map();

    if (std_mp.at("aaa") != ft_mp.at("aaa")) return false;

    std_mp.at("aaa") = 42;
    ft_mp.at("aaa") = 42;
    if (map_comp(std_mp, ft_mp)) return false;

    return true;
}

static bool test_clear(void)
{
    std::map<std::string, int> std_mp = init_std_map();
    ft::map<std::string, int> ft_mp   = init_ft_map();

    std_mp.clear();
    ft_mp.clear();

    if (std_mp.size() != ft_mp.size()) return false;
    if (std_mp.empty() != ft_mp.empty()) return false;
    return true;
}

static bool test_insert(void)
{
    std::map<std::string, int> std_mp;
    ft::map<std::string, int> ft_mp;
    std::map<std::string, int>::iterator std_it;
    ft::map<std::string, int>::iterator ft_it;
    std::pair<std::map<std::string, int>::iterator, bool> std_p;
    ft::pair<ft::map<std::string, int>::iterator, bool> ft_p;

    std_p = std_mp.insert(std::make_pair("aaa", 1));
    ft_p = ft_mp.insert(ft::make_pair("aaa", 1));

    if (std_p.first->first != ft_p.first->first) return false;
    if (std_p.first->second != ft_p.first->second) return false;
    if (std_p.second != ft_p.second) return false;

    if (map_comp(std_mp, ft_mp)) return false;

    std_p = std_mp.insert(std::make_pair("zzz", 2));
    ft_p = ft_mp.insert(ft::make_pair("zzz", 2));

    if (std_p.first->first != ft_p.first->first) return false;
    if (std_p.first->second != ft_p.first->second) return false;
    if (std_p.second != ft_p.second) return false;

    std_p = std_mp.insert(std::make_pair("abc", 3));
    ft_p = ft_mp.insert(ft::make_pair("abc", 3));

    if (std_p.first->first != ft_p.first->first) return false;
    if (std_p.first->second != ft_p.first->second) return false;
    if (std_p.second != ft_p.second) return false;

    if (map_comp(std_mp, ft_mp)) return false;

    std_p = std_mp.insert(std::make_pair("abc", 42));
    ft_p = ft_mp.insert(ft::make_pair("abc", 42));
    if (std_p.first->first != ft_p.first->first) return false;
    if (std_p.first->second != ft_p.first->second) return false;
    if (std_p.second != ft_p.second) return false;

    if (map_comp(std_mp, ft_mp)) return false;

    return true;
}
/*
static bool test_erase(void)
{
    return false;
}

static bool test_swap(void)
{
    return false;
}
*/
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

    // capacities;
    tester.run(test_empty(), "test_empty");
    tester.run(test_size(), "test_size");
    tester.run(test_max_size(), "test_max_size");

    // element_access
//    tester.run(test_indexer(), "test_indexer");
    tester.run(test_at(), "test_at");

    // modifiers
    tester.run(test_clear(), "test_clear");
    tester.run(test_insert(), "test_insert");
//    tester.run(test_erase(), "test_erase");
//    tester.run(test_swap(), "test_swap");

    /*
        // operator
        tester.run(test_operator(), "test_operator");

        // allocator
        tester.run(test_get_allocator(), "test_get_allocator");
    */
    return tester.getRet();
}
