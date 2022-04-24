#ifndef STACK_HPP
#define STACK_HPP

#include "algorithm.hpp"
#include "vector.hpp"

namespace ft
{
template <typename Tp, typename Sequence = ft::vector<Tp> >
class stack
{
public:
    typedef typename Sequence::value_type      value_type;
    typedef typename Sequence::reference       reference;
    typedef typename Sequence::const_reference const_reference;
    typedef typename Sequence::size_type       size_type;
    typedef Sequence                           container_type;

    template <typename T, typename Seq>
    friend bool operator==(const stack<T, Seq>& lhs, const stack<T, Seq>& rhs);

    template <typename T, typename Seq>
    friend bool operator<(const stack<T, Seq>& lhs, const stack<T, Seq>& rhs);

protected:
    container_type c;

public:
    /// Member functions

    // default constructor
    explicit stack(const Sequence& c = Sequence())
        : c(c)
    {
    }

    stack(const stack& other)
        : c(other.c)
    {
    }

    // destructor
    ~stack()
    {
    }

    const stack<Tp, Sequence>& operator=(const stack<Tp, Sequence>& other)
    {
        if (this != &other) c = other.c;
        return *this;
    }

    /// Element access

    /**
     * @brief スタックの先頭要素への参照を返す
     */
    reference top()
    {
        return c.back();
    }
    const_reference top() const
    {
        return c.back();
    }

    /// Capacity

    /**
     * @brief 基礎となるコンテナが空の場合はtrue、それ以外はfalse返す
     */
    bool empty() const
    {
        return c.empty();
    }

    /**
     * @brief 基礎となるコンテナ内の要素数を返す
     */
    size_type size() const
    {
        return c.size();
    }

    /// Modifiers

    /**
     *  @brief 与えられた要素値valueをスタックの先頭にプッシュする。
     */
    void push(const value_type& value)
    {
        c.push_back(value);
    }

    /**
     * @brief スタックから先頭の要素を削除する
     */
    void pop()
    {
        c.pop_back();
    }
};

/// Non-member functions
template <typename Tp, typename Seq>
bool operator==(const stack<Tp, Seq>& lhs, const stack<Tp, Seq>& rhs)
{
    return lhs.c == rhs.c;
}

template <typename Tp, typename Seq>
bool operator<(const stack<Tp, Seq>& lhs, const stack<Tp, Seq>& rhs)
{
    return lhs.c < rhs.c;
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
