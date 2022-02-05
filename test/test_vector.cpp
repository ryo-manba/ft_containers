#include <iostream>
#include <vector>

#include "Color.hpp"
#include "vector.hpp"

/************************/
// debug
#define debug(var)                  \
    do {                            \
        std::cout << #var << " : "; \
        view(var);                  \
    } while (0)
template <typename T>
void view(T e)
{
    std::cout << e << std::endl;
}
/**********************/

#define SIZE 5

void test(bool result, std::string test_case)
{
    if (result == true) { std::cout << GREEN << "[OK]" << RESET; }
    else
    {
        std::cout << RED << "[KO]" << RESET;
    }
    std::cout << " : " << YELLOW << test_case << RESET << std::endl;
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
    size_t std_sz = 0, ft_sz = 0;

    for (; std_it != std_ite; ++std_it)
    {
        std_ans.push_back(*std_it);
        std_sz += 1;
    }
    for (; ft_it != ft_ite; ++ft_it)
    {
        ft_ans.push_back(*ft_it);
        ft_sz += 1;
    }
    if (ft_sz != std_sz) { return false; }
    for (size_t i = 0; i < std_sz; ++i)
    {
        if (ft_ans[i] != std_ans[i]) { return false; }
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
    if (ft_ans.size() != std_ans.size()) { return false; }
    size_t sz = std_ans.size();
    for (size_t i = 0; i < sz; ++i)
    {
        if (ft_ans[i] != std_ans[i]) { return false; }
    }
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

    for (; std_rit != std_rite; ++std_rit) { std_ans.push_back(*std_rit); }
    for (; ft_rit != ft_rite; ++ft_rit) { ft_ans.push_back(*ft_rit); }
    if (std_ans.size() != ft_ans.size()) { return false; }
    size_t sz = std_ans.size();
    for (size_t i = 0; i < sz; ++i)
    {
        if (ft_ans[i] != std_ans[i]) { return false; }
    }
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
    if (ft_ans.size() != std_ans.size()) { return false; }
    size_t sz = std_ans.size();
    for (size_t i = 0; i < sz; ++i)
    {
        if (ft_ans[i] != std_ans[i]) { return false; }
    }
    return true;
}

// Capacity
bool test_size(void)
{
    std::vector<int> vec1;
    ft::vector<int> myvec1;

    if (vec1.size() != myvec1.size()) { return false; }
    vec1.push_back(1);
    myvec1.push_back(1);
    if (vec1.size() != myvec1.size()) { return false; }

    std::vector<int> vec2(5);
    ft::vector<int> myvec2(5);
    if (vec2.size() != myvec2.size()) { return false; }
    return true;
}

bool test_max_size(void)
{
    std::vector<int> vec1;
    ft::vector<int> myvec1;

    if (vec1.max_size() != myvec1.max_size()) { return false; }

    std::vector<int> vec2;
    ft::vector<int> myvec2;
    if (vec2.max_size() != myvec2.max_size()) { return false; }
    return true;
}

bool test_resize(void)
{
    std::vector<int> vec1;
    ft::vector<int> myvec1;

    vec1.resize(0);
    myvec1.resize(0);
    if (vec1.size() != myvec1.size()) { return false; }

    vec1.resize(10);
    myvec1.resize(10);
    if (vec1.size() != myvec1.size()) { return false; }

    std::vector<int> vec2(5);
    std::vector<int> myvec2(5);
    if (vec2.size() != myvec2.size()) { return false; }
    return true;
}

bool test_capacity(void)
{
    std::vector<int> vec1;
    ft::vector<int> myvec1;

    vec1.resize(0);
    myvec1.resize(0);
    if (vec1.capacity() != myvec1.capacity()) { return false; }

    vec1.resize(10);
    myvec1.resize(10);
    if (vec1.capacity() != myvec1.capacity()) { return false; }
    std::vector<int> vec2(5);
    ft::vector<int> myvec2(5);
    if (vec2.capacity() != myvec2.capacity()) { return false; }
    return true;
}

/*
bool test_empty(void)
{
    std::vector<int> vec1;
    ft::vector<int> myvec1;

    if (vec1.empty() != myvec1.empty()) {
        return false;
    }

    std::vector<int> vec2(5);
    ft::vector<int> myvec2(5);

    if (vec2.empty() != myvec2.empty()) {
        return false;
    }

    std::vector<int> vec3(0);
    ft::vector<int> myvec3(0);

    if (vec3.empty() != myvec3.empty()) {
        return false;
    }
    return true;
}
*/
bool test_reserve(void)
{
    std::vector<int> vec;
    ft::vector<int> myvec;

    vec.reserve(0);
    myvec.reserve(0);
    if (vec.capacity() != myvec.capacity()) { return false; }
    vec.reserve(1);
    myvec.reserve(1);
    if (vec.capacity() != myvec.capacity()) { return false; }
    vec.reserve(10);
    myvec.reserve(10);
    if (vec.capacity() != myvec.capacity()) { return false; }
    return true;
}

// Element Access
bool test_indexer(void)
{
    std::vector<int> vec;
    ft::vector<int> myvec;

    for (size_t i = 0; i < 5; ++i)
    {
        vec[i]   = i;
        myvec[i] = i;
    }
    for (size_t i = 0; i < 5; ++i)
    {
        if (vec[i] != myvec[i]) { return false; }
    }
    return true;
}

bool test_at(void)
{
    std::vector<int> vec;
    ft::vector<int> myvec;

    for (size_t i = 0; i < SIZE; ++i)
    {
        vec.at(i)   = i;
        myvec.at(i) = i;
    }
    for (size_t i = 0; i < SIZE; ++i)
    {
        if (vec.at(i) == myvec.at(i)) { return false; }
    }
    return true;
}

bool test_front(void)
{
    std::vector<int> vec(5);
    ft::vector<int> myvec(5);

    if (vec.front() != myvec.front()) { return false; }
    vec.front()   = 5;
    myvec.front() = 5;

    if (vec.front() != myvec.front()) { return false; }
    return true;
}

bool test_back(void)
{
    std::vector<int> vec(5);
    ft::vector<int> myvec(5);

    if (vec.back() != myvec.back()) { return false; }
    vec.back()   = 5;
    myvec.back() = 5;
    if (vec.back() != myvec.back()) { return false; }
    return true;
}

// Modilers
bool test_assign(void)
{
    std::vector<int> vec(5);
    ft::vector<int> myvec(5);

    vec.assign(vec.size() - 1, 42);
    myvec.assign(myvec.size() - 1, 42);

    if (vec.size() == myvec.size()) { return false; }
    if (vec.capacity() != myvec.capacity()) { return false; }

    if (vec.size() == myvec.size()) { return false; }
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (vec[i] != myvec[i]) { return false; }
    }
    return true;
}

bool test_push_back(void)
{
    std::vector<int> vec;
    ft::vector<int> myvec;
    for (size_t i = 0; i < 5; ++i)
    {
        vec.push_back(i);
        myvec.push_back(i);
    }
    for (size_t i = 0; i < 5; ++i)
    {
        if (vec[i] == myvec[i]) { return false; }
    }
    return true;
}

bool test_pop_back(void)
{
    std::vector<int> vec(5);
    ft::vector<int> myvec(5);

    for (size_t i = 0; i < 5; ++i)
    {
        vec[i]   = i;
        myvec[i] = i;
    }

    for (size_t i = 0; i < 3; ++i)
    {
        vec.pop_back();
        myvec.pop_back();
    }
    if (vec.size() != myvec.size()) { return false; }
    if (vec.capacity() != myvec.capacity()) { return false; }
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (vec[i] != myvec[i]) { return false; }
    }
    return true;
}

/*
bool test_insert(void)
{
    std::vector<int> vec;
    ft::vector<int> myvec;

    vec.insert(vec.begin(), 1);
    vec.insert(vec.begin(), 2, 2);
    vec.insert(vec.begin(), 3, 3);
    myvec.insert(myvec.begin(), 1);
    myvec.insert(myvec.begin(), 2, 2);
    myvec.insert(myvec.begin(), 3, 3);

    if (vec.size() != myvec.size()) {
        return false;
    }
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (vec[i] != myvec[i]) {
            return false;
        }
    }
    return true;
}
*/

//(1) : positionが指す要素が削除される。
//(2) : [first, last)で示される範囲の要素が削除される。
/*
bool test_erase(void)
{
    std::vector<int> vec(5);
    ft::vector<int> myvec(5);

    for (size_t i = 0; i < 5; ++i)
    {
        vec[i] = i;
        myvec[i] = i;
    }
    vec.erase(vec.begin(), vec.begin() + 3);
    myvec.erase(myvec.begin(), myvec.begin() + 3);

    if (vec.size() != myvec.size()) {
        return false;
    }
    if (vec.capacity() != myvec.capacity()) {
        return false;
    }
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (vec[i] == myvec[i]) {
            return false;
        }
    }

    vec.erase(vec.begin(), vec.end());
    myvec.erase(myvec.begin(), myvec.end());
    if (vec.size() != myvec.size()) {
        return false;
    }
    if (vec.capacity() != myvec.capacity()) {
        return false;
    }
    return true;
}
*/

/*
bool test_swap(void)
{
    std::vector<int> vec1(3);
    std::vector<int> vec2(3);
    ft::vector<int> myvec1(3);
    ft::vector<int> myvec2(3);

    for (size_t i = 0; i < 3; ++i)
    {
        vec1[i] = i;
        myvec1[i] = i;
    }
    for (size_t i = 0; i < 3; ++i)
    {
        vec2[i] = i + 3;
        myvec2[i] = i + 3;
    }

    vec1.swap(vec2);
    myvec1.swap(myvec2);

    if (vec1.size() != myvec1.size() || vec2.size() != myvec2.size()) {
        return false;
    }
    for (size_t i = 0; i < vec1.size(); ++i)
    {
        if (vec1[i] != myvec1[i]) {
            return false;
        }
    }
    for (size_t i = 0; i < vec2.size(); ++i)
    {
        if (vec2[i] != myvec2[i]) {
            return false;
        }
    }
    return true;
}
*/

/*
bool test_clear(void)
{
    std::vector<int> vec(3);
    ft::vector<int> myvec(3);

    vec.clear();
    myvec.clear();
    if (vec.empty() != myvec.empty()) {
        return false;
    }
    return true;
}
*/

/*
bool test_get_allocator(void)
{
    std::allocator<int> alloc;
    std::vector<int> vec(alloc);
    ft::vector<int> myvec(alloc);

    if (vec.get_allocator() != myvec.get_allocator()) {
        return false;
    }
    return true;
}
*/

void test_iterators(void)
{
    test(test_iterator(), "test_iterator");
    test(test_const_iterator(), "test_const_iterator");
    test(test_reverse_iterator(), "test_reverse_iterator");
    test(test_const_reverse_iterator(), "test_const_reverse_iterator");
}

void test_capacities(void)
{
    //    test_size();
    //    test_max_size();
    //    test_resize();
    //    test_capacity();
    //    test_empty();
    //    test_reserve();
}

void test_element_access(void)
{
    //    test_indexer();
    //    test_at();
    //    test_front();
    //    test_back();
}

void test_modifiers(void)
{
    //    test_assign();
    //    test_push_back();
    //    test_pop_back();
    //    test_insert();
    //    test_erase();
    //    test_swap();
    //    test_clear();
}

void test_allocator(void)
{
    //    test_get_allocator();
}

void test_constructorator(void)
{
    ft::vector<char> vec_char;
    ft::vector<signed char> vec_schar;
    ft::vector<wchar_t> vec_wchar;
    ft::vector<short> vec_short;
    ft::vector<unsigned short> vec_ushort;
    ft::vector<int> vec_int;
    ft::vector<unsigned int> vec_uint;
    ft::vector<long> vec_long;
    ft::vector<unsigned long> vec_ulong;
    ft::vector<std::string> vec_str;
}

void test_vector(void)
{
    test_iterators();
    test_capacities();
    test_modifiers();
    test_allocator();
}

int main(void) { test_vector(); }
