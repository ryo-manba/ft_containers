#ifndef MAP_HPP
#define MAP_HPP

#include <stdexcept>

#include "AVLtree.hpp"
#include "iterator.hpp"
#include "pair.hpp"
#include "utils.hpp"

template <class pointer>
struct tree_node;
namespace ft
{

// lessクラスは、左辺が右辺より小さいかの比較を行う関数オブジェクト
// std::less<int>()(2, 3) => true
template <class Key, class T, class Compare = std::less<Key>,
          class Allocator = std::allocator<ft::pair<const Key, T> > >
class map
{
public:
    // types:
    typedef Key key_type;
    typedef T mapped_type;
    typedef ft::pair<const key_type, mapped_type> value_type;
    typedef Compare key_compare;
    typedef Allocator allocator_type;

    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef typename allocator_type::size_type size_type;
    typedef typename allocator_type::difference_type difference_type;

    // value_type 型のオブジェクト（キーと値のペア）を
    // ペアの最初の構成要素を比較することによって比較する関数オブジェクト
    class value_compare
        : public std::binary_function<value_type, value_type, bool>
    {
    public:
        key_compare comp;

        // pairのkeyで比較する
        value_compare(key_compare c) : comp(c)
        {
        }
        bool operator()(const value_type& lhs, const value_type& rhs) const
        {
            return comp(lhs.first, rhs.first);
        }
    };

private:
    typedef ft::tree<key_type, mapped_type, key_compare, allocator_type> tree;
#ifdef DEBUG
public:
#endif
    tree tree_;

public:
    typedef typename tree::iterator iterator;
    typedef typename tree::const_iterator const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    /// Member functions

    // default constructor
    explicit map(const key_compare& comp     = key_compare(),
                 const allocator_type& alloc = allocator_type())
        : tree_(comp, alloc)
    {
    }

    // range constructor
    template <class InputIt>
    map(InputIt first, InputIt last, const key_compare& comp = key_compare(),
        const allocator_type& alloc = allocator_type())
        : tree_(comp, alloc)
    {
        tree_.insert_range_unique(first, last);
    }

    // copy constructor
    map(const map& other) : tree_(other.tree_)
    {
    }

    map& operator=(const map& other)
    {
        if (this == &other)
        {
            return *this;
        }
        tree_.clear();
        tree_.value_comp() = other.tree_.value_comp();
        insert(other.begin(), other.end());
        return *this;
    }

    // destructor
    ~map()
    {
    }

    /**
     * @brief コンテナに関連づけられたアロケータを返す
     */
    allocator_type get_allocator() const
    {
        return allocator_type(tree_.get_allocator());
    }

    /// Element access

    /**
     *  @brief keyに相当するkeyを持つ要素のマッピングされた値への参照を返す。
     *  @throw  std::out_of_range  要素が存在しない場合
     */
    mapped_type& at(const key_type& key)
    {
        iterator it = lower_bound(key);
        if (it == end() || key_comp()(key, (*it).first))
            throw std::out_of_range("map::at:  key not found");
        return (*it).second;
    }

    const mapped_type& at(const key_type& key) const
    {
        const_iterator it = lower_bound(key);
        if (it == end() || key_comp()(key, (*it).first))
            throw std::out_of_range("map::at:  key not found");
        return (*it).second;
    }

    /**
     *  @brief
     * keyと等価なキーにマッピングされた値への参照を返し、そのようなキーがまだ存在しない場合は挿入を実行する。
     * キーが存在しない場合は value_type(key, T())を挿入する。この関数は return
     * insert(std::make_pair(key, T())).first->second と等価である。
     * 挿入が行われた場合、マップされた値は値が初期化され（クラス型の場合はデフォルトで構築され、それ以外はゼロ初期化）、それへの参照が返される。
     * イテレータや参照は無効化されない。
     */
    mapped_type& operator[](const key_type& key)
    {
        iterator it = lower_bound(key);
        // __i->first is greater than or equivalent to key.
        ft::pair<iterator, bool> p;
        if (it == end() || key_comp()(key, (*it).first))
        {
            p = insert(value_type(key, mapped_type()));
            //            it = insert(it, value_type(key, mapped_type()));
            it = p.first;
        }
        return (*it).second;
    }

    /**
     * @brief
     */

    /// Iterators
    iterator begin()
    {
        return tree_.begin();
    }
    const_iterator begin() const
    {
        return tree_.begin();
    }
    iterator end()
    {
        return tree_.end();
    }
    const_iterator end() const
    {
        return tree_.end();
    }
    reverse_iterator rbegin()
    {
        return reverse_iterator(end());
    }
    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(end());
    }
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
     * @brief コンテナに要素が無いかどうかを調べる
     */
    bool empty() const
    {
        return tree_.empty();
    }

    /**
     * @brief コンテナ内の要素数を返す
     */
    size_type size() const
    {
        return tree_.size();
    }

    /**
     * @brief
     * システムまたはライブラリ実装の制限により、コンテナが保持できる最大の要素数を返す
     */
    size_type max_size() const
    {
        return tree_.max_size();
    }

    /// Modifiers

    /**
     * @brief コンテナからすべての要素を消去する
     * この呼び出しの後、size()はゼロを返す
     */
    void clear()
    {
        tree_.clear();
    }

    /**
     * @brief
     * コンテナに同等のキーを持つ要素がまだない場合、コンテナに要素を挿入する
     * @return
     * 挿入された要素（または挿入を阻止した要素）へのイテレータと、挿入が行われた
     * かどうかを示す bool のペア すでにkeyが存在した場合   : false
     * 　　　　　　存在しない場合 : true
     */
    ft::pair<iterator, bool> insert(const value_type& val)
    {
        return tree_.insert_unique(val);
    }

    /**
     * hintの前後に挿入できる場合はO(1)
     * それ以外は対数時間
     * @return 挿入された要素、または挿入を阻止した要素へのイテレータを返す
     */
    iterator insert(iterator hint, const value_type& val)
    {
        return tree_.insert_unique(hint, val);
    }

    /**
     * @brief firstからlastの範囲を挿入する
     */
    template <typename InputIt>
    void insert(InputIt first, InputIt last)
    {
        tree_.insert_range_unique(first, last);
    }

    /**
     * @brief posにある要素を削除する
     */
    void erase(iterator pos)
    {
        return tree_.erase(pos);
    }

    /**
     * @brief firstからlastの範囲を削除する
     */
    void erase(iterator first, iterator last)
    {
        return tree_.erase(first, last);
    }

    /**
     * @brief key と等価なキーを持つ要素を削除する（存在する場合）
     * @return 削除された要素の数を返す(1 or 0)
     */
    size_type erase(const key_type& key)
    {
        return tree_.erase_unique(key);
    }

    /**
     * @brief コンテナの内容をotherの内容と交換する
     */
    void swap(map& other)
    {
        tree_.swap(other.tree_);
    }

    /// Lookup

    /**
     * @brief key を持つ要素の数を返す
     * mapは重複を許さないので、1か0のどちらかである
     */
    size_type count(const key_type& key) const
    {
        return tree_.count(key);
    }

    /**
     * @brief keyと同等のkeyを持つ要素へのイテレータを返す。
     * そのような要素が見つからない場合、end()イテレータが返される。
     */
    iterator find(const key_type& key)
    {
        return tree_.find(key);
    }

    const_iterator find(const key_type& key) const
    {
        return tree_.find(key);
    }

    /**
     * @brief コンテナ内の与えられたキーを持つすべての要素を含む範囲を返す
     * 1つはキーより小さくない最初の要素を指すもの、もう1つはキーより大きい最初の要素を指すものである
     * 最初のイテレータは lower_bound() で、
     * 2 番目のイテレータは upper_bound()
     * で得ることができる。
     */
    ft::pair<iterator, iterator> equal_range(const key_type& key)
    {
        return tree_.equal_range(key);
    }

    ft::pair<const_iterator, const_iterator> equal_range(
        const key_type& key) const
    {
        return tree_.equal_range(key);
    }

    /**
     * @brief key以上の最初の要素を指すイテレータを返す
     * なかったらend()を返す
     */
    iterator lower_bound(const key_type& key)
    {
        return tree_.lower_bound(key);
    }
    const_iterator lower_bound(const key_type& key) const
    {
        return tree_.lower_bound(key);
    }

    /**
     * @brief key よりも大きい最初の要素を指すイテレータを返す
     * なかったらend()を返す
     */
    iterator upper_bound(const key_type& key)
    {
        return tree_.upper_bound(key);
    }
    const_iterator upper_bound(const key_type& key) const
    {
        return tree_.upper_bound(key);
    }

    /// Observers

    /**
     * @brief キーを比較する関数オブジェクトを返します
     */
    key_compare key_comp() const
    {
        return tree_.key_comp();
    }

    /**
     * @brief std::map::value_type 型のオブジェクト (キーと値のペア) を、
     * key_comp を用いてペアの第一成分を比較する関数オブジェクトを返します
     */
    value_compare value_comp() const
    {
        return value_compare(tree_.key_comp());
    }
};

/// Non-member functions

template <class Key, class T, class Compare, class Allocator>
bool operator==(const ft::map<Key, T, Compare, Allocator>& lhs,
                const ft::map<Key, T, Compare, Allocator>& rhs)
{
    return lhs.size() == rhs.size() &&
           ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class Key, class T, class Compare, class Allocator>
bool operator!=(const ft::map<Key, T, Compare, Allocator>& lhs,
                const ft::map<Key, T, Compare, Allocator>& rhs)
{
    return !(lhs == rhs);
}

template <class Key, class T, class Compare, class Allocator>
bool operator<(const ft::map<Key, T, Compare, Allocator>& lhs,
               const ft::map<Key, T, Compare, Allocator>& rhs)
{
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                       rhs.end());
}

template <class Key, class T, class Compare, class Allocator>
bool operator>(const ft::map<Key, T, Compare, Allocator>& lhs,
               const ft::map<Key, T, Compare, Allocator>& rhs)
{
    return rhs < lhs;
}

template <class Key, class T, class Compare, class Allocator>
bool operator>=(const ft::map<Key, T, Compare, Allocator>& lhs,
                const ft::map<Key, T, Compare, Allocator>& rhs)
{
    return !(lhs < rhs);
}

template <class Key, class T, class Compare, class Allocator>
bool operator<=(const ft::map<Key, T, Compare, Allocator>& lhs,
                const ft::map<Key, T, Compare, Allocator>& rhs)
{
    return !(rhs < lhs);
}
}    // namespace ft

namespace std
{
template <class Key, class T, class Compare, class Allocator>
void swap(ft::map<Key, T, Compare, Allocator>& lhs,
          ft::map<Key, T, Compare, Allocator>& rhs)
{
    lhs.swap(rhs);
}
}    // namespace std

#endif
