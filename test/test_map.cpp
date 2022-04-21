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
static bool map_comp(const STD& st, const FT& ft)
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
        if (st_it->first != ft_it->first) return 1;
        if (st_it->second != ft_it->second) return 1;
    }
    return 0;
}

template <class STD, class FT>
static bool pair_comp(const STD& st, const FT& ft)
{
    if (st.first != ft.first) return 1;
    if (st.second != ft.second) return 1;
    return 0;
}

static std::map<std::string, int> create_std_map(void)
{
    std::vector<std::pair<std::string, int> > vec;
    vec.push_back(std::make_pair("aaa", 1));
    vec.push_back(std::make_pair("zzz", 2));
    vec.push_back(std::make_pair("abc", 3));

    std::map<std::string, int> mp(vec.begin(), vec.end());
    return mp;
}

static ft::map<std::string, int> create_ft_map(void)
{
    std::vector<ft::pair<std::string, int> > vec;
    vec.push_back(ft::make_pair("aaa", 1));
    vec.push_back(ft::make_pair("zzz", 2));
    vec.push_back(ft::make_pair("abc", 3));

    ft::map<std::string, int> mp(vec.begin(), vec.end());
    return mp;
}

static const std::map<std::string, int> create_const_std_map(void)
{
    std::vector<std::pair<std::string, int> > vec;
    vec.push_back(std::make_pair("aaa", 1));
    vec.push_back(std::make_pair("zzz", 2));
    vec.push_back(std::make_pair("abc", 3));

    const std::map<std::string, int> mp(vec.begin(), vec.end());
    return mp;
}

static const ft::map<std::string, int> create_const_ft_map(void)
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
    std::map<std::string, int> std_mp1 = create_std_map();
    ft::map<std::string, int> ft_mp1   = create_ft_map();

    std::map<std::string, int> std_mp2;
    ft::map<std::string, int> ft_mp2;
    std_mp2 = std_mp1;
    ft_mp2  = ft_mp1;

    if (map_comp(std_mp2, ft_mp2)) return false;
    return true;
}

static bool test_get_allocator(void)
{
    std::map<int, int, std::allocator<int> > std_mp1;
    ft::map<int, int, std::allocator<int> > ft_mp1;
    if (std_mp1.get_allocator() != ft_mp1.get_allocator()) return false;

    std::map<int, int, std::allocator<long> > std_mp2;
    ft::map<int, int, std::allocator<long> > ft_mp2;
    if (std_mp2.get_allocator() != ft_mp2.get_allocator()) return false;

    return true;
}

static bool test_at(void)
{
    std::map<std::string, int> std_mp = create_std_map();
    ft::map<std::string, int> ft_mp   = create_ft_map();

    if (std_mp.at("aaa") != ft_mp.at("aaa")) return false;

    std_mp.at("aaa") = 42;
    ft_mp.at("aaa")  = 42;
    if (map_comp(std_mp, ft_mp)) return false;

    return true;
}

static bool test_operator_at(void)
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

    return true;
}

static bool test_iterator(void)
{
    std::map<std::string, int> std_mp = create_std_map();
    ft::map<std::string, int> ft_mp   = create_ft_map();

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
    const std::map<std::string, int> std_mp = create_const_std_map();
    const ft::map<std::string, int> ft_mp   = create_const_ft_map();

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
    std::map<std::string, int> std_mp = create_std_map();
    ft::map<std::string, int> ft_mp   = create_ft_map();

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
    const std::map<std::string, int> std_mp = create_const_std_map();
    const ft::map<std::string, int> ft_mp   = create_const_ft_map();

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

    std::map<std::string, int> std_mp2 = create_std_map();
    ft::map<std::string, int> ft_mp2   = create_ft_map();
    if (std_mp2.empty() != ft_mp2.empty()) return false;

    std_mp2.clear();
    ft_mp2.clear();
    if (std_mp2.empty() != ft_mp2.empty()) return false;
    return true;
}

static bool test_size(void)
{
    std::map<std::string, int> std_mp1;
    ft::map<std::string, int> ft_mp1;
    if (std_mp1.size() != ft_mp1.size()) return false;

    std::map<std::string, int> std_mp2 = create_std_map();
    ft::map<std::string, int> ft_mp2   = create_ft_map();
    if (std_mp2.size() != ft_mp2.size()) return false;

    std_mp2.insert(std::make_pair("Key", 42));
    ft_mp2.insert(ft::make_pair("Key", 42));
    if (std_mp2.size() != ft_mp2.size()) return false;

    std_mp2.erase("Key");
    ft_mp2.erase("Key");
    if (std_mp2.size() != ft_mp2.size()) return false;

    return true;
}

static bool test_max_size(void)
{
    std::map<std::string, int> std_mp1;
    ft::map<std::string, int> ft_mp1;
    if (std_mp1.max_size() != ft_mp1.max_size()) return false;

    std::map<int, int> std_mp2;
    ft::map<int, int> ft_mp2;
    if (std_mp2.max_size() != ft_mp2.max_size()) return false;

    std::map<long, char> std_mp3;
    ft::map<long, char> ft_mp3;
    if (std_mp3.max_size() != ft_mp3.max_size()) return false;

    return true;
}

static bool test_clear(void)
{
    std::map<std::string, int> std_mp = create_std_map();
    ft::map<std::string, int> ft_mp   = create_ft_map();

    std_mp.clear();
    ft_mp.clear();

    if (map_comp(std_mp, ft_mp)) return false;
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
    ft_p  = ft_mp.insert(ft::make_pair("aaa", 1));

    if (pair_comp(*(std_p.first), *(ft_p.first))) return false;
    if (std_p.second != ft_p.second) return false;

    if (map_comp(std_mp, ft_mp)) return false;

    std_p = std_mp.insert(std::make_pair("zzz", 2));
    ft_p  = ft_mp.insert(ft::make_pair("zzz", 2));

    if (pair_comp(*(std_p.first), *(ft_p.first))) return false;
    if (std_p.second != ft_p.second) return false;

    std_p = std_mp.insert(std::make_pair("abc", 3));
    ft_p  = ft_mp.insert(ft::make_pair("abc", 3));

    if (pair_comp(*(std_p.first), *(ft_p.first))) return false;
    if (std_p.second != ft_p.second) return false;

    if (map_comp(std_mp, ft_mp)) return false;

    std_p = std_mp.insert(std::make_pair("abc", 42));
    ft_p  = ft_mp.insert(ft::make_pair("abc", 42));
    if (pair_comp(*(std_p.first), *(ft_p.first))) return false;
    if (std_p.second != ft_p.second) return false;

    if (map_comp(std_mp, ft_mp)) return false;
    return true;
}

static bool test_insert_with_hint(void)
{
    std::map<int, int> std_mp;
    ft::map<int, int> ft_mp;
    std::map<int, int>::iterator std_it;
    ft::map<int, int>::iterator ft_it;

    for (int i = 0; i < 5; i++)
    {
        std_mp[i] = i;
        ft_mp[i]  = i;
    }

    std_it = std_mp.end();
    ft_it  = ft_mp.end();
    for (int i = 5; i < 10; i++)
    {
        std_it = std_mp.insert(std_it, std::make_pair(i, i));
        ft_it  = ft_mp.insert(ft_it, ft::make_pair(i, i));

        if (pair_comp(*std_it, *ft_it)) return false;
        if (map_comp(std_mp, ft_mp)) return false;
    }

    for (int i = 10; i < 15; i++)
    {
        std_it = std_mp.insert(std_mp.begin(), std::make_pair(i, i));
        ft_it  = ft_mp.insert(ft_mp.begin(), ft::make_pair(i, i));

        if (pair_comp(*std_it, *ft_it)) return false;
        if (map_comp(std_mp, ft_mp)) return false;
    }

    return true;
}

static bool test_insert_range(void)
{
    std::vector<std::pair<std::string, int> > std_vec;
    std_vec.push_back(std::make_pair("aaa", 1));
    std_vec.push_back(std::make_pair("zzz", 2));
    std_vec.push_back(std::make_pair("abc", 3));

    std::vector<ft::pair<std::string, int> > ft_vec;
    ft_vec.push_back(ft::make_pair("aaa", 1));
    ft_vec.push_back(ft::make_pair("zzz", 2));
    ft_vec.push_back(ft::make_pair("abc", 3));

    std::map<std::string, int> std_mp;
    ft::map<std::string, int> ft_mp;

    std_mp.insert(std_vec.begin(), std_vec.end());
    ft_mp.insert(ft_vec.begin(), ft_vec.end());
    if (map_comp(std_mp, ft_mp)) return false;

    return true;
}

static bool test_erase(void)
{
    std::map<std::string, int> std_mp1 = create_std_map();
    ft::map<std::string, int> ft_mp1   = create_ft_map();

    // void erase( iterator pos );
    std_mp1.erase(std_mp1.begin());
    ft_mp1.erase(ft_mp1.begin());
    if (map_comp(std_mp1, ft_mp1)) return false;

    // void erase( iterator first, iterator last );
    std_mp1.erase(std_mp1.begin(), std_mp1.end());
    ft_mp1.erase(ft_mp1.begin(), ft_mp1.end());
    if (map_comp(std_mp1, ft_mp1)) return false;

    std::map<std::string, int> std_mp2 = create_std_map();
    ft::map<std::string, int> ft_mp2   = create_ft_map();

    const std::string key1  = "aaa";
    const std::string key2  = "zzz";
    const std::string key3  = "abc";
    const std::string dummy = "TACOPII";

    // size_type erase( const Key& key );
    // 削除した要素数を返す
    if (std_mp2.erase(key1) != ft_mp2.erase(key1)) return false;
    if (map_comp(std_mp2, ft_mp2)) return false;

    if (std_mp2.erase(key2) != ft_mp2.erase(key2)) return false;
    if (map_comp(std_mp2, ft_mp2)) return false;

    if (std_mp2.erase(key3) != ft_mp2.erase(key3)) return false;
    if (map_comp(std_mp2, ft_mp2)) return false;

    if (std_mp2.erase(dummy) != ft_mp2.erase(dummy)) return false;
    if (map_comp(std_mp2, ft_mp2)) return false;

    return true;
}

static bool test_swap(void)
{
    std::map<std::string, int> std_mp1 = create_std_map();
    ft::map<std::string, int> ft_mp1   = create_ft_map();
    std::map<std::string, int> std_mp2;
    ft::map<std::string, int> ft_mp2;

    std_mp1.swap(std_mp2);
    ft_mp1.swap(ft_mp2);
    if (map_comp(std_mp1, ft_mp1)) return false;
    if (map_comp(std_mp2, ft_mp2)) return false;

    return true;
}

static bool test_count(void)
{
    std::map<std::string, int> std_mp = create_std_map();
    ft::map<std::string, int> ft_mp   = create_ft_map();

    const std::string key1  = "aaa";
    const std::string key2  = "zzz";
    const std::string key3  = "abc";
    const std::string dummy = "TACOPII";

    if (std_mp.count(key1) != ft_mp.count(key1)) return false;
    if (std_mp.count(key2) != ft_mp.count(key2)) return false;
    if (std_mp.count(key3) != ft_mp.count(key3)) return false;
    if (std_mp.count(dummy) != ft_mp.count(dummy)) return false;

    return true;
}

static bool test_find(void)
{
    std::map<std::string, int> std_mp = create_std_map();
    ft::map<std::string, int> ft_mp   = create_ft_map();
    std::map<std::string, int>::iterator std_it;
    ft::map<std::string, int>::iterator ft_it;
    const std::string key1  = "aaa";
    const std::string dummy = "TACOPII";

    std_it = std_mp.find(key1);
    ft_it  = ft_mp.find(key1);
    if (pair_comp(*std_it, *ft_it)) return false;

    std_it = std_mp.find(dummy);
    ft_it  = ft_mp.find(dummy);
    if (std_it != std_mp.end()) return false;
    if (ft_it != ft_mp.end()) return false;

    const std::map<std::string, int> const_std_mp = create_const_std_map();
    const ft::map<std::string, int> const_ft_mp   = create_const_ft_map();

    std::map<std::string, int>::const_iterator std_cit1 =
        const_std_mp.find(key1);
    ft::map<std::string, int>::const_iterator ft_cit1 = const_ft_mp.find(key1);
    if (pair_comp(*std_cit1, *ft_cit1)) return false;

    std::map<std::string, int>::const_iterator std_cit2 =
        const_std_mp.find(dummy);
    ft::map<std::string, int>::const_iterator ft_cit2 = const_ft_mp.find(dummy);
    if (std_cit2 != const_std_mp.end()) return false;
    if (ft_cit2 != const_ft_mp.end()) return false;

    return true;
}

static bool test_equal_range(void)
{
    std::map<std::string, int> std_mp = create_std_map();
    ft::map<std::string, int> ft_mp   = create_ft_map();
    typedef std::map<std::string, int>::iterator st_iterator;
    typedef ft::map<std::string, int>::iterator ft_iterator;

    std::pair<st_iterator, st_iterator> std_p;
    ft::pair<ft_iterator, ft_iterator> ft_p;

    const std::string key1  = "aaa";
    const std::string key2  = "zzz";
    const std::string key3  = "abc";
    const std::string dummy = "TACOPII";

    // コンテナ内の与えられたキーを持つすべての要素を含む範囲を返します。
    // 1つはキーより小さくない最初の要素を指すもの、もう1つはキーより大きい最初の要素を指すものである
    // keyより小さくない要素がない場合、過去の終了（end()を参照）イテレータが最初の要素として返されます。
    // 同様に、keyより大きい要素がない場合、past-the-endイテレータが2番目の要素として返される。
    std_p = std_mp.equal_range(key1);
    ft_p  = ft_mp.equal_range(key1);

    if (std_p.first != std_mp.lower_bound(key1)) return false;
    if (std_p.second != std_mp.upper_bound(key1)) return false;
    if (ft_p.first != ft_mp.lower_bound(key1)) return false;
    if (ft_p.second != ft_mp.upper_bound(key1)) return false;

    std_p = std_mp.equal_range(key2);
    ft_p  = ft_mp.equal_range(key2);

    if (std_p.first != std_mp.lower_bound(key2)) return false;
    if (std_p.second != std_mp.upper_bound(key2)) return false;
    if (ft_p.first != ft_mp.lower_bound(key2)) return false;
    if (ft_p.second != ft_mp.upper_bound(key2)) return false;

    std_p = std_mp.equal_range(key3);
    ft_p  = ft_mp.equal_range(key3);

    if (std_p.first != std_mp.lower_bound(key3)) return false;
    if (std_p.second != std_mp.upper_bound(key3)) return false;
    if (ft_p.first != ft_mp.lower_bound(key3)) return false;
    if (ft_p.second != ft_mp.upper_bound(key3)) return false;

    std_p = std_mp.equal_range(dummy);
    ft_p  = ft_mp.equal_range(dummy);

    if (std_p.first != std_mp.lower_bound(dummy)) return false;
    if (std_p.second != std_mp.upper_bound(dummy)) return false;
    if (ft_p.first != ft_mp.lower_bound(dummy)) return false;
    if (ft_p.second != ft_mp.upper_bound(dummy)) return false;

    return true;
}

static bool test_equal_range_const(void)
{
    const std::map<std::string, int> std_mp = create_std_map();
    const ft::map<std::string, int> ft_mp   = create_ft_map();
    typedef std::map<std::string, int>::const_iterator st_iterator;
    typedef ft::map<std::string, int>::const_iterator ft_iterator;

    std::pair<st_iterator, st_iterator> std_p;
    ft::pair<ft_iterator, ft_iterator> ft_p;

    const std::string key1  = "aaa";
    const std::string key2  = "zzz";
    const std::string key3  = "abc";
    const std::string dummy = "TACOPII";

    std_p = std_mp.equal_range(key1);
    ft_p  = ft_mp.equal_range(key1);

    if (std_p.first != std_mp.lower_bound(key1)) return false;
    if (std_p.second != std_mp.upper_bound(key1)) return false;
    if (ft_p.first != ft_mp.lower_bound(key1)) return false;
    if (ft_p.second != ft_mp.upper_bound(key1)) return false;

    std_p = std_mp.equal_range(key2);
    ft_p  = ft_mp.equal_range(key2);

    if (std_p.first != std_mp.lower_bound(key2)) return false;
    if (std_p.second != std_mp.upper_bound(key2)) return false;
    if (ft_p.first != ft_mp.lower_bound(key2)) return false;
    if (ft_p.second != ft_mp.upper_bound(key2)) return false;

    std_p = std_mp.equal_range(key3);
    ft_p  = ft_mp.equal_range(key3);

    if (std_p.first != std_mp.lower_bound(key3)) return false;
    if (std_p.second != std_mp.upper_bound(key3)) return false;
    if (ft_p.first != ft_mp.lower_bound(key3)) return false;
    if (ft_p.second != ft_mp.upper_bound(key3)) return false;

    std_p = std_mp.equal_range(dummy);
    ft_p  = ft_mp.equal_range(dummy);

    if (std_p.first != std_mp.lower_bound(dummy)) return false;
    if (std_p.second != std_mp.upper_bound(dummy)) return false;
    if (ft_p.first != ft_mp.lower_bound(dummy)) return false;
    if (ft_p.second != ft_mp.upper_bound(dummy)) return false;

    return true;
}

static bool test_lower_bound(void)
{
    std::map<std::string, int> std_mp = create_std_map();
    ft::map<std::string, int> ft_mp   = create_ft_map();
    std::map<std::string, int>::iterator std_it;
    ft::map<std::string, int>::iterator ft_it;

    const std::string key1  = "aaa";
    const std::string dummy = "zzzzz";

    std_it = std_mp.lower_bound(key1);
    ft_it  = ft_mp.lower_bound(key1);
    if (pair_comp(*std_it, *ft_it)) return false;

    std_it = std_mp.lower_bound("xxx");
    ft_it  = ft_mp.lower_bound("xxx");
    if (pair_comp(*std_it, *ft_it)) return false;

    std_it = std_mp.lower_bound(dummy);
    ft_it  = ft_mp.lower_bound(dummy);
    if (std_it != std_mp.end()) return false;
    if (ft_it != ft_mp.end()) return false;

    return true;
}

static bool test_lower_bound_const(void)
{
    std::map<std::string, int> std_mp = create_std_map();
    ft::map<std::string, int> ft_mp   = create_ft_map();
    typedef std::map<std::string, int>::const_iterator st_const_iterator;
    typedef ft::map<std::string, int>::const_iterator ft_const_iterator;

    const std::string key1  = "aaa";
    const std::string dummy = "zzzzz";

    st_const_iterator std_cit1 = std_mp.lower_bound(key1);
    ft_const_iterator ft_cit1  = ft_mp.lower_bound(key1);
    if (pair_comp(*std_cit1, *ft_cit1)) return false;

    st_const_iterator std_cit2 = std_mp.lower_bound("xxx");
    ft_const_iterator ft_cit2  = ft_mp.lower_bound("xxx");
    if (pair_comp(*std_cit2, *ft_cit2)) return false;

    st_const_iterator std_cit3 = std_mp.lower_bound(dummy);
    ft_const_iterator ft_cit3  = ft_mp.lower_bound(dummy);
    if (std_cit3 != std_mp.end()) return false;
    if (ft_cit3 != ft_mp.end()) return false;

    return true;
}

static std::map<int, int> create_int_std_map(void)
{
    std::vector<std::pair<int, int> > v(100);
    for (int i = 0; i < 100; i++) v[i] = std::make_pair(i, i);

    std::map<int, int> mp(v.begin(), v.end());
    return mp;
}

static ft::map<int, int> create_int_ft_map(void)
{
    std::vector<ft::pair<int, int> > v(100);
    for (int i = 0; i < 100; i++) v[i] = ft::make_pair(i, i);

    ft::map<int, int> mp(v.begin(), v.end());
    return mp;
}

static bool test_upper_bound(void)
{
    std::map<std::string, int> std_mp1 = create_std_map();
    ft::map<std::string, int> ft_mp1   = create_ft_map();
    std::map<std::string, int>::iterator std_it1;
    ft::map<std::string, int>::iterator ft_it1;

    const std::string key1 = "aaa";
    const std::string key2 = "zzz";

    std_it1 = std_mp1.upper_bound(key1);
    ft_it1  = ft_mp1.upper_bound(key1);
    if (pair_comp(*std_it1, *ft_it1)) return false;

    std_it1 = std_mp1.upper_bound("xxx");
    ft_it1  = ft_mp1.upper_bound("xxx");
    if (pair_comp(*std_it1, *ft_it1)) return false;

    std_it1 = std_mp1.upper_bound(key2);
    ft_it1  = ft_mp1.upper_bound(key2);
    if (std_it1 != std_mp1.end()) return false;
    if (ft_it1 != ft_mp1.end()) return false;

    std::map<int, int> std_mp2 = create_int_std_map();
    ft::map<int, int> ft_mp2   = create_int_ft_map();
    std::map<int, int>::iterator std_it2;
    ft::map<int, int>::iterator ft_it2;

    std_it2 = std_mp2.upper_bound(-42);
    ft_it2  = ft_mp2.upper_bound(-42);
    if (pair_comp(*std_it2, *ft_it2)) return false;

    std_it2 = std_mp2.upper_bound(0);
    ft_it2  = ft_mp2.upper_bound(0);
    if (pair_comp(*std_it2, *ft_it2)) return false;

    std_it2 = std_mp2.upper_bound(99);
    ft_it2  = ft_mp2.upper_bound(99);
    if (std_it2 != std_mp2.end()) return false;
    if (ft_it2 != ft_mp2.end()) return false;

    std_it2 = std_mp2.upper_bound(1000);
    ft_it2  = ft_mp2.upper_bound(1000);
    if (std_it2 != std_mp2.end()) return false;
    if (ft_it2 != ft_mp2.end()) return false;

    return true;
}

static bool test_upper_bound_const(void)
{
    std::map<std::string, int> std_mp = create_std_map();
    ft::map<std::string, int> ft_mp   = create_ft_map();
    typedef const std::map<std::string, int>::const_iterator st_const_iterator;
    typedef const ft::map<std::string, int>::const_iterator ft_const_iterator;

    const std::string key1 = "aaa";
    const std::string key2 = "zzz";

    st_const_iterator std_it1 = std_mp.upper_bound(key1);
    ft_const_iterator ft_it1  = ft_mp.upper_bound(key1);
    if (pair_comp(*std_it1, *ft_it1)) return false;

    st_const_iterator std_it2 = std_mp.upper_bound("xxx");
    ft_const_iterator ft_it2  = ft_mp.upper_bound("xxx");
    if (pair_comp(*std_it2, *ft_it2)) return false;

    st_const_iterator std_it3 = std_mp.upper_bound(key2);
    ft_const_iterator ft_it3  = ft_mp.upper_bound(key2);
    if (std_it3 != std_mp.end()) return false;
    if (ft_it3 != ft_mp.end()) return false;

    const std::map<int, int> std_mp2 = create_int_std_map();
    const ft::map<int, int> ft_mp2   = create_int_ft_map();
    typedef const std::map<int, int>::const_iterator st_const_iterator_int;
    typedef const ft::map<int, int>::const_iterator ft_const_iterator_int;

    st_const_iterator_int std_cit1 = std_mp2.upper_bound(-42);
    ft_const_iterator_int ft_cit1  = ft_mp2.upper_bound(-42);
    if (pair_comp(*std_cit1, *ft_cit1)) return false;

    st_const_iterator_int std_cit2 = std_mp2.upper_bound(0);
    ft_const_iterator_int ft_cit2  = ft_mp2.upper_bound(0);
    if (pair_comp(*std_cit2, *ft_cit2)) return false;

    st_const_iterator_int std_cit3 = std_mp2.upper_bound(99);
    ft_const_iterator_int ft_cit3  = ft_mp2.upper_bound(99);
    if (std_cit3 != std_mp2.end()) return false;
    if (ft_cit3 != ft_mp2.end()) return false;

    st_const_iterator_int std_cit4 = std_mp2.upper_bound(1000);
    ft_const_iterator_int ft_cit4  = ft_mp2.upper_bound(1000);
    if (std_cit4 != std_mp2.end()) return false;
    if (ft_cit4 != ft_mp2.end()) return false;

    return true;
}

static bool test_key_comp(void)
{
    std::map<int, int, std::less<int> > std_mp1;
    ft::map<int, int, std::less<int> > ft_mp1;

    if (std_mp1.key_comp()(1, 2) != ft_mp1.key_comp()(1, 2)) return false;
    if (std_mp1.key_comp()(2, 2) != ft_mp1.key_comp()(2, 2)) return false;
    if (std_mp1.key_comp()(3, 2) != ft_mp1.key_comp()(3, 2)) return false;

    std::map<int, int, std::greater<int> > std_mp2;
    ft::map<int, int, std::greater<int> > ft_mp2;
    if (std_mp2.key_comp()(1, 2) != ft_mp2.key_comp()(1, 2)) return false;
    if (std_mp2.key_comp()(2, 2) != ft_mp2.key_comp()(2, 2)) return false;
    if (std_mp2.key_comp()(3, 2) != ft_mp2.key_comp()(3, 2)) return false;

    return true;
}

static bool test_value_comp(void)
{
    std::map<int, int, std::less<int> > std_mp1;
    ft::map<int, int, std::less<int> > ft_mp1;

    std::pair<int, int> std_p1(1, 1);
    std::pair<int, int> std_p2(2, 2);
    std::pair<int, int> std_p3(3, 3);
    ft::pair<int, int> ft_p1(1, 1);
    ft::pair<int, int> ft_p2(2, 2);
    ft::pair<int, int> ft_p3(3, 3);
    if (std_mp1.value_comp()(std_p1, std_p2) !=
        ft_mp1.value_comp()(ft_p1, ft_p2))
        return false;
    if (std_mp1.value_comp()(std_p2, std_p2) !=
        ft_mp1.value_comp()(ft_p2, ft_p2))
        return false;
    if (std_mp1.value_comp()(std_p3, std_p2) !=
        ft_mp1.value_comp()(ft_p3, ft_p2))
        return false;

    std::map<int, int, std::greater<int> > std_mp2;
    ft::map<int, int, std::greater<int> > ft_mp2;
    if (std_mp2.value_comp()(std_p1, std_p2) !=
        ft_mp2.value_comp()(ft_p1, ft_p2))
        return false;
    if (std_mp2.value_comp()(std_p2, std_p2) !=
        ft_mp2.value_comp()(ft_p2, ft_p2))
        return false;
    if (std_mp2.value_comp()(std_p3, std_p2) !=
        ft_mp2.value_comp()(ft_p3, ft_p2))
        return false;

    return true;
}

static bool test_operator_cmp(void)
{
    std::map<std::string, int> std_mp1 = create_std_map();
    ft::map<std::string, int> ft_mp1   = create_ft_map();

    std::map<std::string, int> std_mp2 = create_std_map();
    ft::map<std::string, int> ft_mp2   = create_ft_map();

    std::map<std::string, int> std_mp3;
    ft::map<std::string, int> ft_mp3;

    std_mp3["aaa"] = 42;
    std_mp3["zzz"] = 42;
    ft_mp3["aaa"]  = 42;
    ft_mp3["zzz"]  = 42;

    if ((std_mp1 == std_mp2) != (ft_mp1 == ft_mp2)) return false;
    if ((std_mp1 != std_mp2) != (ft_mp1 != ft_mp2)) return false;
    if ((std_mp1 < std_mp2) != (ft_mp1 < ft_mp2)) return false;
    if ((std_mp1 <= std_mp2) != (ft_mp1 <= ft_mp2)) return false;
    if ((std_mp1 > std_mp2) != (ft_mp1 > ft_mp2)) return false;
    if ((std_mp1 >= std_mp2) != (ft_mp1 >= ft_mp2)) return false;

    if ((std_mp1 == std_mp3) != (ft_mp1 == ft_mp3)) return false;
    if ((std_mp1 != std_mp3) != (ft_mp1 != ft_mp3)) return false;
    if ((std_mp1 < std_mp3) != (ft_mp1 < ft_mp3)) return false;
    if ((std_mp1 <= std_mp3) != (ft_mp1 <= ft_mp3)) return false;
    if ((std_mp1 > std_mp3) != (ft_mp1 > ft_mp3)) return false;
    if ((std_mp1 >= std_mp3) != (ft_mp1 >= ft_mp3)) return false;

    return true;
}

static bool test_std_swap(void)
{
    std::map<std::string, int> std_mp1 = create_std_map();
    ft::map<std::string, int> ft_mp1   = create_ft_map();
    std::map<std::string, int> std_mp2;
    ft::map<std::string, int> ft_mp2;

    std_mp2["aaa"] = 42;
    ft_mp2["aaa"]  = 42;

    std::map<std::string, int>::iterator std_it1 = std_mp1.begin();
    std::map<std::string, int>::iterator std_it2 = std_mp2.begin();
    ft::map<std::string, int>::iterator ft_it1   = ft_mp1.begin();
    ft::map<std::string, int>::iterator ft_it2   = ft_mp2.begin();

    std::swap(std_mp1, std_mp2);
    std::swap(ft_mp1, ft_mp2);

    if (map_comp(std_mp1, ft_mp1)) return false;
    if (map_comp(std_mp2, ft_mp2)) return false;

    if (std_mp1.begin() != std_it2) return false;
    if (std_mp2.begin() != std_it1) return false;
    if (ft_mp1.begin() != ft_it2) return false;
    if (ft_mp2.begin() != ft_it1) return false;

    return true;
}

int test_map(void)
{
    Tester tester;
    std::cout << "==========[TEST MAP]==========" << std::endl;

    // Member functions
    tester.run(test_constructor(), "test_constructor");
    tester.run(test_operator_equal(), "test_operator_equal");
    tester.run(test_get_allocator(), "test_get_allocator");

    // Element access
    tester.run(test_at(), "test_at");
    tester.run(test_operator_at(), "test_operator_at");

    // Iterators
    tester.run(test_iterator(), "test_iterator");
    tester.run(test_const_iterator(), "test_const_iterator");
    tester.run(test_reverse_iterator(), "test_reverse_iterator");
    tester.run(test_const_reverse_iterator(), "test_const_reverse_iterator");

    // Capacity
    tester.run(test_empty(), "test_empty");
    tester.run(test_size(), "test_size");
    tester.run(test_max_size(), "test_max_size");

    // Modifiers
    tester.run(test_clear(), "test_clear");
    tester.run(test_insert(), "test_insert");
    tester.run(test_insert_with_hint(), "test_insert_with_hint");
    tester.run(test_insert_range(), "test_insert_range");
    tester.run(test_erase(), "test_erase");
    tester.run(test_swap(), "test_swap");

    // Lookup
    tester.run(test_count(), "test_count");
    tester.run(test_find(), "test_find");
    tester.run(test_equal_range(), "test_equal_range");
    tester.run(test_equal_range_const(), "test_equal_range_const");
    tester.run(test_lower_bound(), "test_lower_bound");
    tester.run(test_lower_bound_const(), "test_lower_bound_const");
    tester.run(test_upper_bound(), "test_upper_bound");
    tester.run(test_upper_bound_const(), "test_upper_bound_const");

    // Observers
    tester.run(test_key_comp(), "test_key_comp");
    tester.run(test_value_comp(), "test_value_comp");

    // Non-member functions
    tester.run(test_operator_cmp(), "test_operator_cmp");
    tester.run(test_std_swap(), "test_std_swap");

    return tester.getRet();
}
