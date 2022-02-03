#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include "iterator.hpp"
#include "utils.hpp"
#include "type_traits.hpp"
#include "normal_iterator.hpp"

namespace ft
{
template <typename T, typename Allocator = std::allocator<T> >
class vector
{
public:
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef size_t size_type;

    typedef ft::normal_iterator<value_type> iterator;
    typedef ft::normal_iterator<const value_type> const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    // constructor
    vector() :
    first_(NULL), last_(NULL), reserved_last_(NULL), alloc_(allocator_type()) {}

    explicit vector(const Allocator& alloc_)
        : first_(NULL), last_(NULL), reserved_last_(NULL), alloc_(alloc_)
    {
    }
    explicit vector(size_type count, const T& value = T(),
                    const Allocator& alloc_ = Allocator())
        : first_(NULL), last_(NULL), reserved_last_(NULL), alloc_(alloc_)
    {
        resize(count, value);
    }

    template <typename InputIt>
    vector(InputIt first_, InputIt last_, const Allocator& alloc_ = Allocator(),
           typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                   InputIt>::type* = NULL)
        : first_(NULL), last_(NULL), reserved_last_(NULL), alloc_(alloc_)
    {
        reserve(ft::distance(first_, last_));
        for (pointer i = first_; i != last_; ++i) { push_back(*i); }
    }

// copy constructor
    vector(const vector& other)
        : first_(NULL),
          last_(NULL),
          reserved_last_(NULL),
          alloc_(other.alloc_)
    {
        // コピー元の要素数を保持できるだけのストレージを確保
        reserve(other.size());
        // コピー元の要素をコピー構築
        // destはコピー先
        // [src, last_)はコピー元
        for (pointer dest = first_, src = other.begin(), last_ = other.end();
             src != last_; ++dest, ++src)
        {
            construct(dest, *src);
        }
        last_ = first_ + other.size();
    }

    // destructor
    ~vector()
    {
        // 1. 要素を末尾から先頭に向かう順番で破棄
        clear();
        // 2. 生のメモリーを解放する
        deallocate();
    }

    vector& operator=(const vector& r)
    {
        // 自分自身への代入なら何もしない
        if (this == &r) return *this;

        // 要素数が同じ
        if (size() == r.size())
        {
            // 要素ごとコピー代入
            std::copy(r.begin(), r.end(), begin());
        }
        else
        {
            // 予約数が十分
            if (capacity() >= r.size())
            {
                // 有効な要素はコピー
                std::copy(r.begin(), r.begin() + r.size(), begin());
                // 残りはコピー構築
                for (const_iterator src_iter = r.begin() + r.size(), src_end = r.end();
                     src_iter != src_end; ++src_iter, ++last_)
                {
                    construct(last_, *src_iter);
                }
            }
            else    // 予約数が不十分
            {
                // 要素をすべて破棄
                destroy_until(rbegin());
                // 予約
                reserve(r.size());
                // コピー構築
                for (const_iterator src_iter = r.begin(), src_end = r.end(),
                          dest_iter = begin();
                     src_iter != src_end; ++src_iter, ++dest_iter, ++last_)
                {
                    construct(dest_iter, *src_iter);
                }
            }
        }
        return *this;
    }

    void push_back(const_reference value)
    {
        // 予約メモリーが足りなければ拡張
        if (size() + 1 > capacity())
        {
            // 現在のストレージサイズ
            size_type c = size();
            // 0の場合は1に
            if (c == 0)
                c = 1;
            else
                // それ以外の場合は2倍する
                c *= 2;

            reserve(c);
        }
        // 要素を末尾に追加
        construct(last_, value);
        // 有効な要素数を更新
        ++last_;
    }

    // 容量確認
    size_type size() const { return end() - begin(); }
    bool empty() const { return begin() == end(); }
    size_type capacity() const { return reserved_last_ - first_; }

    // 要素アクセス
    reference operator[](size_type i) { return first_[i]; }
    const_reference operator[](size_type i) const { return first_[i]; }

    reference at(size_type i)
    {
        if (i >= size()) throw std::out_of_range("index is out of range.");
        return first_[i];
    }
    const_reference at(size_type i) const
    {
        if (i >= size()) throw std::out_of_range("index is out of range.");
        return first_[i];
    }

    // DEBUG
    reference front() { return *first_; }
    const_reference front() const { return *first_; }
    reference back() { return *(last_ - 1); }
    const_reference back() const { return *(last_ - 1); }

    pointer data() { return first_; }
    const_pointer data() const { return first_; }

    // イテレーターアクセス
    iterator begin() { return first_; }
    const_iterator begin() const { return first_; }
    iterator end() { return last_; }
    const_iterator end() const { return last_; }
    reverse_iterator rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const { return reverse_iterator(begin()); }

    void clear() { destroy_until(rend()); }

    void reserve(size_type sz)
    {
        // すでに指定された要素数以上に予約されているなら何もしない
        if (sz <= capacity()) return;

        // 動的メモリー確保をする
        pointer ptr = allocate(sz);

        // 古いストレージの情報を保存
        pointer old_first = first_;
        pointer old_last  = last_;
        //    auto old_capacity = capacity();

        // 新しいストレージに差し替え
        first_         = ptr;
        last_          = first_;
        reserved_last_ = first_ + sz;


        // 実際にはムーブ構築
        for (pointer old_iter = old_first; old_iter != old_last;
             ++old_iter, ++last_)
        {
            // このコピーの理解にはムーブセマンティクスの理解が必要
            construct(last_, *old_iter);
        }

        // 新しいストレージにコピーし終えたので古いストレージの値は破棄
        for (reverse_iterator riter = reverse_iterator(old_last),
                  rend  = reverse_iterator(old_first);
             riter != rend; ++riter)
        {
            destroy(&*riter);
        }
    }

    void resize(size_type sz)
    {
        // 現在の要素数より少ない
        if (sz < size())
        {
            size_type diff = size() - sz;
            destroy_until(rbegin() + diff);
            last_ = first_ + sz;
        }
        // 現在の要素数より大きい
        else if (sz > size())
        {
            reserve(sz);
            for (; last_ != reserved_last_; ++last_) { construct(last_); }
        }
    }

    void resize(size_type sz, const_reference value)
    {
        if (sz < size())
        {
            size_type diff = size() - sz;
            destroy_until(rbegin() + diff);
            last_ = first_ + sz;
        }
        else if (sz > size())
        {
            reserve(sz);
            for (; last_ != reserved_last_; ++last_)
            {
                construct(last_, value);    // ここが引数valueに変更されている
            }
        }
    }

protected:
    pointer first_;
    pointer last_;
    pointer reserved_last_;
    allocator_type alloc_;

    // ヘルパー関数

    pointer allocate(size_type n) { return alloc_.allocate(n); }
    void deallocate() { alloc_.deallocate(first_, capacity()); }
    void construct(pointer ptr) { alloc_.construct(ptr, 0); }
    void construct(pointer ptr, const_reference value)
    {
      alloc_.construct(ptr, value);
    }
    void destroy(pointer ptr) { alloc_.destroy(ptr); }

    void destroy_until(reverse_iterator rend)
    {
        for (reverse_iterator riter = rbegin(); riter != rend; ++riter, --last_)
        {
            destroy(&*riter);
        }
    }
};

}    // namespace ft

#endif
