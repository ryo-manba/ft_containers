#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <iostream>

#include "iterator.hpp"
#include "pair.hpp"
#include "stack.hpp"
namespace ft
{

template <class T>
class tree_iterator;

template <class T>
class tree_const_iterator;

template <class Value>
struct tree_node
{
    typedef tree_node* node_pointer;

    Value* value_;
    node_pointer parent_;
    node_pointer left_;
    node_pointer right_;
    long height_;

private:
    node_pointer root_;
    node_pointer null_node_;

public:
    tree_node(Value* value = NULL, node_pointer parent = NULL,
              node_pointer left = NULL, node_pointer right = NULL)
        : value_(value), parent_(parent), left_(left), right_(right), height_(0)
    {
        // ダミーノードの作成
        //        null_node_ = new node_pointer;
        //        root_      = null_node_;
    }

    tree_node(const tree_node& other)
        : value_(other.value_),
          parent_(other.parent_),
          left_(other.left_),
          right_(other.right_),
          height_(other.height_)
    {
    }

    ~tree_node(void)
    {
    }

    // getter
    node_pointer get_root(void) const
    {
        return root_;
    }
    node_pointer get_null_node(void) const
    {
        return null_node_;
    }

    /**
     * utility
     */
    node_pointer get_max_node(node_pointer node) const
    {
        node_pointer maxi = node;

        while (maxi->right)
        {
            maxi = maxi->right;
        }
        return maxi;
    }

    node_pointer get_min_node(node_pointer node) const
    {
        node_pointer mini = node;

        while (mini->left)
        {
            mini = mini->left;
        }
        return mini;
    }

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
            return get_min_node(node->right);
        }

        // 値が大きくなるまで親ノードを辿っていく
        node_pointer cur = node->parent_;
        while (node == cur->right_)
        {
            node = cur;
            cur  = cur->parent_;
        }
        return cur;
    }

    node_pointer tree_decrement(node_pointer node)
    {
        // 左の子の最大ノード
        if (node->left_)
        {
            return get_max_node(node->left_);
        }
        // 値が小さくなるまで親ノードを辿っていく
        node_pointer cur = node->parent_;
        while (node == cur->left_)
        {
            node = cur;
            cur  = cur->parent_;
        }
        return cur;
    }
};

template <class T>
class tree_iterator
{
public:
    std::bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef std::ptrdiff_t difference_type;
    typedef value_type& reference;
    typedef value_type* pointer;

    typedef tree_node<value_type>* node_pointer;
    typedef tree_iterator<value_type> Self;

private:
    node_pointer node_;

public:
    tree_iterator() : node_(NULL)
    {
    }
    tree_iterator(node_pointer p) : node_(p)
    {
    }
    tree_iterator(const map_iterator& other) : node_(other.node_)
    {
    }
    ~tree_iterator()

        reference
        operator*() const
    {
        return node_->value_;
    }

    pointer operator->() const
    {
        return &node_->value_;
    }

    Self& operator++()
    {
        node_ = node_->tree_increment(node_);
        return *this;
    }

    Self operator++(int)
    {
        tree_iterator tmp(*this);
        ++(*this);
        return tmp;
    }

    Self& operator--()
    {
        node_ = node_->tree_decrement(node_);
        return *this;
    }

    Self operator--(int)
    {
        Self tmp(*this);
        --(*this);
        return tmp;
    }

    friend bool operator==(const tree_iterator& lhs,
                           const tree_iterator& rhs) const
    {
        return lhs.node_ == rhs.node_;
    }

    friend bool operator!=(const tree_iterator& lhs,
                           const tree_iterator& rhs) const
    {
        return !(lhs.node_ == rhs.node_);
    }
};

template <class T>
class tree_const_iterator
{
public:
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    std::bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef std::ptrdiff_t difference_type;
    typedef value_type& reference;
    typedef value_type* pointer;

    typedef tree_node<value_type>* node_pointer;
    typedef tree_const_iterator<value_type> Self;

private:
    typedef tree_iterator<value_type> tree_iterator;

    node_pointer node_;

public:
    tree_const_iterator() : node_(NULL)
    {
    }
    tree_const_iterator(node_pointer p) : node_(p)
    {
    }
    tree_const_iterator(const tree_const_iterator& other) : node_(other.node_)
    {
    }
    ~tree_const_iterator()
    {
    }

    reference operator*() const
    {
        return node_->value_;
    }
    pointer operator->() const
    {
        return &node_->value_;
    }

    Self& operator++()
    {
        node_ = node_->tree_increment(node_);
        return *this;
    }
    Self operator++(int)
    {
        tree_const_iterator tmp(*this);
        ++(*this);
        return tmp;
    }

    Self& operator--()
    {
        node_ = node_->tree_decrement(node_);
        return *this;
    }
    Self operator--(int)
    {
        tree_const_iterator tmp(*this);
        --(*this);
        return tmp;
    }

    friend bool operator==(const tree_const_iterator& lhs,
                           const tree_const_iterator& rhs)
    {
        return lhs.node_ == rhs.node_;
    }

    friend bool operator!=(const tree_const_iterator& lhs,
                           const tree_const_iterator& rhs)
    {
        return !(lhs.node_ == rhs.node_);
    }
};

template <class Key, class Val, class Compare,
          class Allocator = std::allocator<ft::pair<Key, Val> > >
class tree
{
public:
    typedef Key key_type;
    typedef Val value_type;
    typedef Compare key_compare;
    typedef Allocator allocator_type;
    typedef typename allocator_type::size_type size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef value_type& reference;
    typedef value_type* pointer;

    typedef tree_node<ft::pair<const key_type, value_type> > node_type;
    typedef node_type* node_pointer;

private:
    node_pointer root_;
    node_pointer null_node_;    // ダミーノード
    size_type size_;            // マップの要素数
    key_compare comp_;
    allocator_type alloc_;

public:
    explicit tree(const allocator_type& alloc = allocator_type(),
                  const key_compare& comp     = key_compare())
        : size_(0), comp_(comp), alloc_(alloc)
    {
        null_node_ = create_node();
        root_      = null_node_;
    }
    ~tree(void)
    {
        all_clear(root_);
        delete_node(null_node_);
    }
    /**
     * utility
     */
    // 偏りを計算する
    int calc_bias()
    {
        return left_->height_ - right_->height_;
    }
    // 木の高さとバイアスを更新する
    // 木の高さ = 1 + max(左の木の高さ, 右の木の高さ)
    // バイアス = 左の木の高さ - 右の木の高さ
    void update_height(void)
    {
        if (value_ == NULL)
        {
            height_ = 0;
        }
        else
        {
            // 常にnull_nodeがあるのでNULLチェックはいらない。
            size_type left_height  = left_->height_;
            size_type right_height = right_->height_;
            height_                = 1 + std::max(left_height, right_height);
        }
    }

    // replace(aノード,bノード)
    // aノードをルートとする部分木をbノードをルートとする部分木に置き換える
    void replace(node_pointer before, node_pointer after)
    {
        node_pointer parent_node = before->Parent;

        // beforeがrootだったらそのままafterをrootにする
        if (before == root_)
        {
            root_ = after;
        }
        else if (parent_node->left_ == before)
        {
            // beforeが親の左部分木だった場合
            parent_node->left_ = after;
        }
        else
        {
            // beforeが親の右部分木だった場合
            parent_node->right_ = after;
        }
        // afterの親を繋ぎ変える
        after->parent_ = parent_node;
    }

    /**
     * search
     */
    bool search(pointer data)
    {
        // keyを比較する関数かます？
        node_pointer result = search_node(root_, data);

        // dataが見つからない場合
        if (result == null_node_)
        {
            return false;
        }
        return true;
    }

    node_pointer search_node(node_pointer node, pointer data)
    {
        // nodeに要素が存在しない場合
        if (node == null_node_)
        {
            return node;
        }

        node_pointer tmp = node;

        while (tmp != null_node_)
        {
            if (tmp->data == data)
            {
                break;
            }

            // 要素が小さい場合は左を探索する
            // 比較関数かます?(key_comp)
            // pairのkey比較
            if (data < tmp->data)
            {
                tmp = tmp->left;
            }
            else
            {
                // tmp->data
                tmp = tmp->right;
            }
        }
        return tmp;
    }

private:
    node_pointer create_node(void)
    {
        node_pointer node;

        node = alloc_.allocate(1);
        alloc_.construct(node);
        node->left   = NULL;
        node->right  = NULL;
        node->parent = NULL;
        node->height = 0;
        return node;
    }

    void delete_node(node_pointer node)
    {
        alloc_.destroy(node);
        alloc_.deallocate(node, 1);
        size_ -= 1;
    }

    void all_clear(node_pointer node)
    {
        if (node == NULL)
            return ;
        all_clear(node->left);
        all_clear(node->right);
        delete_node(node);
    }
};
}    // namespace ft
#endif
