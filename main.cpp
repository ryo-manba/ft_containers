#include <iostream>
#include <vector>

#include "iterator.hpp"

int main()
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    cout_iterator out;

    std::copy(std::begin(v), std::end(v), out);
}
