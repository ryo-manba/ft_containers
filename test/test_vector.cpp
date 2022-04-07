#include <iostream>
#include <vector>

#include "Color.hpp"
#include "debug.hpp"
#include "tester.hpp"
#include "vector.hpp"

/**
 * 要素、size()
 * 完全一致 -> 0
 * Not完全一致 -> 1
 */
template <typename STD, typename FT>
bool vector_comp(const STD& st, const FT& ft)
{
    if (st.size() != ft.size()) return 1;
    // capacityは実装依存なので比較しない
    //    if (st.capacity() != ft.capacity()) return 1;

    const size_t sz = st.size();
    for (size_t i = 0; i < sz; ++i)
    {
        if (st[i] != ft[i]) return 1;
    }
    return 0;
}

static const size_t sz = 5;

template <typename T>
void init_vector(T v)
{
    for (size_t i = 0; i < sz; i++)
    {
        v[i] = i;
    }
}

bool test_constructor(void)
{
    // default constructor
    std::vector<int> std_vec1;
    ft::vector<int> ft_vec1;
    if (vector_comp(std_vec1, ft_vec1)) return false;

    // size指定
    std::vector<int> std_vec2(sz);
    ft::vector<int> ft_vec2(sz);
    if (vector_comp(std_vec2, ft_vec2)) return false;
    init_vector(std_vec2);
    init_vector(ft_vec2);

    // range constructor[first, last]
    std::vector<int> std_vec3(std_vec2.begin(), std_vec2.end());
    ft::vector<int> ft_vec3(ft_vec2.begin(), ft_vec2.end());
    if (vector_comp(std_vec3, ft_vec3)) return false;

    // copy constructer
    std::vector<int> std_vec4(std_vec1);
    ft::vector<int> ft_vec4(ft_vec1);
    if (vector_comp(std_vec4, ft_vec4)) return false;

    // fill constructor
    std::vector<int> std_vec5(sz, 42);
    ft::vector<int> ft_vec5(sz, 42);
    if (vector_comp(std_vec5, ft_vec5)) return false;

    // allocator
    std::allocator<int> alloc;
    std::vector<int> std_vec6(alloc);
    ft::vector<int> ft_vec6(alloc);
    if (vector_comp(std_vec6, ft_vec6)) return false;
    if (std_vec6.get_allocator() != ft_vec6.get_allocator()) return false;

    return true;
}

bool test_operator_equal(void)
{
    std::vector<int> std_vec1(sz);
    ft::vector<int> ft_vec1(sz);
    init_vector(std_vec1);
    init_vector(ft_vec1);

    // 代入
    std::vector<int> std_vec2;
    ft::vector<int> ft_vec2;
    std_vec2 = std_vec1;
    ft_vec2  = ft_vec1;
    if (vector_comp(std_vec1, ft_vec1)) return false;
    if (vector_comp(std_vec2, ft_vec2)) return false;

    return true;
}

bool test_assign(void)
{
    std::vector<int> std_vec1;
    ft::vector<int> ft_vec1;
    std::vector<int> std_vec2(10);
    ft::vector<int> ft_vec2(10);

    // capacity以上
    std_vec1.assign(5, 42);
    ft_vec1.assign(5, 42);
    if (vector_comp(std_vec1, ft_vec1)) return false;

    // capacity以下
    std_vec2.assign(std_vec2.size(), 42);
    ft_vec2.assign(ft_vec2.size(), 42);
    if (vector_comp(std_vec2, ft_vec2)) return false;

    std_vec1.assign(std_vec2.begin(), std_vec2.end());
    ft_vec1.assign(ft_vec2.begin(), ft_vec2.end());
    if (vector_comp(std_vec2, ft_vec2)) return false;

    return true;
}

bool test_get_allocator(void)
{
    std::allocator<int> alloc;
    std::vector<int> std_vec(alloc);
    ft::vector<int> ft_vec(alloc);
    if (std_vec.get_allocator() != ft_vec.get_allocator()) return false;

    return true;
}

// Element access
bool test_at(void)
{
    std::vector<int> std_vec(sz);
    ft::vector<int> ft_vec(sz);

    for (size_t i = 0; i < sz; ++i)
    {
        std_vec.at(i) = i;
        ft_vec.at(i)  = i;
    }
    for (size_t i = 0; i < sz; ++i)
    {
        if (std_vec.at(i) != ft_vec.at(i)) return false;
    }

    return true;
}

bool test_indexer(void)
{
    std::vector<int> std_vec(sz);
    ft::vector<int> ft_vec(sz);
    for (size_t i = 0; i < sz; ++i)
    {
        std_vec[i] = i;
        ft_vec[i]  = i;
    }
    if (vector_comp(std_vec, ft_vec)) return false;

    return true;
}

bool test_front(void)
{
    std::vector<int> std_vec(sz);
    ft::vector<int> ft_vec(sz);
    if (std_vec.front() != ft_vec.front()) return false;

    std_vec.front() = 42;
    ft_vec.front()  = 42;
    if (std_vec.front() != ft_vec.front()) return false;
    if (vector_comp(std_vec, ft_vec)) return false;

    return true;
}

bool test_back(void)
{
    std::vector<int> std_vec(sz);
    ft::vector<int> ft_vec(sz);
    if (std_vec.back() != ft_vec.back()) return false;

    std_vec.back() = 42;
    ft_vec.back()  = 42;
    if (std_vec.back() != ft_vec.back()) return false;
    if (vector_comp(std_vec, ft_vec)) return false;

    return true;
}

bool test_data(void)
{
    std::vector<int> std_vec(sz);
    std::vector<int> ft_vec(sz);

    if (std_vec.data() != &std_vec[0]) return false;
    if (ft_vec.data() != &ft_vec[0]) return false;

    return true;
}

// Iterators
bool test_iterator(void)
{
    std::vector<int> std_vec(sz);
    ft::vector<int> ft_vec(sz);
    init_vector(std_vec);
    init_vector(ft_vec);

    std::vector<int>::iterator std_it  = std_vec.begin();
    std::vector<int>::iterator std_ite = std_vec.end();
    ft::vector<int>::iterator ft_it    = ft_vec.begin();
    ft::vector<int>::iterator ft_ite   = ft_vec.end();

    for (size_t i = 0; i < sz; ++i, ++std_it, ++ft_it)
    {
        if (*std_it != *ft_it) return false;
        if (std_it == std_ite) return false;
        if (ft_it == ft_ite) return false;
    }
    if (std_it != std_ite) return false;
    if (ft_it != ft_ite) return false;

    return true;
}

bool test_const_iterator(void)
{
    std::vector<int> std_vec(sz);
    ft::vector<int> ft_vec(sz);
    init_vector(std_vec);
    init_vector(ft_vec);

    std::vector<int>::const_iterator std_it  = std_vec.begin();
    std::vector<int>::const_iterator std_ite = std_vec.end();
    ft::vector<int>::const_iterator ft_it    = ft_vec.begin();
    ft::vector<int>::const_iterator ft_ite   = ft_vec.end();

    for (size_t i = 0; i < sz; ++i, ++std_it, ++ft_it)
    {
        if (*std_it != *ft_it) return false;
        if (std_it == std_ite) return false;
        if (ft_it == ft_ite) return false;
    }
    if (std_it != std_ite) return false;
    if (ft_it != ft_ite) return false;

    return true;
}

bool test_reverse_iterator(void)
{
    std::vector<int> std_vec(sz);
    ft::vector<int> ft_vec(sz);
    init_vector(std_vec);
    init_vector(ft_vec);

    std::vector<int>::reverse_iterator std_rit  = std_vec.rbegin();
    std::vector<int>::reverse_iterator std_rite = std_vec.rend();
    ft::vector<int>::reverse_iterator ft_rit    = ft_vec.rbegin();
    ft::vector<int>::reverse_iterator ft_rite   = ft_vec.rend();

    for (size_t i = 0; i < sz; ++i, ++std_rit, ++ft_rit)
    {
        if (*std_rit != *ft_rit) return false;
        if (std_rit == std_rite) return false;
        if (ft_rit == ft_rite) return false;
    }
    if (std_rit != std_rite) return false;
    if (ft_rit != ft_rite) return false;

    return true;
}

bool test_const_reverse_iterator(void)
{
    std::vector<int> std_vec(sz);
    ft::vector<int> ft_vec(sz);
    init_vector(std_vec);
    init_vector(ft_vec);

    std::vector<int>::const_reverse_iterator std_rit  = std_vec.rbegin();
    std::vector<int>::const_reverse_iterator std_rite = std_vec.rend();
    ft::vector<int>::const_reverse_iterator ft_rit    = ft_vec.rbegin();
    ft::vector<int>::const_reverse_iterator ft_rite   = ft_vec.rend();

    for (size_t i = 0; i < sz; ++i, ++std_rit, ++ft_rit)
    {
        if (*std_rit != *ft_rit) return false;
        if (std_rit == std_rite) return false;
        if (ft_rit == ft_rite) return false;
    }
    if (std_rit != std_rite) return false;
    if (ft_rit != ft_rite) return false;

    return true;
}

// Capacity
bool test_empty(void)
{
    std::vector<int> std_vec1;
    ft::vector<int> ft_vec1;
    if (std_vec1.empty() != ft_vec1.empty()) return false;

    std::vector<int> std_vec2(sz);
    ft::vector<int> ft_vec2(sz);
    if (std_vec2.empty() != ft_vec2.empty()) return false;

    std::vector<int> std_vec3(0);
    ft::vector<int> ft_vec3(0);
    if (std_vec3.empty() != ft_vec3.empty()) return false;

    return true;
}

bool test_size(void)
{
    std::vector<int> std_vec1;
    ft::vector<int> ft_vec1;
    if (std_vec1.size() != ft_vec1.size()) return false;

    std::vector<int> std_vec2(sz);
    ft::vector<int> ft_vec2(sz);
    if (std_vec2.size() != ft_vec2.size()) return false;

    std::vector<int> std_vec3(sz, 42);
    ft::vector<int> ft_vec3(sz, 42);
    if (std_vec3.size() != ft_vec3.size()) return false;

    return true;
}

bool test_max_size(void)
{
    std::vector<char> std_vec_char;
    std::vector<signed char> std_vec_schar;
    std::vector<wchar_t> std_vec_wchar;
    std::vector<short> std_vec_short;
    std::vector<unsigned short> std_vec_ushort;
    std::vector<int> std_vec_int;
    std::vector<unsigned int> std_vec_uint;
    std::vector<long> std_vec_long;
    std::vector<unsigned long> std_vec_ulong;
    std::vector<std::string> std_vec_str;

    ft::vector<char> ft_vec_char;
    ft::vector<signed char> ft_vec_schar;
    ft::vector<wchar_t> ft_vec_wchar;
    ft::vector<short> ft_vec_short;
    ft::vector<unsigned short> ft_vec_ushort;
    ft::vector<int> ft_vec_int;
    ft::vector<unsigned int> ft_vec_uint;
    ft::vector<long> ft_vec_long;
    ft::vector<unsigned long> ft_vec_ulong;
    ft::vector<std::string> ft_vec_str;

    if (std_vec_char.max_size() != ft_vec_char.max_size()) return false;
    if (std_vec_schar.max_size() != ft_vec_schar.max_size()) return false;
    if (std_vec_wchar.max_size() != ft_vec_wchar.max_size()) return false;
    if (std_vec_short.max_size() != ft_vec_short.max_size()) return false;
    if (std_vec_ushort.max_size() != ft_vec_ushort.max_size()) return false;
    if (std_vec_int.max_size() != ft_vec_int.max_size()) return false;
    if (std_vec_uint.max_size() != ft_vec_uint.max_size()) return false;
    if (std_vec_long.max_size() != ft_vec_long.max_size()) return false;
    if (std_vec_ulong.max_size() != ft_vec_ulong.max_size()) return false;
    if (std_vec_str.max_size() != ft_vec_str.max_size()) return false;

    return true;
}

bool test_reserve(void)
{
    std::vector<int> std_vec;
    ft::vector<int> ft_vec;

    std_vec.reserve(0);
    ft_vec.reserve(0);
    if (vector_comp(std_vec, ft_vec)) return false;

    std_vec.reserve(10);
    ft_vec.reserve(10);
    if (vector_comp(std_vec, ft_vec)) return false;

    std_vec.reserve(5);
    ft_vec.reserve(5);
    if (vector_comp(std_vec, ft_vec)) return false;

    return true;
}

// 直接比較した場合の結果がローカルとGitHub Actionsで異なる
// capacityの初期値や増加率などの値は仕様で定められていない
bool test_capacity(void)
{
    std::vector<int> std_vec1;
    ft::vector<int> ft_vec1;
    //    if (std_vec1.capacity() != ft_vec1.capacity()) return false;
    if (std_vec1.capacity() < 0) return false;
    if (ft_vec1.capacity() < 0) return false;

    std::vector<int> std_vec2(256);
    ft::vector<int> ft_vec2(256);
    //    if (std_vec2.capacity() != ft_vec2.capacity()) return false;
    if (std_vec2.capacity() < 256) return false;
    if (ft_vec2.capacity() < 256) return false;

    std::vector<int> std_vec3(1024);
    ft::vector<int> ft_vec3(1024);
    //    if (std_vec3.capacity() != ft_vec3.capacity()) return false;
    if (std_vec3.capacity() < 1024) return false;
    if (ft_vec3.capacity() < 1024) return false;

    return true;
}

// Modifilers
bool test_clear(void)
{
    std::vector<int> std_vec(3);
    ft::vector<int> ft_vec(3);

    std_vec.clear();
    ft_vec.clear();
    if (std_vec.empty() != ft_vec.empty()) return false;

    return true;
}

bool test_insert(void)
{
    std::vector<int> std_vec1(sz);
    ft::vector<int> ft_vec1(sz);
    init_vector(std_vec1);
    init_vector(ft_vec1);

    // 要素2つ(it, pos)
    std::vector<int>::iterator std_it = std_vec1.insert(std_vec1.begin(), 1);
    ft::vector<int>::iterator ft_it   = ft_vec1.insert(ft_vec1.begin(), 1);

    if (*std_it != *ft_it) return false;
    if (vector_comp(std_vec1, ft_vec1)) return false;

    std::vector<int> std_vec2(sz);
    ft::vector<int> ft_vec2(sz);
    init_vector(std_vec2);
    init_vector(ft_vec2);

    // 要素3つ(it, count, value)
    std_vec2.insert(std_vec2.begin() + 2, 2, 42);
    ft_vec2.insert(ft_vec2.begin() + 2, 2, 42);
    if (vector_comp(std_vec2, ft_vec2)) return false;

    std::vector<int> std_vec3(sz);
    ft::vector<int> ft_vec3(sz);

    // 要素3つ(it, first, last)
    std_vec3.insert(std_vec3.begin(), std_vec2.begin(), std_vec2.end());
    ft_vec3.insert(ft_vec3.begin(), std_vec2.begin(), std_vec2.end());
    if (vector_comp(std_vec3, ft_vec3)) return false;

    return true;
}

//(1) : positionが指す要素が削除される。
//(2) : [first, last)で示される範囲の要素が削除される。
bool test_erase(void)
{
    std::vector<int> std_vec1(sz);
    ft::vector<int> ft_vec1(sz);
    init_vector(std_vec1);
    init_vector(ft_vec1);

    std::vector<int>::iterator std_it;
    ft::vector<int>::iterator ft_it;

    // 引数1つ
    for (size_t i = 0; i < sz; ++i)
    {
        std_it = std_vec1.erase(std_vec1.begin());
        ft_it  = ft_vec1.erase(ft_vec1.begin());

        if (*std_it != *ft_it) return false;
        if (vector_comp(std_vec1, ft_vec1)) return false;
    }

    // 引数2つ
    std::vector<int> std_vec2(sz);
    ft::vector<int> ft_vec2(sz);
    init_vector(std_vec2);
    init_vector(ft_vec2);

    std_it = std_vec2.erase(std_vec2.begin(), std_vec2.begin() + 2);
    ft_it  = ft_vec2.erase(ft_vec2.begin(), ft_vec2.begin() + 2);
    if (*std_it != *ft_it) return false;
    if (vector_comp(std_vec2, ft_vec2)) return false;

    std_it = std_vec2.erase(std_vec2.begin(), std_vec2.end());
    ft_it  = ft_vec2.erase(ft_vec2.begin(), ft_vec2.end());
    if (vector_comp(std_vec2, ft_vec2)) return false;

    return true;
}

bool test_push_back(void)
{
    std::vector<int> std_vec;
    ft::vector<int> ft_vec;

    for (size_t i = 0; i < sz; ++i)
    {
        std_vec.push_back(i);
        ft_vec.push_back(i);
    }
    if (vector_comp(std_vec, ft_vec)) return false;

    return true;
}

bool test_pop_back(void)
{
    std::vector<int> std_vec(sz);
    ft::vector<int> ft_vec(sz);
    init_vector(std_vec);
    init_vector(ft_vec);

    for (size_t i = 0; i < sz; ++i)
    {
        std_vec.pop_back();
        ft_vec.pop_back();
        if (vector_comp(std_vec, ft_vec)) return false;
    }

    return true;
}

bool test_resize(void)
{
    std::vector<int> std_vec;
    ft::vector<int> ft_vec;

    for (size_t i = 0; i < sz; i++)
    {
        std_vec.resize(i);
        ft_vec.resize(i);
        if (vector_comp(std_vec, ft_vec)) return false;
    }

    std_vec.resize(sz + 5, 42);
    ft_vec.resize(sz + 5, 42);
    if (vector_comp(std_vec, ft_vec)) return false;

    std_vec.resize(sz - 3, -42);
    ft_vec.resize(sz - 3, -42);
    if (vector_comp(std_vec, ft_vec)) return false;

    return true;
}

bool test_swap(void)
{
    std::vector<int> std_vec1(sz);
    ft::vector<int> ft_vec1(sz);
    init_vector(std_vec1);
    init_vector(ft_vec1);

    std::vector<int> std_vec2;
    ft::vector<int> ft_vec2;

    std_vec1.swap(std_vec2);
    ft_vec1.swap(ft_vec2);

    if (vector_comp(std_vec1, ft_vec1)) return false;
    if (vector_comp(std_vec2, ft_vec2)) return false;

    return true;
}

// Non-member functions
bool test_operator(void)
{
    std::vector<int> std_vec1(sz, 1);
    std::vector<int> std_vec2(sz, 1);
    std::vector<int> std_vec3(sz, 42);

    ft::vector<int> ft_vec1(sz, 1);
    ft::vector<int> ft_vec2(sz, 1);
    ft::vector<int> ft_vec3(sz, 42);

    if ((std_vec1 == std_vec2) != (ft_vec1 == ft_vec2)) return false;
    if ((std_vec1 != std_vec2) != (ft_vec1 != ft_vec2)) return false;
    if ((std_vec1 < std_vec2) != (ft_vec1 < ft_vec2)) return false;
    if ((std_vec1 <= std_vec2) != (ft_vec1 <= ft_vec2)) return false;
    if ((std_vec1 > std_vec2) != (ft_vec2 > ft_vec1)) return false;
    if ((std_vec1 >= std_vec2) != (ft_vec1 >= ft_vec2)) return false;

    if ((std_vec1 == std_vec3) != (ft_vec1 == ft_vec3)) return false;
    if ((std_vec1 != std_vec3) != (ft_vec1 != ft_vec3)) return false;
    if ((std_vec1 < std_vec3) != (ft_vec1 < ft_vec3)) return false;
    if ((std_vec1 <= std_vec3) != (ft_vec1 <= ft_vec3)) return false;
    if ((std_vec1 > std_vec3) != (ft_vec1 > ft_vec3)) return false;
    if ((std_vec1 >= std_vec3) != (ft_vec1 >= ft_vec3)) return false;

    return true;
}

bool test_std_swap(void)
{
    std::vector<int> std_vec1(sz);
    ft::vector<int> ft_vec1(sz);
    init_vector(std_vec1);
    init_vector(ft_vec1);

    std::vector<int> std_vec2(sz, 42);
    ft::vector<int> ft_vec2(sz, 42);

    if (vector_comp(std_vec1, ft_vec1)) return false;
    if (vector_comp(std_vec2, ft_vec2)) return false;

    std::swap(std_vec1, std_vec2);
    std::swap(ft_vec1, ft_vec2);
    if (vector_comp(std_vec1, ft_vec1)) return false;
    if (vector_comp(std_vec2, ft_vec2)) return false;

    return true;
}

int test_vector(void)
{
    Tester tester;
    std::cout << "==========[TEST VECTOR]==========" << std::endl;

    // Member functions
    tester.run(test_constructor(), "test_constructor");
    tester.run(test_operator_equal(), "test_operator_equal");
    tester.run(test_assign(), "test_assign");
    tester.run(test_get_allocator(), "test_get_allocator");

    // Element access
    tester.run(test_at(), "test_at");
    tester.run(test_indexer(), "test_indexer");
    tester.run(test_front(), "test_front");
    tester.run(test_back(), "test_back");
    tester.run(test_data(), "test_data");

    // Iterators
    tester.run(test_iterator(), "test_iterator");
    tester.run(test_const_iterator(), "test_const_iterator");
    tester.run(test_reverse_iterator(), "test_reverse_iterator");
    tester.run(test_const_reverse_iterator(), "test_const_reverse_iterator");

    // Capacity
    tester.run(test_empty(), "test_empty");
    tester.run(test_size(), "test_size");
    tester.run(test_max_size(), "test_max_size");
    tester.run(test_reserve(), "test_reserve");
    tester.run(test_capacity(), "test_capacity");

    // Modifiers
    tester.run(test_clear(), "test_clear");
    tester.run(test_insert(), "test_insert");
    tester.run(test_erase(), "test_erase");
    tester.run(test_push_back(), "test_push_back");
    tester.run(test_pop_back(), "test_pop_back");
    tester.run(test_resize(), "test_resize");
    tester.run(test_swap(), "test_swap");

    // Non-member functions
    tester.run(test_operator(), "test_operator");
    tester.run(test_std_swap(), "test_std_swap");

    return tester.getRet();
}
