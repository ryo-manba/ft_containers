#ifndef MAP_HPP
#define MAP_HPP

#include "pair.hpp"
#include "iterator.hpp"
#include "utils.hpp"
#include "AVLtree.hpp"

template<class pointer>
struct tree_node;
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
    typedef map_iterator   iterator;
    typedef const_map_iterator   const_iterator;
    typedef ft::reverse_iterator<iterator>           reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;

    // value_type 型のオブジェクト（キーと値のペア）を
    // ペアの最初の構成要素を比較することによって比較する関数オブジェクト
    class value_compare
        : public std::binary_function<value_type, value_type, bool>
    {
    public:
        key_compare comp;

        value_compare(key_compare c) : comp(c) {}
        bool operator()(const value_type& lhs, const value_type& rhs) const
        {
            return comp(lhs.first, rhs.first);
        }
    };

private:

    struct tree_node
    {
        ft::pair<const Key, T> value_;
        tree_node*   parent_;
        tree_node*   right_;
        tree_node*   left_;
    };

    // TODO: treeを正しく動かせるように修正する
//    typedef avl_tree<key_type, mapped_type, key_compare, allocator_type> tree;

    tree_node*  root_;
    tree_node*  last_;
    key_compare comp_;
    allocator_type alloc_;


public:

explicit map( const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type())
    : comp_(comp),
      alloc_(alloc) {}

template<class InputIt>
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


template <class ValueType, class KeyType, class NodePointer,
          class DifferenceType, class ValueComp, class KeyComp>
class map_iterator
{
public:
    typedef ValueType value_type;
    typedef KeyType key_type;
    typedef DifferenceType difference_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef map_iterator<ValueType> Self;

private:
    typedef NodePointer node_pointer;
    typedef ValueComp value_compare;
    typedef KeyComp key_compare;
    typedef stack<node_pointer> stack_type;

public:
    node_pointer node_;

private:
    key_compare key_comp_;
    value_compare value_comp_;

private:

/*
    4
   /  \
  2    5
 / \    \
1   3    6

- 3 のnextは 4, 4 のprevは 3
- 5 のnextは 6, 6 のprevは 5
*/
    node_pointer tree_increment(node_pointer node)
    {
        // 右の子の最小ノード
        if (node->right_)
        {
            node = node->right_;
            while (node->left_)
            {
                node = node->left_;
            }
        }
        else
        {
            // 値が大きくなるまで親ノードを辿っていく
            tree_node* tmp = node->parent_;
            while (node == tmp->right_)
            {
                node = tmp;
                tmp = tmp->parent_;
            }
            if (node->right != tmp)
                node = tmp;
        }
        return node;
    }

    node_pointer tree_decrement(node_pointer node)
    {
        // 左の子の最大ノード
        if (node->left_)
        {
            node = node->left_;
            while (node->right_)
            {
                node = node->right_;
            }
        }
        else
        {
            // 値が小さくなるまで親ノードを辿っていく
            tree_node* tmp = node->parent_;
            while (node == tmp->left_)
            {
                node = tmp;
                tmp = tmp->parent_;
            }
            node = tmp;
        }
        return node;
    }

public:

    map_iterator() : node_(NULL) {}
    map_iterator(node_pointer p) : node_(p) {}
    map_iterator(const map_iterator& other) : node_(other.node_) {}

    reference operator*() const
    {
        return node_->value_;
    }

    pointer operator->() const
    {
        return &node->value_;
    }

    Self& operator++()
    {
        node_ = tree_increment(node_);
        return *this;
    }

    Self operator++(int)
    {
        Self tmp = *this;
        node_ = tree_increment(node_);
        return tmp;
    }

    Self& operator--()
    {
        node_ = tree_decrement(node_);
        return *this;
    }

    Self operator--()
    {
        Self tmp = *this;
        node_ = tree_decrement(node_);
        return tmp;
    }

};
}
#endif
