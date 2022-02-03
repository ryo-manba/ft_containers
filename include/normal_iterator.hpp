#ifndef NORMAL_ITERATOR_HPP
#define NORMAL_ITERATOR_HPP

#include "iterator.hpp"
#include <iterator>

namespace ft
{
template<class T>
class normal_iterator : public ft::iterator<std::random_access_iterator_tag, T>
{
protected:
    T* current_;
//    typedef iterator_traits<Iterator> traits_type;
    typedef typename ft::iterator<std::random_access_iterator_tag, T> traits_type;

public:
    typedef typename traits_type::iterator_category iterator_category;
    typedef typename traits_type::value_type value_type;
    typedef typename traits_type::difference_type difference_type;
    typedef T& reference;
    typedef T* pointer;

    // Member functions
    normal_iterator() : current_(NULL) {}
    normal_iterator(pointer& p) : current_(p) {}
    normal_iterator(const normal_iterator& other)
        : current_(other.base()) { }
    normal_iterator& operator=(const normal_iterator& other)
    {
        if (this == &other)
            return *this;
        current_ = other.base();
        return *this;
    }
    pointer base() const { return current_; }
    ~normal_iterator() { }

    // Forward iterator requirements
    reference operator*() const { return *current_; }
    pointer operator->() const { return &(operator*()); }

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
    reference operator[](difference_type n) const { return current_[n]; }

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
        return lhs.base() != rhs.base();
    }

    template <typename Iterator>
    bool operator!=(const normal_iterator<Iterator>& lhs,
                    const normal_iterator<Iterator>& rhs)
    {
        return lhs.base() != rhs.base();
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
        return lhs.base() > rhs.base();
    }

    template <typename Iterator>
    bool operator>(const normal_iterator<Iterator>& lhs,
                   const normal_iterator<Iterator>& rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <typename IteratorL, typename IteratorR>
    bool operator<=(const normal_iterator<IteratorL>& lhs,
                    const normal_iterator<IteratorR>& rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template <typename Iterator>
    bool operator<=(const normal_iterator<Iterator>& lhs,
                    const normal_iterator<Iterator>& rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template <typename IteratorL, typename IteratorR>
    bool operator>=(const normal_iterator<IteratorL>& lhs,
                    const normal_iterator<IteratorR>& rhs)
    {
        return lhs.base() >= rhs.base();
    }

    template <typename Iterator>
    bool operator>=(const normal_iterator<Iterator>& lhs,
                    const normal_iterator<Iterator>& rhs)
    {
        return lhs.base() >= rhs.base();
    }


template <typename Iterator>
inline typename normal_iterator<Iterator>::difference_type operator-(
    const normal_iterator<Iterator>& lhs,
    const normal_iterator<Iterator>& rhs)
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
