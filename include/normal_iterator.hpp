#ifndef NORMAL_ITERATOR_HPP
#define NORMAL_ITERATOR_HPP

#include "iterator.hpp"

namespace ft
{
template <typename Iterator, typename Container>
class normal_iterator
{
protected:
    Iterator current_;
    typedef iterator_traits<Iterator> traits_type;

    typedef typename Iterator iterator_type;
    typedef typename traits_type::iterator_category iterator_category;
    typedef typename traits_type::value_type value_type;
    typedef typename traits_type::difference_type difference_type;
    typedef typename traits_type::reference reference;
    typedef typename traits_type::pointer pointer;

    // Member functions
    normal_iterator() : current_(Iterator()) {}

    normal_iterator(const Iterator& it) : current_(it) {}

    // よく分かってない
    template <typename Iter>
    normal_iterator(
        const normal_iterator<
            Iter, typename enable_if<
                      (std::are_same<Iter, typename Container::pointer>::value),
                      Container>::type>& it)
        : current_(it.base())
    {
    }

    // Forward iterator requirements
    reference operator*() const { return *current_; }

    pointer operator->() const { return current_; }

    normal_iterator& operator++()
    {
        ++current_;
        return *this;
    }

    normal_iterator operator++(int) { return normal_iterator(current_++;) }

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
        current -= n;
        return *this;
    }

    normal_iterator operator-(difference_type n) const
    {
        return normal_iterator(current_ - n);
    }

    const Iterator& base() { return current_; }

    // Non-member functions

    // Forward iterator requirements
    template <class IteratorL, typename IteratorR, typename Container>
    bool operator==(const normal_iterator<IteratorL, Container>& lhs,
                    const normal_iterator<IteratorR, Container>& rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <typename Iterator, typename Container>
    bool operator==(const normal_iterator<Iterator, Container>& lhs,
                    const normal_iterator<IteratorR, Container>& rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <typename IteratorL, typename IteratorR, typename Container>
    bool operator!=(const normal_iterator<IteratorL, Container>& lhs,
                    const normal_iterator<IteratorR, Container>& rhs)
    {
        return lhs.base() != rhs.base();
    }

    template <typename Iterator, typename Container>
    bool operator!=(const normal_iterator<Iterator, Container>& lhs,
                    const normal_iterator<Iterator, Container>& rhs)
    {
        return lhs.base() != rhs.base();
    }

    // Random access iterator requirements
    template <typename IteratorL, typename IteratorR, typename Container>
    bool operator<(const normal_iterator<IteratorL, Container>& lhs,
                   const normal_iterator<IteratorR, Container>& rhs)
    {
        return lhs.base() < rhs.base();
    }

    template <typename Iterator, typename Container>
    bool operator<(const normal_iterator<Iterator, Container>& lhs,
                   const normal_iterator<Iterator, Container>& rhs)
    {
        return lhs.base() < rhs.base();
    }

    template <typename IteratorL, typename IteratorR, typename Container>
    bool operator>(const normal_iterator<IteratorL, Container>& lhs,
                   const normal_iterator<IteratorR, Container>& rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <typename Iterator, typename Container>
    bool operator>(const normal_iterator<Iterator, Container>& lhs,
                   const normal_iterator<Iterator, Container>& rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <typename IteratorL, typename IteratorR, typename Container>
    bool operator<=(const normal_iterator<IteratorL, Container>& lhs,
                    const normal_iterator<IteratorR, Container>& rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template <typename Iterator, typename Container>
    bool operator<=(const normal_iterator<Iterator, Container>& lhs,
                    const normal_iterator<Iterator, Container>& rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template <typename IteratorL, typename IteratorR, typename Container>
    bool operator>=(const normal_iterator<IteratorL, Container>& lhs,
                    const normal_iterator<IteratorR, Container>& rhs)
    {
        return lhs.base() >= rhs.base();
    }

    template <typename Iterator, typename Container>
    bool operator>=(const normal_iterator<Iterator, Container>& lhs,
                    const normal_iterator<Iterator, Container>& rhs)
    {
        return lhs.base() >= rhs.base();
    }
};

template <typename Iterator, typename Container>
inline typename normal_iterator<Iterator, Container>::difference_type operator-(
    const normal_iterator<Iterator, Container>& lhs,
    const normal_iterator<Iterator, Container>& rhs)
{
    return lhs.base() - rhs.base();
}

template <typename Iterator, typename Container>
inline normal_iterator<Iterator, Container> operator+(
    typename normal_iterator<Iterator, Container>::difference_type n,
    const normal_iterator<Iterator, Container>& it)
{
    return normal_iterator<Iterator, Container>(it.base() + n);
}

}    // namespace ft

#endif
