#ifndef IOTA_ITERATOR_HPP
#define IOTA_ITERATOR_HPP

#include <iterator>

// 前方イテレーター
template <typename T>
struct iota_iterator
{
    // イテレーター同士の距離を表現する型
    using difference_type = std::ptrdiff_t;
    // 要素の型
    using value_type = T;
    using reference  = T &;
    using pointer    = T *;
    // イテレーターカテゴリーは前方イテレーター
//    using iterator_category = std::forward_iterator_tag;
    // イテレーターカテゴリーは双方向イテレーター
    using iterator_category = std::bidirectional_iterator_tag;

    // 値を保持する
    T value;

    // コンストラクター
    iota_iterator(T value = 0) : value(value) {}

    T &operator*() { return value; }
    const T &operator*() const { return value; }

    // 前置
    iota_iterator &operator++()
    {
        ++value;
        return *this;
    }

    // 後置
    iota_iterator operator++(int)
    {
        auto temp = *this;
        ++(*this);
        return temp;
    }

    iota_iterator& operator--()
    {
        --value;
        return *this;
    }

    iota_iterator operator--(int)
    {
        auto temp = *this;
        --value;
        return temp;
    }

    iota_iterator& operator+=(difference_type n)
    {
        value += n;
        return *this;
    }

    // iterator + n
    iota_iterator operator+(difference_type n) const
    {
        auto temp = *this;
        temp += n;
        return *this;
    }

    iota_iterator& operator-=(difference_type n)
    {
        value -= n;
        return *this;
    }
    iota_iterator operator-(difference_type n) const
    {
        auto temp = *this;
        temp -= n;
        return *this;
    }

    difference_type operator -(iota_iterator const& i)
    {
        return value - i.value;
    }

    bool operator==(iota_iterator const &i) { return value == i.value; }
    bool operator!=(iota_iterator const &i) { return !(*this == i); }
    bool operator<(iota_iterator const& i) const
    {
        return value < i.value;
    }
    bool operator<=(iota_iterator const& i) const
    {
        return value <= i.value;
    }
    bool operator>(iota_iterator const& i) const
    {
        return value > i.value;
    }
    bool operator>=(iota_iterator const& i) const
    {
        return value >= i.value;
    }
};


// difference_type + iota_iteratorの場合
template <typename T>
iota_iterator<T> operator +
(
    typename iota_iterator<T>::difference_type n,
    iota_iterator<T> const& i
)
{
    return i + n;
}

template<typename T>
iota_iterator<T>operator -
(
    typename iota_iterator<T>::difference_type n,
    iota_iterator<T> const & i
)
{ return i - n; }


#endif
