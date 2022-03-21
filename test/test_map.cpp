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
/*
        std::cout << "-------------------" << std::endl;
        std::cout << "[st] first  : " << (*st_it).first << "\n"
                  << "     second : " << (*st_it).second << std::endl;
        std::cout << "[ft] first  : " << (*ft_it).first << "\n"
                  << "     second : " << (*ft_it).second << std::endl;
        std::cout << "-------------------" << std::endl;
*/
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

int test_map(void)
{
    Tester tester;
    std::cout << "-----[TEST MAP]-----" << std::endl;

    // constructer
    tester.run(test_constructor(), "test_constructor");

    return tester.getRet();
}
