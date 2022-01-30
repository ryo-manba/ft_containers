#include <iostream>
#include <vector>

#include "cin_iterator.hpp"
#include "cout_iterator.hpp"

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

void testOutputIterator(void)
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    cout_iterator out;

    std::copy(std::begin(v), std::end(v), out);
}

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

int main(void)
{
    testOutputIterator();
    testInputIterator();
}
