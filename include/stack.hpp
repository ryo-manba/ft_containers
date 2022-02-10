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

/**
 * @fn
 * ここに関数の説明を書く
 * @brief 要約説明
 * @param (引数名) 引数の説明
 * @param (引数名) 引数の説明
 * @return 戻り値の説明
 * @sa 参照すべき関数を書けばリンクが貼れる
 * @detail 詳細な説明
 */

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

protected:
    Sequence c_;

public:
    // constoractor
    explicit stack(const Sequence& c = Sequence()) : c_(c){}

    stack(const stack& other) : c_(other.c_){}
    ~stack(){}

    /**
     * @brief Returns true if the %stack is empty.
     */
    bool empty() const
    {
        return c_.empty;
    }

    /**
     * @brief Returns the number of elements in the %stack.
     */
    size_type size() const
    {
        return c_.size();
    }

    /**
     * @brief
     * Returns a read/write reference to the data at the first
     * element of the %stack.
     */
    reference top()
    {
        // 空のときはassert投げるっぽい
        // if (c_.empty())
        return c_.back();
    }
    const_reference top() const
    {
        return c_.back();
    }
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

    // operators
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
        return !(lhs.c_ == rhs.c_);
    }

    // Based on operator<
    template <typename Tp, typename Seq>
    bool operator>(const stack<Tp, Seq>& lhs, const stack<Tp, Seq>& rhs)
    {
        return rhs.c_ < lhs.c_;
    }

    // Based on operator<
    template <typename Tp, typename Seq>
    bool operator<=(const stack<Tp, Seq>& lhs, const stack<Tp, Seq>& rhs)
    {
        return !(rhs < lhs);
    }

    // Based on operator<
    template <typename Tp, typename Seq>
    inline bool operator>=(const stack<Tp, Seq>& lhs, const stack<Tp, Seq>& rhs)
    {
        return !(lhs < rhs);
    }
}    // namespace ft

#endif
