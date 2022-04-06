#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <limits>
#include <memory>

/***********************/
#include "debug.hpp"
/***********************/
#include "iterator.hpp"
#include "normal_iterator.hpp"
#include "type_traits.hpp"
#include "utils.hpp"
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
template <typename T, typename Allocator = std::allocator<T> >
class vector
{
public:
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef size_t size_type;

    typedef ft::normal_iterator<value_type> iterator;
    typedef ft::normal_iterator<value_type> const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    // constructor
    vector()
        : first_(NULL),
          last_(NULL),
          reserved_last_(NULL),
          alloc_(allocator_type())
    {
    }

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

    /*
        template< class InputIt >
        vector( InputIt first, InputIt last,
            const Allocator& alloc = Allocator() )
        {

        }
        */

    template <typename InputIt>
    vector(InputIt first, InputIt last, const Allocator& alloc_ = Allocator(),
           typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                  InputIt>::type* = NULL)
        : first_(NULL), last_(NULL), reserved_last_(NULL), alloc_(alloc_)
    {
        reserve(std::distance(first, last));
        for (iterator it = first; it != last; ++it)
        {
            push_back(*it);
        }
    }

    // copy constructor
    vector(const vector& other)
        : first_(NULL), last_(NULL), reserved_last_(NULL), alloc_(other.alloc_)
    {
        // コピー元の要素数を保持できるだけのストレージを確保
        reserve(other.size());
        // コピー元の要素をコピー構築
        // destはコピー先
        // [src, last_)はコピー元
        // FIXME: dest = first_がおかしそう
        for (iterator dest = first_, src = other.begin(), last = other.end();
             src != last; ++dest, ++src)
        {
            construct(dest.base(), *src);
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
                for (const_iterator src_iter = r.begin() + r.size(),
                                    src_end  = r.end();
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
                    construct(dest_iter.base(), *src_iter);
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
    size_type size() const
    {
        return end() - begin();
    }
    bool empty() const
    {
        return begin() == end();
    }
    size_type capacity() const
    {
        return reserved_last_ - first_;
    }

    // 要素アクセス
    reference operator[](size_type i)
    {
        return first_[i];
    }
    const_reference operator[](size_type i) const
    {
        return first_[i];
    }

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
    reference front()
    {
        return *first_;
    }
    const_reference front() const
    {
        return *first_;
    }
    reference back()
    {
        return *(last_ - 1);
    }
    const_reference back() const
    {
        return *(last_ - 1);
    }

    pointer data()
    {
        return first_;
    }
    const_pointer data() const
    {
        return first_;
    }

    // イテレーターアクセス
    iterator begin()
    {
        return first_;
    }
    const_iterator begin() const
    {
        return first_;
    }
    iterator end()
    {
        return last_;
    }
    const_iterator end() const
    {
        return last_;
    }
    reverse_iterator rbegin()
    {
        return reverse_iterator(end());
    }
    const_reverse_iterator rbegin() const
    {
        return reverse_iterator(end());
    }
    reverse_iterator rend()
    {
        return reverse_iterator(begin());
    }
    const_reverse_iterator rend() const
    {
        return reverse_iterator(begin());
    }

    void clear()
    {
        destroy_until(rend());
    }

    void reserve(size_type sz)
    {
        // TODO: 例外チェック
        if (sz > max_size())
        {
            //            throw length_error("vector::reserve");
            throw std::out_of_range("vector::reserve");
        }
        // すでに指定された要素数以上に予約されているなら何もしない
        if (sz <= capacity())
        {
            return;
        }

        // 動的メモリー確保をする
        pointer ptr = allocate(sz);

        // 古いストレージの情報を保存
        pointer old_first      = first_;
        pointer old_last       = last_;
        size_type old_capacity = capacity();

        // 新しいストレージに差し替え
        first_         = ptr;
        last_          = first_;
        reserved_last_ = first_ + sz;

        // 実際にはムーブ構築
        for (pointer old_iter = old_first; old_iter != old_last;
             ++old_iter, ++last_)
        {
            construct(last_, *old_iter);
        }

        // 新しいストレージにコピーし終えたので古いストレージの値は破棄
        for (reverse_iterator riter = reverse_iterator(old_last),
                              rend  = reverse_iterator(old_first);
             riter != rend; ++riter)
        {
            destroy(&*riter);
        }
        alloc_.deallocate(old_first, old_capacity);
    }

    /**
     * コンテナのサイズを変更し、count 個の要素を含むようにする。
     * 現在のサイズが count より大きい場合、コンテナは最初の count
     * 要素まで縮小される。 現在のサイズが count より小さい場合。
     * 1. デフォルトで挿入されている要素が追加で挿入される
     * 2. value のコピーを追加する。
     */
    void resize(size_type sz, value_type val = value_type())
    {
        // 現在の要素数より少ない
        if (sz < size())
        {
            erase(begin() + sz, end());
        }
        // 現在の要素数より大きい
        else if (sz > size())
        {
            insert(end(), sz - size(), val);
        }
    }

    // コンテナが保持できる最大の要素数を返す
    size_type max_size(void) const
    {
        const size_t diffmax = std::numeric_limits<size_type>::max() /
                               sizeof(value_type);    // GCC
        const size_t allocmax = std::numeric_limits<difference_type>::max();

        return std::min<size_type>(diffmax, allocmax);
    }

    /**
     * コンテナの再代入。
     * (1) : 範囲を代入。
     * (2) : n個の値tを代入。
     * capacityがnより大きい場合、要素をそのまま埋めるだけ。
     * capacityがnより小さい場合、新たにallocateし直す。
     */
    void assign(size_type n, const value_type& val)
    {
        size_type cap = capacity();

        if (n > cap)
        {
            clear();
            reserve(n);
        }
        pointer t = first_;
        for (size_type i = 0; i < n; ++i)
        {
            *t = val;
            ++t;
        }
        last_ = t;
    }

    template<class InputIt>
    void assign(InputIt first, InputIt last)
    {
        clear();
        insert(begin(), first, last);
    }

    /**
     * @brief posの前にvalueを挿入する。
     * @return 挿入された値を指すイテレータ
     */

    /**
     * [example]
     * a b c
     * a と b の間に [x y] を挿入する
     * - a はそのまま
     * - b c をmemmove
     * a     b c
     * - a と　b の間に挿入する
     * a x y b c
     */
    iterator insert(const_iterator pos, const value_type& value)
    {
        difference_type offset = std::distance(begin(), pos);
        insert(pos, 1, value);
        return begin() + offset;
    }

    /**
     * @brief posの前にvalueをcountの数挿入する。
     * offset: 先頭から挿入するまでの位置
     */
    void insert(const_iterator pos, size_type count, const value_type& value)
    {
        if (count == 0) return;

        // offset: 先頭から挿入するまでの位置
        difference_type offset = std::distance(begin(), pos);
        size_type new_size     = size() + count;
        size_type c            = capacity();

        // 予約メモリーが足りなければ拡張
        while (c < new_size)
        {
            if (c == 0)
                c = 1;
            else
                c *= 2;
        }
        reserve(c);

        // 追加で確保した要素のコンストラクタを呼ぶ
        for (; last_ != first_ + new_size; ++last_) construct(last_);

        iterator ite = last_ - 1;

        // endから要素を挿入する先頭(pos + count - 1)までmemmoveする
        iterator move_end_pos = begin() + offset + count - 1;
        for (; ite != move_end_pos; --ite)
        {
            *ite = *(ite - count);
        }

        // insertのスタート地点まで要素を挿入する
        iterator start_pos = begin() + offset - 1;
        for (; ite != start_pos; --ite)
        {
            *ite = value;
        }
    }

    /**
     * @brief posの前に範囲[first, last]の要素を挿入する。
     * first と last が *this へのイテレータの場合、動作は未定義。
     * enable_if
     * 整数型かどうかを判定している。
     * enable_ifの第2型パラメータはデフォルトがvoidなので::typeはvoidとなる
     */
    template <class InputIt>
    typename ft::enable_if<!ft::is_integral<InputIt>::value>::type insert(
        iterator pos, InputIt first, InputIt last)
    {
        size_type offset = std::distance(begin(), pos);
        size_type count  = std::distance(first, last);
        if (count == 0) return;
        size_type new_size = size() + count;
        size_type c            = capacity();

        // 予約メモリーが足りなければ拡張
        while (c < new_size)
        {
            if (c == 0)
                c = 1;
            else
                c *= 2;
        }
        reserve(c);
        // 追加で確保した要素のコンストラクタを呼ぶ
        for (; last_ != first_ + new_size; ++last_) construct(last_);

        iterator ite = end() - 1;
        // endから要素を挿入する先頭(pos + count - 1)までmemmoveする
        iterator end_pos = begin() + offset + count - 1;
        for (; ite > end_pos; --ite)
        {
            *ite = *(ite - count);
        }

        // 要素を挿入する
        for (size_type i = 0; i < count; i++, ++first)
        {
            *(first_ + offset + i) = *first;
        }
    }

    /**
     * @brief pos にある要素を削除する。
     * @param  削除するiterator
     * @return 最後に削除された要素に続くイテレータ。
     */
    iterator erase(iterator pos)
    {
        if (pos != end())
        {
            std::copy(pos + 1, end(), pos);
            // 最後の要素のデストラクタを呼ぶ。
            --last_;
            destroy(last_);
        }
        return pos;
    }

    /**
     * @brief [first, last)で示される範囲の要素が削除する。
     * @return 最後に削除された要素に続くイテレータ。
     * @detail
     * first==last の場合、削除せずfirstを返す。
     * 削除前の last==end() の場合、更新後の end() イテレータが返される。
     * [first,last) が空の場合、last が返される。
     */

    // a = {1,2,3,4,5};
    // a.erase(a.begin()+1, a.begin()+3);
    //      * * (ここを詰める)
    // a: 1 2 3 4 5 -> 1 4 5
    iterator erase(iterator first, iterator last)
    {
        difference_type start_idx = std::distance(begin(), first);
        difference_type del_range = std::distance(first, last);

        // firstの位置からlastの要素を埋めていく
        std::copy(last, end(), first);
//        while (last != end())
//        {
//            *first = *last;
//            ++first;
//            ++last;
//        }
        // 削除する要素の先頭を渡す -> 後ろから削除していく
        destroy_until(rbegin() + del_range);
        return (begin() + start_idx);
    }

    // vectorの要素を other と入れ替える
    void swap(vector& other)
    {
        std::swap(first_, other.first_);
        std::swap(last_, other.last_);
        std::swap(reserved_last_, other.reserved_last_);
        std::swap(alloc_, other.alloc_);
    }

    allocator_type get_allocator() const
    {
        return alloc_;
    }

    void pop_back()
    {
        pointer tmp = last_;
        --last_;
        alloc_.destroy(tmp);
    }

protected:
    pointer first_;
    pointer last_;
    pointer reserved_last_;
    allocator_type alloc_;

    // ヘルパー関数
    pointer allocate(size_type n)
    {
        return alloc_.allocate(n);
    }
    void deallocate()
    {
        alloc_.deallocate(first_, capacity());
    }
    void construct(pointer ptr)
    {
        alloc_.construct(ptr, 0);
    }
    void construct(pointer ptr, const_reference value)
    {
        alloc_.construct(ptr, value);
    }
    void destroy(pointer ptr)
    {
        alloc_.destroy(ptr);
    }

    /**
     * @brief
     * vectorが保持するrbegin()からリバースイテレーターrendまでの要素を破棄する。
     * @detail
     * リバースイテレーターを使うので、要素の末尾から先頭に向けて順番に破棄される。
     * 末尾から先頭に向けて要素を破棄する理由はC++では値の破棄は構築の逆順で行われるという原則があるから。
     * ポインターを取るために*riterでまずT &を得て、そこに&を適用することでT
     * *を得る。 破棄できたら有効な要素数を減らすために--lastする。
     */
    void destroy_until(reverse_iterator rend)
    {
        for (reverse_iterator riter = rbegin(); riter != rend; ++riter, --last_)
        {
            destroy(&*riter);
        }
    }
};

template <class Tp, class Alloc>
bool operator==(const vector<Tp, Alloc>& lhs, const vector<Tp, Alloc>& rhs)
{
    return lhs.size() == rhs.size() &&
           ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class Tp, class Alloc>
bool operator!=(const vector<Tp, Alloc>& lhs, const vector<Tp, Alloc>& rhs)
{
    return !(lhs == rhs);
}

template <class Tp, class Alloc>
bool operator<(const vector<Tp, Alloc>& lhs, const vector<Tp, Alloc>& rhs)
{
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                       rhs.end());
}

template <class Tp, class Alloc>
bool operator>(const vector<Tp, Alloc>& lhs, const vector<Tp, Alloc>& rhs)
{
    return rhs < lhs;
}

template <class Tp, class Alloc>
bool operator>=(const vector<Tp, Alloc>& lhs, const vector<Tp, Alloc>& rhs)
{
    return !(lhs < rhs);
}

template <class Tp, class Alloc>
bool operator<=(const vector<Tp, Alloc>& lhs, const vector<Tp, Alloc>& rhs)
{
    return !(rhs < lhs);
}

}    // namespace ft

#endif
