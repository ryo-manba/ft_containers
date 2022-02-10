#include <iostream>
#include <vector>

#include "Color.hpp"
#include "debug.hpp"
#include "vector.hpp"
#include "tester.hpp"

/************************/
// leaks
#ifdef LEAK
__attribute__((destructor)) static void destructor()
{
    system("leaks -q a.out");
}
#endif
/************************/

/**
 * 要素、size(), capacity()を比較する
 * 完全一致 -> 0
 * Not完全一致 -> 1
 */
template <typename STD, typename FT>
bool vector_comp(const STD& st, const FT& ft)
{
    const size_t sz = st.size();
    if (st.size() != ft.size()) return 1;
    // capacityは実装依存なので比較しない
    //    if (st.capacity() != ft.capacity()) return 1;

    for (size_t i = 0; i < sz; ++i)
    {
        if (st[i] != ft[i]) return 1;
    }
    return 0;
}

// Iterators
bool test_iterator(void)
{
    std::vector<int> vec(5);
    ft::vector<int> myvec(5);

    std::vector<int>::iterator std_it  = vec.begin();
    std::vector<int>::iterator std_ite = vec.end();
    ft::vector<int>::iterator ft_it    = myvec.begin();
    ft::vector<int>::iterator ft_ite   = myvec.end();

    std::vector<int> std_ans, ft_ans;

    for (; std_it != std_ite; ++std_it)
    {
        std_ans.push_back(*std_it);
    }
    for (; ft_it != ft_ite; ++ft_it)
    {
        ft_ans.push_back(*ft_it);
    }
    if (std_ans.size() != ft_ans.size())
    {
        return false;
    }

    size_t sz = std_ans.size();
    for (size_t i = 0; i < sz; ++i)
    {
        if (ft_ans[i] != std_ans[i])
        {
            return false;
        }
    }
    return true;
}

bool test_const_iterator(void)
{
    const std::vector<int> vec(5);
    const ft::vector<int> myvec(5);

    std::vector<int>::const_iterator std_it  = vec.begin();
    std::vector<int>::const_iterator std_ite = vec.end();
    ft::vector<int>::const_iterator ft_it    = myvec.begin();
    ft::vector<int>::const_iterator ft_ite   = myvec.end();

    std::vector<int> std_ans, ft_ans;

    for (; std_it != std_ite; ++std_it)
    {
        std_ans.push_back(*std_it);
    }
    for (; ft_it != ft_ite; ++ft_it)
    {
        ft_ans.push_back(*ft_it);
    }
    if (vector_comp(std_ans, ft_ans)) return false;

    return true;
}

bool test_reverse_iterator(void)
{
    std::vector<int> vec(5);
    ft::vector<int> myvec(5);

    std::vector<int>::reverse_iterator std_rit  = vec.rbegin();
    std::vector<int>::reverse_iterator std_rite = vec.rend();
    ft::vector<int>::reverse_iterator ft_rit    = myvec.rbegin();
    ft::vector<int>::reverse_iterator ft_rite   = myvec.rend();

    std::vector<int> std_ans, ft_ans;

    for (; std_rit != std_rite; ++std_rit)
    {
        std_ans.push_back(*std_rit);
    }
    for (; ft_rit != ft_rite; ++ft_rit)
    {
        ft_ans.push_back(*ft_rit);
    }
    if (vector_comp(std_ans, ft_ans)) return false;

    return true;
}

bool test_const_reverse_iterator(void)
{
    const std::vector<int> vec(5);
    const ft::vector<int> myvec(5);

    std::vector<int>::const_reverse_iterator std_rit  = vec.rbegin();
    std::vector<int>::const_reverse_iterator std_rite = vec.rend();
    ft::vector<int>::const_reverse_iterator ft_rit    = myvec.rbegin();
    ft::vector<int>::const_reverse_iterator ft_rite   = myvec.rend();

    std::vector<int> std_ans, ft_ans;

    for (; std_rit != std_rite; ++std_rit)
    {
        std_ans.push_back(*std_rit);
    }
    for (; ft_rit != ft_rite; ++ft_rit)
    {
        ft_ans.push_back(*ft_rit);
    }
    if (vector_comp(std_ans, ft_ans)) return false;
    return true;
}

// Capacity
bool test_size(void)
{
    std::vector<int> vec1;
    ft::vector<int> myvec1;

    if (vec1.size() != myvec1.size())
    {
        return false;
    }
    vec1.push_back(1);
    myvec1.push_back(1);
    if (vec1.size() != myvec1.size())
    {
        return false;
    }

    std::vector<int> vec2(5);
    ft::vector<int> myvec2(5);
    if (vec2.size() != myvec2.size())
    {
        return false;
    }
    return true;
}

bool test_max_size(void)
{
    std::vector<char> vec_char;
    std::vector<signed char> vec_schar;
    std::vector<wchar_t> vec_wchar;
    std::vector<short> vec_short;
    std::vector<unsigned short> vec_ushort;
    std::vector<int> vec_int;
    std::vector<unsigned int> vec_uint;
    std::vector<long> vec_long;
    std::vector<unsigned long> vec_ulong;
    std::vector<std::string> vec_str;

    ft::vector<char> myvec_char;
    ft::vector<signed char> myvec_schar;
    ft::vector<wchar_t> myvec_wchar;
    ft::vector<short> myvec_short;
    ft::vector<unsigned short> myvec_ushort;
    ft::vector<int> myvec_int;
    ft::vector<unsigned int> myvec_uint;
    ft::vector<long> myvec_long;
    ft::vector<unsigned long> myvec_ulong;
    ft::vector<std::string> myvec_str;

    if (vec_char.max_size() != myvec_char.max_size()) return false;
    if (vec_schar.max_size() != myvec_schar.max_size()) return false;
    if (vec_wchar.max_size() != myvec_wchar.max_size()) return false;
    if (vec_short.max_size() != myvec_short.max_size()) return false;
    if (vec_ushort.max_size() != myvec_ushort.max_size()) return false;
    if (vec_int.max_size() != myvec_int.max_size()) return false;
    if (vec_uint.max_size() != myvec_uint.max_size()) return false;
    if (vec_long.max_size() != myvec_long.max_size()) return false;
    if (vec_ulong.max_size() != myvec_ulong.max_size()) return false;
    if (vec_str.max_size() != myvec_str.max_size()) return false;

    return true;
}

bool test_resize(void)
{
    std::vector<int> vec1;
    ft::vector<int> myvec1;

    vec1.resize(0);
    myvec1.resize(0);
    if (vec1.size() != myvec1.size())
    {
        return false;
    }

    vec1.resize(10);
    myvec1.resize(10);
    if (vec1.size() != myvec1.size())
    {
        return false;
    }

    std::vector<int> vec2(5);
    std::vector<int> myvec2(5);
    if (vec2.size() != myvec2.size())
    {
        return false;
    }
    return true;
}

bool test_capacity(void)
{
    std::vector<int> vec1;
    ft::vector<int> myvec1;

    vec1.resize(0);
    myvec1.resize(0);
    if (vec1.capacity() != myvec1.capacity()) return false;
    vec1.resize(10);
    myvec1.resize(10);
    if (vec1.capacity() != myvec1.capacity()) return false;

    std::vector<int> vec2(5);
    ft::vector<int> myvec2(5);
    if (vec2.capacity() != myvec2.capacity()) return false;

    return true;
}

bool test_empty(void)
{
    std::vector<int> vec1;
    ft::vector<int> myvec1;

    if (vec1.empty() != myvec1.empty())
    {
        return false;
    }

    std::vector<int> vec2(5);
    ft::vector<int> myvec2(5);

    if (vec2.empty() != myvec2.empty())
    {
        return false;
    }

    std::vector<int> vec3(0);
    ft::vector<int> myvec3(0);

    if (vec3.empty() != myvec3.empty())
    {
        return false;
    }
    return true;
}

bool test_reserve(void)
{
    std::vector<int> vec;
    ft::vector<int> myvec;

    vec.reserve(0);
    myvec.reserve(0);
    if (vector_comp(vec, myvec)) return false;

    vec.reserve(1);
    myvec.reserve(1);
    if (vector_comp(vec, myvec)) return false;

    vec.reserve(10);
    myvec.reserve(10);
    if (vector_comp(vec, myvec)) return false;

    return true;
}

// Element Access
bool test_indexer(void)
{
    const size_t sz = 5;
    std::vector<int> vec(sz);
    ft::vector<int> myvec(sz);

    for (size_t i = 0; i < sz; ++i)
    {
        vec[i]   = i;
        myvec[i] = i;
    }
    if (vector_comp(vec, myvec)) return false;
    return true;
}

bool test_at(void)
{
    const size_t sz = 5;
    std::vector<int> vec(sz);
    ft::vector<int> myvec(sz);

    for (size_t i = 0; i < sz; ++i)
    {
        vec.at(i)   = i;
        myvec.at(i) = i;
    }
    for (size_t i = 0; i < sz; ++i)
    {
        if (vec.at(i) != myvec.at(i))
        {
            return false;
        }
    }
    return true;
}

bool test_front(void)
{
    std::vector<int> vec(5);
    ft::vector<int> myvec(5);

    if (vec.front() != myvec.front())
    {
        return false;
    }
    vec.front()   = 5;
    myvec.front() = 5;

    if (vec.front() != myvec.front())
    {
        return false;
    }
    return true;
}

bool test_back(void)
{
    std::vector<int> vec(5);
    ft::vector<int> myvec(5);

    if (vec.back() != myvec.back())
    {
        return false;
    }
    vec.back()   = 5;
    myvec.back() = 5;
    if (vec.back() != myvec.back())
    {
        return false;
    }
    return true;
}

// Modilers
bool test_assign(void)
{
    std::vector<int> vec1;
    ft::vector<int> myvec1;
    std::vector<int> vec2(5);
    ft::vector<int> myvec2(5);

    // capacity以上
    vec1.assign(5, 42);
    myvec1.assign(5, 42);

    // capacity以下
    vec2.assign(vec2.size(), 42);
    myvec2.assign(myvec2.size(), 42);

    if (vector_comp(vec1, myvec1)) return false;
    if (vector_comp(vec2, myvec2)) return false;
    return true;
}

bool test_push_back(void)
{
    const size_t sz = 5;
    std::vector<int> vec;
    ft::vector<int> myvec;
    for (size_t i = 0; i < sz; ++i)
    {
        vec.push_back(i);
        myvec.push_back(i);
    }
    if (vector_comp(vec, myvec)) return false;
    return true;
}

bool test_pop_back(void)
{
    size_t sz = 5;
    std::vector<int> vec(sz);
    ft::vector<int> myvec(sz);

    for (size_t i = 0; i < sz; ++i)
    {
        vec[i]   = i;
        myvec[i] = i;
    }

    for (size_t i = 0; i < sz - 2; ++i)
    {
        vec.pop_back();
        myvec.pop_back();
    }
    if (vector_comp(vec, myvec)) return false;

    sz = vec.size();
    for (size_t i = 0; i < sz; ++i)
    {
        vec.push_back(i);
        myvec.push_back(i);
    }
    if (vector_comp(vec, myvec)) return false;

    return true;
}

bool test_insert(void)
{
    const size_t sz = 5;
    std::vector<int> vec1(sz);
    ft::vector<int> myvec1(sz);

    for (size_t i = 0; i < sz; ++i)
    {
        vec1[i]   = i;
        myvec1[i] = i;
    }
    // 要素2つ(it, pos)
    std::vector<int>::iterator it  = vec1.insert(vec1.begin(), 1);
    ft::vector<int>::iterator myit = myvec1.insert(myvec1.begin(), 1);
    if (*it != *myit) return false;
    if (vector_comp(vec1, myvec1)) return false;

    std::vector<int> vec2(sz);
    ft::vector<int> myvec2(sz);

    for (size_t i = 0; i < sz; ++i)
    {
        vec2[i]   = i;
        myvec2[i] = i;
    }
    // 要素3つ(it, digit, digit)
    vec2.insert(vec2.begin() + 2, 2, 2);
    myvec2.insert(myvec2.begin() + 2, 2, 2);
    if (vector_comp(vec2, myvec2)) return false;

    std::vector<int> vec3(sz);
    ft::vector<int> myvec3(sz);

    // 要素3つ(it, other_it, other_it)
    vec3.insert(vec3.begin(), vec2.begin(), vec2.end());
    myvec3.insert(myvec3.begin(), vec2.begin(), vec2.end());
    if (vector_comp(vec3, myvec3)) return false;

    return true;
}

//(1) : positionが指す要素が削除される。
//(2) : [first, last)で示される範囲の要素が削除される。
bool test_erase(void)
{
    const size_t sz = 5;
    std::vector<int> vec1(sz);
    ft::vector<int> myvec1(sz);

    for (size_t i = 0; i < sz; ++i)
    {
        vec1[i]   = i;
        myvec1[i] = i;
    }
    std::vector<int>::iterator it;
    ft::vector<int>::iterator myit;

    // 引数1つ
    for (size_t i = 0; i < sz; ++i)
    {
        it   = vec1.erase(vec1.begin());
        myit = myvec1.erase(myvec1.begin());

        if (i != sz - 1)
        {
            if (*it != *myit) return false;
        }
        if (vector_comp(vec1, myvec1)) return false;
    }

    // 引数2つ
    std::vector<int> vec2(sz);
    ft::vector<int> myvec2(sz);

    for (size_t i = 0; i < sz; ++i)
    {
        vec2[i]   = i;
        myvec2[i] = i;
    }
    it   = vec2.erase(vec2.begin(), vec2.begin() + 2);
    myit = myvec2.erase(myvec2.begin(), myvec2.begin() + 2);

    if (*it != *myit) return false;
    if (vector_comp(vec2, myvec2)) return false;

    it   = vec2.erase(vec2.begin(), vec2.end());
    myit = myvec2.erase(myvec2.begin(), myvec2.end());

    if (vector_comp(vec2, myvec2)) return false;

    return true;
}

bool test_swap(void)
{
    std::vector<int> vec1(3);
    std::vector<int> vec2(3);
    ft::vector<int> myvec1(3);
    ft::vector<int> myvec2(3);

    for (size_t i = 0; i < 3; ++i)
    {
        vec1[i]   = i;
        myvec1[i] = i;
    }
    for (size_t i = 0; i < 3; ++i)
    {
        vec2[i]   = i + 3;
        myvec2[i] = i + 3;
    }

    vec1.swap(vec2);
    myvec1.swap(myvec2);

    if (vec1.size() != myvec1.size() || vec2.size() != myvec2.size())
    {
        return false;
    }
    for (size_t i = 0; i < vec1.size(); ++i)
    {
        if (vec1[i] != myvec1[i])
        {
            return false;
        }
    }
    for (size_t i = 0; i < vec2.size(); ++i)
    {
        if (vec2[i] != myvec2[i])
        {
            return false;
        }
    }
    return true;
}

bool test_clear(void)
{
    std::vector<int> vec(3);
    ft::vector<int> myvec(3);

    vec.clear();
    myvec.clear();
    if (vec.empty() != myvec.empty())
    {
        return false;
    }
    return true;
}

bool test_get_allocator(void)
{
    std::allocator<int> alloc;
    std::vector<int> vec(alloc);
    ft::vector<int> myvec(alloc);

    if (vec.get_allocator() != myvec.get_allocator())
    {
        return false;
    }
    return true;
}

// TODO: 修正
bool test_constructorator(void)
{
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

    if (vector_comp(std_vec_char, ft_vec_char)) return false;
    if (vector_comp(std_vec_schar, ft_vec_schar)) return false;
    if (vector_comp(std_vec_wchar, ft_vec_wchar)) return false;
    if (vector_comp(std_vec_short, ft_vec_short)) return false;
    if (vector_comp(std_vec_ushort, ft_vec_ushort)) return false;
    if (vector_comp(std_vec_int, ft_vec_int)) return false;
    if (vector_comp(std_vec_uint, ft_vec_uint)) return false;
    if (vector_comp(std_vec_long, ft_vec_long)) return false;
    if (vector_comp(std_vec_ulong, ft_vec_ulong)) return false;
    if (vector_comp(std_vec_str, ft_vec_str)) return false;

    return true;
}

bool test_vector(void)
{
    Tester tester;
    std::cout << "-----[TEST VECTOR]-----" << std::endl;

    // constructer
    tester.run(test_constructorator(), "test_constructorator");

    // Iterators
    tester.run(test_iterator(), "test_iterator");
    tester.run(test_const_iterator(), "test_const_iterator");
    tester.run(test_reverse_iterator(), "test_reverse_iterator");
    tester.run(test_const_reverse_iterator(), "test_const_reverse_iterator");

    // capacitys
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

    // allocator
    tester.run(test_get_allocator(), "test_get_allocator");

    return tester.getRet();
}

int main(void)
{
    return test_vector();
}
