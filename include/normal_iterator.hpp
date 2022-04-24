#ifndef NORMAL_ITERATOR_HPP
#define NORMAL_ITERATOR_HPP

#include <iterator>

#include "iterator_traits.hpp"

namespace ft
{
template <typename Iterator>
class normal_iterator : public std::iterator<std::random_access_iterator_tag, Iterator>
{
protected:
    Iterator current_;
    typedef ft::iterator_traits<Iterator> traits_type;

public:
    typedef Iterator                                iterator_type;
    typedef typename traits_type::iterator_category iterator_category;
    typedef typename traits_type::value_type        value_type;
    typedef typename traits_type::difference_type   difference_type;
    typedef typename traits_type::reference         reference;
    typedef typename traits_type::pointer           pointer;

    // Member functions
    normal_iterator()
        : current_(NULL)
    {
    }
    explicit normal_iterator(iterator_type it)
        : current_(it)
    {
    }

    template <typename T>
    normal_iterator(const normal_iterator<T>& other)
        : current_(other.base())
    {
    }

    template <typename T>
    normal_iterator& operator=(const normal_iterator<T>& other)
    {
        current_ = other.base();
        return *this;
    }
    ~normal_iterator()
    {
    }
    iterator_type base() const
    {
        return current_;
    }

    // Forward iterator requirements
    reference operator*() const
    {
        return *current_;
    }
    pointer operator->() const
    {
        return current_;
    }

    normal_iterator& operator++()
    {
        ++current_;
        return *this;
    }

    normal_iterator operator++(int)
    {
        normal_iterator tmp = *this;
        ++current_;
        return tmp;
    }

    // Bidirectional iterator requirements
    normal_iterator& operator--()
    {
        --current_;
        return *this;
    }

    normal_iterator operator--(int)
    {
        normal_iterator tmp = *this;
        --current_;
        return tmp;
    }

    // Random access iterator requirements
    reference operator[](difference_type n) const
    {
        return current_[n];
    }

    normal_iterator& operator+=(difference_type n)
    {
        current_ += n;
        return *this;
    }

    normal_iterator operator+(difference_type n) const
    {
        return normal_iterator(current_ + n);
    }

    normal_iterator& operator-=(difference_type n)
    {
        current_ -= n;
        return *this;
    }

    normal_iterator operator-(difference_type n) const
    {
        return normal_iterator(current_ - n);
    }
};

// Non-member functions

// Forward iterator requirements
template <typename IteratorL, typename IteratorR>
bool operator==(const normal_iterator<IteratorL>& lhs,
                const normal_iterator<IteratorR>& rhs)
{
    return lhs.base() == rhs.base();
}

template <typename IteratorL, typename IteratorR>
bool operator!=(const normal_iterator<IteratorL>& lhs,
                const normal_iterator<IteratorR>& rhs)
{
    return !(lhs == rhs);
}

template <typename Iterator>
bool operator!=(const normal_iterator<Iterator>& lhs,
                const normal_iterator<Iterator>& rhs)
{
    return !(lhs == rhs);
}

// Random access iterator requirements
template <typename IteratorL, typename IteratorR>
bool operator<(const normal_iterator<IteratorL>& lhs,
               const normal_iterator<IteratorR>& rhs)
{
    return lhs.base() < rhs.base();
}

template <typename Iterator>
bool operator<(const normal_iterator<Iterator>& lhs,
               const normal_iterator<Iterator>& rhs)
{
    return lhs.base() < rhs.base();
}

template <typename IteratorL, typename IteratorR>
bool operator>(const normal_iterator<IteratorL>& lhs,
               const normal_iterator<IteratorR>& rhs)
{
    return rhs < lhs;
}

template <typename Iterator>
bool operator>(const normal_iterator<Iterator>& lhs,
               const normal_iterator<Iterator>& rhs)
{
    return rhs < lhs;
}

template <typename IteratorL, typename IteratorR>
bool operator<=(const normal_iterator<IteratorL>& lhs,
                const normal_iterator<IteratorR>& rhs)
{
    return !(rhs < lhs);
}

template <typename Iterator>
bool operator<=(const normal_iterator<Iterator>& lhs,
                const normal_iterator<Iterator>& rhs)
{
    return !(rhs < lhs);
}

template <typename IteratorL, typename IteratorR>
bool operator>=(const normal_iterator<IteratorL>& lhs,
                const normal_iterator<IteratorR>& rhs)
{
    return !(lhs < rhs);
}

template <typename Iterator>
bool operator>=(const normal_iterator<Iterator>& lhs,
                const normal_iterator<Iterator>& rhs)
{
    return !(lhs < rhs);
}

template <typename IteratorL, typename IteratorR>
inline typename normal_iterator<IteratorL>::difference_type operator-(
    const normal_iterator<IteratorL>& lhs,
    const normal_iterator<IteratorR>& rhs)
{
    return lhs.base() - rhs.base();
}

template <typename Iterator>
inline normal_iterator<Iterator> operator+(
    typename normal_iterator<Iterator>::difference_type n,
    const normal_iterator<Iterator>& it)
{
    return normal_iterator<Iterator>(it.base() + n);
}

}    // namespace ft

#endif
