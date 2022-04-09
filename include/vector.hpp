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

    /// Member functions

    // default constructor
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

    // fill constructor
    explicit vector(size_type count, const T& value = T(),
                    const Allocator& alloc_ = Allocator())
        : first_(NULL), last_(NULL), reserved_last_(NULL), alloc_(alloc_)
    {
        resize(count, value);
    }

    // TODO: InputIteratorとそれ以外で処理を分ける
    // ForwardIteratorで処理を分ける
    // range constructor
    template <typename InputIt>
    vector(InputIt first, InputIt last, const Allocator& alloc_ = Allocator(),
           typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                  InputIt>::type* = NULL)
        : first_(NULL), last_(NULL), reserved_last_(NULL), alloc_(alloc_)
    {
        // InputItは使えない
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

    /**
     * @brief コンテナの再代入
     * (1) : 範囲を代入
     * (2) : count個の値tを代入
     * capacity が count より大きい場合、要素をそのまま埋める
     * capacity が count より小さい場合、新たにアロケートし直す
     */
    void assign(size_type count, const value_type& val)
    {
        size_type cap = capacity();

        if (count > cap)
        {
            clear();
            while (cap < count)
            {
                cap *= 2;
            }
            reserve(cap);
        }
        pointer t = first_;
        for (size_type i = 0; i < count; ++i)
        {
            *t = val;
            ++t;
        }
        last_ = t;
    }

    template <class InputIt>
    void assign(InputIt first, InputIt last)
    {
        clear();
        insert(begin(), first, last);
    }

    /**
     * @brief コンテナに関連付けられたアロケータを返す
     */
    allocator_type get_allocator() const
    {
        return alloc_;
    }

    /// Element access

    /**
     * @brief 指定された位置 pos にある要素への参照を、境界チェック付きで返す
     * pos がコンテナの範囲内にない場合、std::out_of_range
     * 型の例外がスローされる
     */
    reference at(size_type pos)
    {
        if (pos >= size()) throw std::out_of_range("vector");
        return first_[pos];
    }
    const_reference at(size_type pos) const
    {
        if (pos >= size()) throw std::out_of_range("vector");
        return first_[pos];
    }

    /**
     * @brief 要求された要素への参照を返す
     * 存在しない要素へのアクセスは未定義の動作になる
     */
    reference operator[](size_type pos)
    {
        return first_[pos];
    }
    const_reference operator[](size_type pos) const
    {
        return first_[pos];
    }

    /**
     * @brief コンテナの最初の要素への参照を返す
     * 空のコンテナで呼び出した場合は未定義の動作になる
     */
    reference front()
    {
        return *first_;
    }
    const_reference front() const
    {
        return *first_;
    }

    /**
     * @brief コンテナ内の最後の要素への参照を返す
     * 空のコンテナで呼び出した場合は未定義の動作になる
     */
    reference back()
    {
        return *(last_ - 1);
    }
    const_reference back() const
    {
        return *(last_ - 1);
    }

    /**
     * @brief 配列の先頭のポインタを返す
     * size() が 0 の場合、data()
     * はヌルポインタを返す場合と返さない場合がある(実装定義なはず)
     */
    pointer data()
    {
        return first_;
    }
    const_pointer data() const
    {
        return first_;
    }

    /// Iterators

    /**
     * @brief 最初の要素へのイテレータを返す
     * 空の場合に返されるイテレータは end() と等しくなる
     */
    iterator begin()
    {
        return first_;
    }
    const_iterator begin() const
    {
        return first_;
    }

    /**
     * @brief 最後の要素に続く要素へのイテレータを返す
     * この要素はプレースホルダとして動作し、これにアクセスしようとすると未定義の動作になる
     */
    iterator end()
    {
        return last_;
    }
    const_iterator end() const
    {
        return last_;
    }

    /**
     * @brief
     * 反転したベクトルの最初の要素への反転イテレータを返す(非反転ベクトルの最後の要素に相当する)
     * ベクトルが空の場合、返されるイテレータは rend() と等しくなる
     */
    reverse_iterator rbegin()
    {
        return reverse_iterator(end());
    }
    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(end());
    }

    /**
     * @brief
     * 反転したベクトルの最後の要素に続く要素への反転イテレータを返す(非反転ベクトルの最初の要素の前にある要素に相当する)
     * この要素はプレースホルダとして動作し、これにアクセスしようとすると未定義の動作となる
     */
    reverse_iterator rend()
    {
        return reverse_iterator(begin());
    }
    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(begin());
    }

    /// Capacity

    /**
     * @brief コンテナに要素がないかどうかを調べる
     */
    bool empty() const
    {
        return begin() == end();
    }

    /**
     * @brief コンテナ内の要素数を返す
     */
    size_type size() const
    {
        return std::distance(begin(), end());
    }

    /**
     * @brief
     * システムまたはライブラリ実装の制限により、コンテナが保持できる最大の要素数を返す
     * コンテナのサイズの理論的な制限を反映しており、利用可能な RAM の量によって
     * max_size() よりも小さな値に制限されることがある
     */
    size_type max_size(void) const
    {
        const size_t diffmax =
            std::numeric_limits<size_type>::max() / sizeof(value_type);
        const size_t allocmax = std::numeric_limits<difference_type>::max();

        return std::min<size_type>(diffmax, allocmax);
    }

    /**
     * @brief ベクターの容量をnew_cap以上の値まで増加させる
     * new_cap が現在の capacity()
     * より大きい場合、新しいストレージが割り当てられ、そうでない場合は何もしない
     * 再確保された場合にはシーケンス中の要素を指す全ての参照、ポインタ、イテレータが無効になる
     */
    void reserve(size_type new_cap)
    {
        // TODO: 例外チェック
        if (new_cap > max_size())
        {
            //            throw length_error("vector::reserve");
            throw std::out_of_range("vector::reserve");
        }
        // すでに指定された要素数以上に予約されているなら何もしない
        if (new_cap <= capacity())
        {
            return;
        }

        // 動的メモリー確保をする
        pointer ptr = allocate(new_cap);

        // 古いストレージの情報を保存
        pointer old_first      = first_;
        pointer old_last       = last_;
        size_type old_capacity = capacity();

        // 新しいストレージに差し替え
        first_         = ptr;
        last_          = first_;
        reserved_last_ = first_ + new_cap;

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
     * @brief コンテナが現在割り当てられている要素数を返す
     */
    size_type capacity() const
    {
        return reserved_last_ - first_;
    }

    /// Modifiers

    /**
     * @brief 全ての要素を削除する
     * この呼び出しの後、size() はゼロを返す
     */
    void clear()
    {
        destroy_until(rend());
    }

    /**
     * @brief pos の前に value を挿入する
     * @return 挿入された値を指すイテレータ
     */
    iterator insert(const_iterator pos, const value_type& value)
    {
        difference_type offset = std::distance(begin(), pos);
        insert(pos, 1, value);
        return begin() + offset;
    }

    /**
     * @brief pos の前に value を count の数挿入する
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
     * @brief posの前に範囲[first, last]の要素を挿入する
     * first と last が *this へのイテレータの場合、未定義の動作になる
     * enable_if で整数型かどうかを判定している
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
        size_type c        = capacity();

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
     * @brief pos にある要素を削除する
     * @return 最後に削除された要素に続くイテレータ
     */
    iterator erase(iterator pos)
    {
        if (pos != end())
        {
            std::copy(pos + 1, end(), pos);
            // 最後の要素のデストラクタを呼ぶ
            --last_;
            destroy(last_);
        }
        return pos;
    }

    /**
     * @brief [first, last)で示される範囲の要素が削除する
     * @return 最後に削除された要素に続くイテレータ
     *         first==last の場合、削除せずに first が返される
     *         削除前の last==end() の場合、更新後の end() イテレータが返される
     *         [first,last) が空の場合、last が返される
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
        // 後ろから削除していく
        destroy_until(rbegin() + del_range);
        return (begin() + start_idx);
    }

    /**
     * @brief　value を末尾に追加する。
     */
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

    /**
     * @brief 末尾要素を削除する
     */
    void pop_back()
    {
        pointer tmp = last_;
        --last_;
        alloc_.destroy(tmp);
    }

    /**
     * @brief コンテナのサイズを変更し、count 個の要素を含むようにする
     * - 現在のサイズが count より大きい場合、count 要素まで縮小される
     * - 現在のサイズが count より小さい場合、値は変更されずに後ろに value
     * が追加される
     */
    void resize(size_type count, value_type value = value_type())
    {
        if (count < size())
        {
            erase(begin() + count, end());
        }
        else if (count > size())
        {
            insert(end(), count - size(), value);
        }
    }

    /**
     * @brief 他のvectorオブジェクトとデータを入れ替える
     */
    void swap(vector& other)
    {
        std::swap(first_, other.first_);
        std::swap(last_, other.last_);
        std::swap(reserved_last_, other.reserved_last_);
        std::swap(alloc_, other.alloc_);
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
     * vectorが保持するrbegin()からリバースイテレーターrendまでの要素を破棄する
     * @detail
     * リバースイテレーターを使うので、要素の末尾から先頭に向けて順番に破棄される
     * 末尾から先頭に向けて要素を破棄する理由はC++では値の破棄は構築の逆順で行われるという原則があるから
     * ポインターを取るために*riterでまずT &を得て、そこに&を適用することでT
     * *を得る 破棄できたら有効な要素数を減らすために--lastする
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

template <class Tp, class Alloc>
void swap(ft::vector<Tp, Alloc>& x, ft::vector<Tp, Alloc>& y)
{
    x.swap(y);
}

}    // namespace ft

#endif
