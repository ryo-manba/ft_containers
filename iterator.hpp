#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>

// 出力イテレータ
struct cout_iterator
{
    using difference_type   = void;
    using value_type        = void;
    using reference         = void;
    using pointer           = void;
    using iterator_category = std::output_iterator_tag;

    cout_iterator& operator*() { return *this; }
    cout_iterator& operator++() { return *this; }
    cout_iterator& operator++(int) { return *this; }

    template <typename T>
    cout_iterator& operator=(T const& x)
    {
        std::cout << x;
        return *this;
    }
};

#endif
