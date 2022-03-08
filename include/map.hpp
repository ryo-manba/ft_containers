#ifndef MAP_HPP
#define MAP_HPP

#include "pair.hpp"
#include "iterator.hpp"

namespace ft
{

template <class Key,
          class T,
          class Compare = std::less<Key>,
          class Allocator = std::allocator<ft::pair<const Key, T> > >
class map
{
public:
    // types:
    typedef Key                                      key_type;
    typedef T                                        mapped_type;
    typedef ft::pair<const key_type, mapped_type>    value_type;
    typedef Compare                                  key_compare;
    typedef Allocator                                allocator_type;

    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;

// TODO: mapのイテレーター作る
//    typedef implementation-defined                   iterator;
//    typedef implementation-defined                   const_iterator;
    typedef ft::reverse_iterator<iterator>           reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;

    // value_type 型のオブジェクト（キーと値のペア）を
    // ペアの最初の構成要素を比較することによって比較する関数オブジェクト
    class value_compare
        : public binary_function<value_type, value_type, bool>
    {
    public:
        key_compare comp;

        value_compare(key_compare c) : comp(c) {};
        bool operator()(const value_type& lhs, const value_type& rhs) const
        {
            return comp(lhs.first, rhs.first);
        }
    };

private:
    // TODO: treeを正しく動かせるように修正する
    typedef tree_node<value_type> tree;
    key_comp comp_;
    allocator_type alloc_;
    tree tree_;


explicit map( const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type())
    : comp_(comp),
      alloc_(alloc)

template< class InputIt >
map(InputIt first, 
    InputIt last,
    const key_compare& comp = key_compare(),
    const allocator_type& alloc = allocator_type())
    : comp_(comp),
      alloc_(alloc)
    {
        while (first != last)
        {
            // tree_.insert(first->first, first->second);
            ++first;
        }
    }

    map( const map& other ) :
    tree_(other.tree_),
    comp_(other.comp_),
    alloc_(other.alloc_)
    {
    }

    map& operator=(const map& other)
    {
        if (this == &other) {
            return *this;
        }
        tree_ = other.tree_;
        comp_ = other.comp_;
        alloc_ = other.alloc_;
        return *this;
    }

    // TODO: メンバーファンクション追加する

};

template <class Key, class T, class Compare, class Allocator>
bool operator==(const ft::map<Key, T, Compare, Allocator>& lhs,
                const ft::map<Key, T, Compare, Allocator>& rhs)
{
    return lhs.size() == rhs.size() && \
           ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class Key, class T, class Compare, class Allocator>
bool operator!=(const ft::map<Key, T, Compare, Allocator>& lhs,
                const ft::map<Key, T, Compare, Allocator>& rhs)
{
    return !(lhs == rhs);
}

template <class Key, class T, class Compare, class Allocator>
bool operator< (const ft::map<Key, T, Compare, Allocator>& lhs,
                const ft::map<Key, T, Compare, Allocator>& rhs)
{
    return ft::lexicographical_compare(
        lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class Key, class T, class Compare, class Allocator>
bool operator> (const ft::map<Key, T, Compare, Allocator>& lhs,
                const ft::map<Key, T, Compare, Allocator>& rhs)
{
    return rhs > lhs;
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

template <class Key, class T, class Compare, class Allocator>
void swap(const ft::map<Key, T, Compare, Allocator>& lhs,
          const ft::map<Key, T, Compare, Allocator>& rhs)
{
    lhs.swap(rhs);
}

}
#endif
