#ifndef STACK_HPP
#define STACK_HPP

/***********************/
#include "debug.hpp"
/***********************/
#include "iterator.hpp"
#include "normal_iterator.hpp"
#include "type_traits.hpp"
#include "utils.hpp"
#include "vector.hpp"

namespace ft
{
template <typename Tp, typename Sequence = ft::vector<Tp> >
class stack
{
public:
    typedef typename Sequence::value_type value_type;
    typedef typename Sequence::reference reference;
    typedef typename Sequence::const_reference const_reference;
    typedef typename Sequence::size_type size_type;
    typedef Sequence container_type;

    template <typename T, typename Seq>
    friend bool operator==(const stack<T, Seq>& lhs, const stack<T, Seq>& rhs);

    template <typename T, typename Seq>
    friend bool operator<(const stack<T, Seq>& lhs, const stack<T, Seq>& rhs);

protected:
    container_type c_;

public:
    /// Member functions

    // default constructor
    explicit stack(const Sequence& c = Sequence()) : c_(c)
    {
    }

    stack(const stack& other) : c_(other.c_)
    {
    }

    // destructor
    ~stack()
    {
    }

    const stack<Tp, Sequence>& operator=(const stack<Tp, Sequence>& other)
    {
        if (this != &other) c_ = other.c_;
        return *this;
    }

    /// Element access

    /**
     * @brief スタックの先頭要素への参照を返す
     */
    reference top()
    {
        return c_.back();
    }
    const_reference top() const
    {
        return c_.back();
    }

    /// Capacity

    /**
     * @brief 基礎となるコンテナが空の場合はtrue、それ以外はfalse返す
     */
    bool empty() const
    {
        return c_.empty();
    }

    /**
     * @brief 基礎となるコンテナ内の要素数を返す
     */
    size_type size() const
    {
        return c_.size();
    }

    /// Modifiers

    /**
     *  @brief 与えられた要素値valueをスタックの先頭にプッシュする。
     */
    void push(const value_type& value)
    {
        c_.push_back(value);
    }

    /**
     * @brief スタックから先頭の要素を削除する
     */
    void pop()
    {
        c_.pop_back();
    }
};

/// Non-member functions
template <typename Tp, typename Seq>
bool operator==(const stack<Tp, Seq>& lhs, const stack<Tp, Seq>& rhs)
{
    return lhs.c_ == rhs.c_;
}

template <typename Tp, typename Seq>
bool operator<(const stack<Tp, Seq>& lhs, const stack<Tp, Seq>& rhs)
{
    return lhs.c_ < rhs.c_;
}

// Based on operator==
template <typename Tp, typename Seq>
bool operator!=(const stack<Tp, Seq>& lhs, const stack<Tp, Seq>& rhs)
{
    return !(lhs == rhs);
}

// Based on operator<
template <typename Tp, typename Seq>
bool operator>(const stack<Tp, Seq>& lhs, const stack<Tp, Seq>& rhs)
{
    return rhs < lhs;
}

// Based on operator<
template <typename Tp, typename Seq>
bool operator<=(const stack<Tp, Seq>& lhs, const stack<Tp, Seq>& rhs)
{
    return !(rhs < lhs);
}

// Based on operator<
template <typename Tp, typename Seq>
bool operator>=(const stack<Tp, Seq>& lhs, const stack<Tp, Seq>& rhs)
{
    return !(lhs < rhs);
}

}    // namespace ft

#endif
