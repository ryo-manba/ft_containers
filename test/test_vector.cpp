#include <iostream>
#include <vector>
#include "vector.hpp"

#define debug(var)  do{std::cout << #var << " : ";view(var);}while(0)
template<typename T> void view(T e){std::cout << e << std::endl;}

#define SIZE 5

// Iterators
template <typename T>
void testIterator(T vec)
{
    std::cout << "-----" << __func__ << "-----" << std::endl;

    typename T::iterator it = vec.begin();
    typename T::iterator ite = vec.end();
    for (; it != ite; ++it)
    {
        std::cout << *it << std::endl;
    }
}

template <typename T>
void testConstIterator(T vec)
{
    std::cout << "-----" << __func__ << "-----" << std::endl;

    typename T::const_iterator cit = vec.begin();
    typename T::const_iterator cite = vec.end();
    for (; cit != cite; ++cit)
    {
        std::cout << *cit << std::endl;
    }
}

template <typename T>
void testRevIterator(T vec)
{
    std::cout << "-----" << __func__ << "-----" << std::endl;

    typename T::reverse_iterator rit = vec.rbegin();
    typename T::reverse_iterator rite = vec.rend();
    for (; rit != rite; ++rit)
    {
        std::cout << *rit << std::endl;
    }
}

template <typename T>
void testConstRevIterator(T vec)
{
    std::cout << "-----" << __func__ << "-----" << std::endl;

    typename T::const_reverse_iterator crit = vec.rbegin();
    typename T::const_reverse_iterator crite = vec.rend();
    for (; crit != crite; ++crit)
    {
        std::cout << *crit << std::endl;
    }
}

// Capacity
template <typename T>
void testSize(T vec)
{
    std::cout << "-----" << __func__ << "-----" << std::endl;
    std::cout << vec.size() << std::endl;
}

template <typename T>
void testMaxSize(T vec)
{
    std::cout << "-----" << __func__ << "-----" << std::endl;
    std::cout << vec.max_size() << std::endl;
}

template <typename T>
void testResize(T vec)
{
    std::cout << "-----" << __func__ << "-----" << std::endl;
    std::cout << vec.size() << std::endl;
    vec.resize(0);
    std::cout << vec.size() << std::endl;
    vec.resize(10);
    std::cout << vec.size() << std::endl;
}

template <typename T>
void testCapacity(T vec)
{
    std::cout << "-----" << __func__ << "-----" << std::endl;

    for (size_t i = 0; i < SIZE; ++i)
    {
        vec.push_back(i);
        std::cout << vec.capacity() << std::endl;
    }
}

template <typename T>
void testEmpty(T vec)
{
    std::cout << "-----" << __func__ << "-----" << std::endl;

    std::cout << vec.empty() << std::endl;
    T a;
    std::cout << a.empty() << std::endl;
}

template <typename T>
void testReserve(T vec)
{
    std::cout << "-----" << __func__ << "-----" << std::endl;

    vec.reserve(0);
    std::cout << vec.capacity() << std::endl;

    vec.reserve(1);
    std::cout << vec.capacity() << std::endl;

    vec.reserve(10);
    std::cout << vec.capacity() << std::endl;
}

// Element Access
template <typename T>
void testIndexer(T vec)
{
    std::cout << "-----" << __func__ << "-----" << std::endl;

    for (size_t i = 0; i < SIZE; ++i)
    {
        vec[i] = i;
    }
    for (size_t i = 0; i < SIZE; ++i)
    {
        std::cout << vec[i] << std::endl;
    }
}

template<typename T>
void testAt(T vec)
{
    std::cout << "-----" << __func__ << "-----" << std::endl;

    for (size_t i = 0; i < SIZE; ++i)
    {
        vec.at(i) = i;
    }
    for (size_t i = 0; i < SIZE; ++i)
    {
        std::cout << vec.at(i) << std::endl;
    }
}

template<typename T>
void testFront(T vec)
{
    std::cout << "-----" << __func__ << "-----" << std::endl;

    std::cout << vec.front() << std::endl;
    vec[0] = 42;
    std::cout << vec.front() << std::endl;
}

template<typename T>
void testBack(T vec)
{
    std::cout << "-----" << __func__ << "-----" << std::endl;

    std::cout << vec.back() << std::endl;
    vec[vec.size()-1] = 42;
    std::cout << vec.back() << std::endl;
}

/*
template<typename T>
void testData(T vec)
{
    std::cout << "-----" << __func__ << "-----" << std::endl;

    std::cout << vec.data() << std::endl;
    std::cout << *vec.data() << std::endl;
}
*/

// Modilers
template <typename T>
void testAssign(T vec)
{
    std::cout << "-----" << __func__ << "-----" << std::endl;

    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << std::endl;
    }
    vec.assign(vec.size()-1, 42);
    std::cout << vec.size() << std::endl;
    std::cout << vec.capacity() << std::endl;
    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << std::endl;
    }
}

template <typename T>
void testPushBack(T vec)
{
    std::cout << "-----" << __func__ << "-----" << std::endl;

    for (size_t i = 0; i < SIZE; ++i)
    {
        vec.push_back(i);
    }
    for (size_t i = 0; i < SIZE; ++i)
    {
        std::cout << vec[i] << std::endl;
    }
}

template <typename T>
void testPopBack(T vec)
{
    std::cout << "-----" << __func__ << "-----" << std::endl;

    size_t sz = vec.size();
    std::cout << sz << std::endl;
    for (size_t i = 0; i < sz; ++i)
    {
        vec.pop_back();
    }
    std::cout << vec.size() << std::endl;
    std::cout << vec.capacity() << std::endl;
}

template <typename T>
void testInsert(T vec)
{
    std::cout << "-----" << __func__ << "-----" << std::endl;

    vec.insert(vec.begin(), 1);
    vec.insert(vec.begin(), 2, 2);
    vec.insert(vec.begin(), 3, 3);

    std::cout << "size : " << vec.size() << std::endl;
    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << std::endl;
    }
}

//(1) : positionが指す要素が削除される。
//(2) : [first, last)で示される範囲の要素が削除される。
template <typename T>
void testErase(T vec)
{
    std::cout << "-----" << __func__ << "-----" << std::endl;

    std::cout << "size : " << vec.size() << std::endl;
    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << std::endl;
    }

    vec.erase(vec.begin(), vec.begin() + 3);
    std::cout << "size     : " << vec.size() << std::endl;
    std::cout << "capacity : " << vec.capacity() << std::endl;
    for (size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i] << std::endl;
    }

    vec.erase(vec.begin(), vec.end());
    std::cout << "size     : " << vec.size() << std::endl;
    std::cout << "capacity : " << vec.capacity() << std::endl;
}

template <typename T>
void testSwap(T vec)
{
    std::cout << "-----" << __func__ << "-----" << std::endl;

    static_cast<void>(vec);
    std::vector<int> v1;
    std::vector<int> v2;

    for (size_t i = 0; i < 3; ++i)
    {
        v1.push_back(i);
        v2.push_back(i+3);
    }

    v1.swap(v2);
    std::cout << "v1 : ";
    for (size_t i = 0; i < v1.size(); ++i) std::cout << v1[i] << " ";
    std::cout << "v2 : ";
    for (size_t i = 0; i < v2.size(); ++i) std::cout << v2[i] << " ";
}

template <typename T>
void testClear(T vec)
{

    T temp = vec;
    vec.clear();
    std::cout << vec.empty() << std::endl;
    vec = temp;
}

template <typename T>
void testGetAllocator(T vec)
{
    int* p = vec.get_allocator().allocate(2);
//    p[0] = 42;
//    p[1] = 84;
//    std::cout << p[0] << " " << p[1] << std::endl;
    vec.get_allocator().deallocate(p, 2);
}

template<typename T>
void testIterators(T vec)
{
    testIterator(vec);
    testConstIterator(vec);
    testRevIterator(vec);
    testConstRevIterator(vec);
}

template <typename T>
void testCapacities(T vec)
{
    testSize(vec);
//    testMaxSize(vec);
    testResize(vec);
    testCapacity(vec);
    testEmpty(vec);
    testReserve(vec);
}

template<typename T>
void testElementAccess(T vec)
{
    testIndexer(vec);
    testAt(vec);
    testFront(vec);
    testBack(vec);
}

template<typename T>
void testModifiers(T vec)
{
//    testAssign(vec);
    testPushBack(vec);
//    testPopBack(vec);
//    testInsert(vec);
//    testErase(vec);
    testSwap(vec);
//    testClear(vec);
}

template<typename T>
void testAllocator(T vec)
{
    static_cast<void>(vec);
//    testGetAllocator(vec);
}

void testVector(void)
{
    ft::vector<int> vec;

//    testIterators(vec);
//    testCapacities(vec);
//    testModifiers(vec);
//    testAllocator(vec);
}

int main(void)
{
    testVector();
}
