#ifndef NORMAL_ITERATOR_HPP
#define NORMAL_ITERATOR_HPP

#include "iterator.hpp"
#include <iterator>

namespace ft
{
template<class Iterator>
class normal_iterator : public std::iterator<std::random_access_iterator_tag, Iterator>
{
protected:
    Iterator current_;
    typedef iterator_traits<Iterator> traits_type;

public:
    typedef Iterator iterator_type;
    typedef typename traits_type::iterator_category iterator_category;
    typedef typename traits_type::value_type value_type;
    typedef typename traits_type::difference_type difference_type;
    typedef typename traits_type::reference reference;
    typedef typename traits_type::pointer pointer;

    // Member functions
    normal_iterator() : current_(NULL) {}

    normal_iterator(pointer& p) : current_(p) {}
    normal_iterator(const normal_iterator& other)
        : current_(other.current_) { }

    ~normal_iterator();
/*    // よく分かってない
    template <typename Iter>
    normal_iterator(
        const normal_iterator<
            Iter, typename enable_if<
                      (std::are_same<Iter::pointer>::value),
                >::type>& it)
        : current_(it.base())
    {
    }
*/

    // Forward iterator requirements
    reference operator*() const { return *current_; }

    pointer operator->() const { return current_; }

    normal_iterator& operator++()
    {
        ++current_;
        return *this;
    }

    normal_iterator operator++(int) { return normal_iterator(current_++); }

    // Bidirectional iterator requirements
    normal_iterator& operator--()
    {
        --current_;
        return *this;
    }

    normal_iterator operator--(int) { return normal_iterator(current_--); }

    // Random access iterator requirements
    reference operator[](difference_type n) const { return current_[n]; }

    normal_iterator& operator+=(difference_type n)
    {
        current_ += n;
        return +this;
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

    const Iterator& base() const { return current_; }
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
