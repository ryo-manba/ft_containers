#include <algorithm>
#include <iostream>
#include <vector>

#include "cin_iterator.hpp"
#include "cout_iterator.hpp"
#include "iota_iterator.hpp"

template <typename InputIterator>
void print(InputIterator iter, InputIterator end_iter)
{
    // 終了条件に達するまで
    while (iter != end_iter)
    {    // 値を標準出力する
        std::cout << *iter;
        ++iter;
    }
}

// 出力イテレーター
void testOutputIterator(void)
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    cout_iterator out;
    std::copy(std::begin(v), std::end(v), out);
}

// 入力イテレーター
void testInputIterator(void)
{
    cin_iterator<int> input, fail(true);
    std::vector<int> buffer;

    std::copy(input, fail, std::back_inserter(buffer));

    /* EOFが渡されるまで読み込む
     *   cin_iterator<std::string> iter, fail(true);
     *   print( iter, fail );
     */
}

// 双方向イテレーター
void testIotaIterator(void)
{
    iota_iterator<int> iter1(0), iter2(0);
    std::cout << *iter1 << std::endl;
    std::cout << ++(*iter1)<< std::endl;
    std::cout << (*iter1)++ << std::endl;
    std::cout << *iter1 << std::endl;

    iter1++;
    ++iter1;
    --iter1;
    iter1--;

    std::cout << --(*iter1) << std::endl;
    std::cout << (*iter1)-- << std::endl;
    std::cout << *iter1 << std::endl;

    std::cout << (iter1 == iter2) << std::endl;
    std::cout << (iter1 != iter2) << std::endl;
    std::cout << (iter1 > iter2) << std::endl;
    std::cout << (iter1 >= iter2) << std::endl;
    std::cout << (iter1 < iter2) << std::endl;
    std::cout << (iter1 <= iter2) << std::endl;

    iota_iterator<int> first(0), last(10);

    // 0123456789と出力される
//    std::for_each(first, last, [](auto i) { std::cout << i; });

    std::vector<int> v;
    std::copy(first, last, std::back_inserter(v));
    // vは{0,1,2,3,4,5,6,7,8,9}

    // 非constなオブジェクト
    iota_iterator<int> non_const(0);
    // 非const版のoperator *を呼び出す
    int value = *non_const;
    // 変更できる
    *non_const = 1;
    std::cout << value << std::endl;

    // constなオブジェクト
    const iota_iterator<int> immutable(0);
    // const版のoperator *を呼び出す
    int const_value = *immutable;
    // 変更はできない
    std::cout << const_value << std::endl;
}

int main(void)
{
    //    testOutputIterator();
    //    testInputIterator();
    testIotaIterator();
}
/*
int main()
{ 
    std::advance
    std::iterator_traits s
    std::reverse_iterator
}
*/
