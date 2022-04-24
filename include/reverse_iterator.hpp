#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <cstddef>
#include <iterator>

#include "iterator_traits.hpp"

namespace ft
{

/**
 * イテレータ・クラスはこのクラスを継承することで作業を軽減することができます。
 * 型定義は，特殊化およびオーバーロードで使用されます。
 */
template <typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
          typename _Pointer = _Tp*, typename _Reference = _Tp&>
struct iterator
{
    typedef _Category  iterator_category;
    typedef _Tp        value_type;
    typedef _Distance  difference_type;
    typedef _Pointer   pointer;
    typedef _Reference reference;
};

// reverse iterator
template <typename Iterator>
class reverse_iterator
    : public iterator<typename iterator_traits<Iterator>::iterator_category,
                      typename iterator_traits<Iterator>::value_type,
                      typename iterator_traits<Iterator>::difference_type,
                      typename iterator_traits<Iterator>::pointer,
                      typename iterator_traits<Iterator>::reference>
{
protected:
    Iterator current_;
    typedef iterator_traits<Iterator> traits_type;

public:
    typedef Iterator                                iterator_type;
    typedef typename traits_type::iterator_category iterator_category;
    typedef typename traits_type::value_type        value_type;
    typedef typename traits_type::difference_type   difference_type;
    typedef typename traits_type::reference         reference;
    typedef typename traits_type::pointer           pointer;

    // member functions
    reverse_iterator()
        : current_()
    {
    }
    explicit reverse_iterator(iterator_type it)
        : current_(it)
    {
    }

    template <typename Iter>
    reverse_iterator(const reverse_iterator<Iter>& other)
        : current_(other.base())
    {
    }

    reverse_iterator(const reverse_iterator& other)
        : current_(other.base())
    {
    }

    reverse_iterator& operator=(const reverse_iterator& other)
    {
        current_ = other.base();
        return *this;
    }

    virtual ~reverse_iterator()
    {
    }

    iterator_type base() const
    {
        return current_;
    }

    // Operators
    reference operator*() const
    {
        Iterator tmp = current_;
        return *--tmp;
    }
    pointer operator->() const
    {
        return &(operator*());
    }
    reverse_iterator& operator++()
    {
        --current_;
        return *this;
    }
    reverse_iterator operator++(int)
    {
        reverse_iterator tmp = *this;
        --current_;
        return tmp;
    }
    reverse_iterator& operator--()
    {
        ++current_;
        return *this;
    }
    reverse_iterator operator--(int)
    {
        reverse_iterator tmp = *this;
        ++current_;
        return tmp;
    }
    reverse_iterator operator+(difference_type n) const
    {
        return reverse_iterator(current_ - n);
    }

    reverse_iterator& operator+=(difference_type n)
    {
        current_ -= n;
        return *this;
    }

    reverse_iterator operator-(difference_type n) const
    {
        return reverse_iterator(current_ + n);
    }

    reverse_iterator& operator-=(difference_type n)
    {
        current_ += n;
        return *this;
    }
    reference operator[](difference_type n) const
    {
        return *(*this + n);
    }
};

/**
 *  @param  __x  A %reverse_iterator.
 *  @param  __y  A %reverse_iterator.
 *  @return  A simple bool.
 *
 *  Reverse iterators forward comparisons to their underlying base() iterators.
 */

// non member function
template <typename Iterator>
bool operator==(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs)
{
    return lhs.base() == rhs.base();
}

template <typename Iterator>
bool operator<(const reverse_iterator<Iterator>& lhs,
               const reverse_iterator<Iterator>& rhs)
{
    return rhs.base() < lhs.base();
}

template <typename Iterator>
bool operator!=(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs)
{
    return !(lhs == rhs);
}

template <typename Iterator>
bool operator>(const reverse_iterator<Iterator>& lhs,
               const reverse_iterator<Iterator>& rhs)
{
    return rhs < lhs;
}

template <typename Iterator>
bool operator<=(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs)
{
    return !(rhs < lhs);
}

template <typename Iterator>
bool operator>=(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs)
{
    return !(lhs < rhs);
}

template <typename IteratorL, typename IteratorR>
bool operator==(const reverse_iterator<IteratorL>& lhs,
                const reverse_iterator<IteratorR>& rhs)
{
    return lhs.base() == rhs.base();
}

template <typename IteratorL, typename IteratorR>
bool operator<(const reverse_iterator<IteratorL>& lhs,
               const reverse_iterator<IteratorR>& rhs)
{
    return rhs.base() < lhs.base();
}

template <typename IteratorL, typename IteratorR>
bool operator!=(const reverse_iterator<IteratorL>& lhs,
                const reverse_iterator<IteratorR>& rhs)
{
    return !(lhs == rhs);
}

template <typename IteratorL, typename IteratorR>
bool operator>(const reverse_iterator<IteratorL>& lhs,
               const reverse_iterator<IteratorR>& rhs)
{
    return rhs < lhs;
}

template <typename IteratorL, typename IteratorR>
bool operator<=(const reverse_iterator<IteratorL>& lhs,
                const reverse_iterator<IteratorR>& rhs)
{
    return !(rhs < lhs);
}

template <typename IteratorL, typename IteratorR>
bool operator>=(const reverse_iterator<IteratorL>& lhs,
                const reverse_iterator<IteratorR>& rhs)
{
    return !(lhs < rhs);
}

template <typename Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(
    const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs)
{
    return rhs.base() - lhs.base();
}

template <typename IteratorL, typename IteratorR>
typename reverse_iterator<IteratorL>::difference_type operator-(
    const reverse_iterator<IteratorL>& lhs,
    const reverse_iterator<IteratorR>& rhs)
{
    return rhs.base() - lhs.base();
}

template <typename Iterator>
reverse_iterator<Iterator> operator+(
    typename reverse_iterator<Iterator>::difference_type n,
    const reverse_iterator<Iterator>& lhs)
{
    return reverse_iterator<Iterator>(lhs.base() - n);
}

}    // namespace ft

#endif
