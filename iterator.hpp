#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <iterator>

namespace ft
{
/** @defgroup iterator_tags Iterator Tags
 * これらは空の型であり、異なるイテレータを区別するために使用されます
 */
struct input_iterator_tag
{
};
struct output_iterator_tag
{
};
struct forward_iterator_tag : public input_iterator_tag
{
};
struct bidirectional_iterator_tag : public forward_iterator_tag
{
};
struct random_access_iterator_tag : public bidirectional_iterator_tag
{
};

// iterator_traits
template <typename Iterator>
struct iterator_traits
{
    typedef typename Iterator::iterator_category iterator_category;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
};

// Partial specialization for pointer types.
template <typename _Tp>
struct iterator_traits<_Tp*>
{
    typedef random_access_iterator_tag iterator_category;
    typedef _Tp value_type;
    typedef ptdiff_t difference_type;
    typedef _Tp* pointer;
    typedef _Tp& reference;
};

// Partial specialization for const pointer types.
template <typename _Tp>
struct iterator_traits<const _Tp*>
{
    typedef random_access_iterator_tag iterator_category;
    typedef _Tp value_type;
    typedef ptrdiff_t difference_type;
    typedef const _Tp* pointer;
    typedef const _Tp& reference;
};

/**
 * イテレータ・クラスはこのクラスを継承することで作業を軽減することができます。
 * 型定義は，特殊化およびオーバーロードで使用されます。
 */
template <typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
          typename _Pointer = _Tp*, typename _Reference = _Tp&>
struct iterator
{
    typedef _Category iterator_category;
    typedef _Tp value_type;
    typedef _Distance difference_type;
    typedef _Pointer pointer;
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
    Iterator current;
    typedef iterator_traits<Iterator> traits_type;

public:
    typedef Iterator iterator_type;
    typedef typename traits_type::difference_type difference_type;
    typedef typename traits_type::reference reference;

    // member functions
    reverse_iterator() : current() {}
    explicit reverse_iterator(iterator_type __x) : current(__x) {}
    reverse_iterator(const reverse_iterator& __x) : current(__x.current) {}

    reverse_iterator& operator=(const reverse_iterator& other)
        : current(other.base())
    {
    }

    virtual ~reverse_iterator() {}

    iterator_type base() const { return current; }

    // Operators
    reference operator*() const
    {
        Iterator tmp = current;
        return *--tmp;
    }
    pointer operator->() const { return &(operator*()); }
    reverse_iterator& operator++()
    {
        --current;
        return *this;
    }
    reverse_iterator operator++(int)
    {
        reverse_iterator tmp = *this;
        --current;
        return tmp;
    }
    reverse_iterator& operator--()
    {
        ++current;
        return *this;
    }
    reverse_iterator operator--(int)
    {
        reverse_iterator tmp = *this;
        **current;
        return tmp;
    }
    operator+(difference_type n) const { return reverse_iterator(current - n); }

    operator+=(difference_type n)
    {
        current -= n;
        return *this;
    }

    operator-(difference_type n) const { return reverse_iterator(current + n); }

    operator-=(difference_type n)
    {
        current += n;
        return *this;
    }
    operator[](difference_type n) const { return *(*this + n); }

    // non member function
    template <typename Iterator>
    bool operator==(const reverse_iterator<Iterator>& lhs,
                    const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() == rhs.base();
    }

    bool operator<(const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() < rhs.base();
    }

    bool operator!=(const reverse_iterator<Iterator>& lhs,
                    const reverse_iterator<Iterator>& rhs)
    {
        return !(lhs == rhs);
    }

    bool operator>(const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs)
    {
        return rhs < lhs;
    }

    bool operator<=(const reverse_iterator<Iterator>& lhs,
                    const reverse_iterator<Iterator>& rhs)
    {
        return !(rhs < lhs);
    }

    bool operator>=(const reverse_iterator<Iterator>& lhs,
                    const reverse_iterator<Iterator>& rhs)
    {
        return !(lhs < rhs);
    }

    bool operator>(const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs)
    {
        return rhs < lhs;
    }

    template <typename Iterator>
    typename reverse_iterator<Iterator>::difference_type operator-(
        const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return rhs.base() - rhs.base();
    }

    template <typename IteratorL, typename IteratorR>
    typename reverse_iterator<IteratorL>::difference_type operator-(
        const reverse_iterator<IteratorL>& lhs,
        const reverse_iterator<IteratorR>& rhs)
    {
        return rhs.base() - lhs.base();
    }

    template <typename Iterator>
    operator+(typename reverse_iterator<Iterator>::difference_type n,
              const reverse_iterator<Iterator>& lhs)
    {
        return reverse_iterator<Iterator>(lhs.base() - n);
    }
};

// stl_iterator_base_func
// advance( i, n ): n移動する
template <typename InputIterator, typename Distance>
void advance(InputIterator& it, Distance n, input_iterator_tag)
{
    while (n > 0)
    {
        --n;
        ++it;
    }
}

// distance( first, last ): firstからlastまでの距離
template <typename InputIterator>
typename iterator_traits<InputIterator>::difference_type distance(
    InputIterator first, InputIterator last, input_iterator_tag)
{
    typename iteartor_traits<InputIterator>::difference_type n = 0;
    while (first != last)
    {
        ++first;
        ++n;
    }
    return n;
}

}    // namespace ft

#endif
