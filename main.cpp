#include <iostream>
#include <vector>
#include "vector.hpp"

#define debug(var)  do{std::cout << #var << " : ";view(var);}while(0)
template<typename T> void view(T e){std::cout << e << std::endl;}
template<typename T> void view(const std::vector<T>& v){for(const auto& e : v){ std::cout << e << " "; } std::cout << std::endl;}
template<typename T> void view(const std::vector<std::vector<T> >& vv){ for(const auto& v : vv){ view(v); } }

int main(void)
{
//    std::vector<int> st(100);
    ft::vector<int> ft(100);

    for (int i = 0; i <= 100; ++i)
    {
        ft[i] = i;
    }
    for (int i = 0;  i <= 100; ++i)
    {
        std::cout << ft[i] << std::endl;
    }
    return 0;
}
