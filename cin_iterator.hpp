#ifndef CIN_ITERATOR_HPP
#define CIN_ITERATOR_HPP

#include <iterator>

// 入力イテレーター
template <typename T>
struct cin_iterator
{
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using reference         = T &;
    using pointer           = T *;
    using iterator_category = std::input_iterator_tag;

    cin_iterator(bool fail = false) : fail(fail) { ++(*this); }

    // キャッシュした値を返す
    // const referenceの場合エラー
    const T &operator*() const { return value; }

    // 新しい値をキャッシュする
    cin_iterator &operator++()
    {
        if (!fail)
        {
            std::cin >> value;
            fail = std::cin.fail();
        }
        return *this;
    }

    //　後置インクリメント
    cin_iterator operator++(int)
    {
        auto old = *this;
        ++(*this);
        return old;
    }

    // イテレーターの等価比較の状態
    bool fail;
    // 値のキャッシュ
    value_type value;
};

template <typename T>
bool operator==(cin_iterator<T> const &l, cin_iterator<T> const &r)
{
    return l.fail == r.fail;
}

template <typename T>
bool operator!=(cin_iterator<T> const &l, cin_iterator<T> const &r)
{
    return !(l == r);
}

#endif
