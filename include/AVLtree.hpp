#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include "iterator.hpp"
#include "stack.hpp"
namespace ft
{

template <class Val, class NodePtr, class DiffType>
class tree_iterator;

template <class Val, class NodePtr, class DiffType>
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
        null_node_ = new node_pointer;
        root_      = null_node_;
    }

    tree_node(const tree_node& other)
        : value_(other.value_),
          parent_(other.parent_),
          left_(other.left_),
          right_(other.right_),
          height_(other.height_)
    {
    }

    virtual ~tree_node(void)
    {
        ft::stack<node_pointer> sta;

        if (root_ == null_node_)
        {
            delete null_node_;
            return;
        }

        if (root_->left != null_node_)
        {
            sta.push(root_->left_);
        }
        if (root_->right != null_node_)
        {
            sta.push(root_->right);
        }

        // BFSのようなイメージで木を辿りながらdeleteしていく
        while (!sta.empty())
        {
            node_pointer front = sta.top();
            sta.pop();

            if (front->left != null_node_)
            {
                sta.push(front->left);
            }
            if (front->right != null_node_)
            {
                sta.push(front->right);
            }
            delete front;
        }
        delete null_node_;
        delete root_;
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
            cur = cur->parent_;
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
            cur = cur->parent_;
        }
        return cur;
    }
};

template <class T>
class tree_iterator
{
public:
    std::bidirectional_iterator_tag iterator_category;
    typedef T   value_type;
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
    tree_iterator(node_pointer p): node_(p) {}
    tree_iterator(const map_iterator& other) : node_(other.node_) {}
    ~tree_iterator()

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

    friend bool operator==(const tree_iterator& lhs, const tree_iterator& rhs) const
    {
        return lhs.node_ == rhs.node_;
    }

    friend bool operator!=(const tree_iterator& lhs, const tree_iterator& rhs) const
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
    typedef T   value_type;
    typedef std::ptrdiff_t difference_type;
    typedef value_type& reference;
    typedef value_type* pointer;

    typedef tree_node<value_type>* node_pointer;
    typedef tree_const_iterator<value_type> Self;

private:
    typedef tree_iterator<value_type> tree_iterator;

    node_pointer node_;

public:
    tree_const_iterator() : node_(NULL) {}
    tree_const_iterator(node_pointer p) : node_(p) {}
    tree_const_iterator(const tree_const_iterator& other) : node_(other.node_) {}
    ~tree_const_iterator() {}

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

    friend bool operator==(const tree_const_iterator& lhs, const tree_const_iterator& rhs)
    {
        return lhs.node_ == rhs.node_;
    }

    friend bool operator!=(const tree_const_iterator& lhs, const tree_const_iterator& rhs)
    {
        return !(lhs.node_ == rhs.node_);
    }
};

template <typename Key, typename Val, typename Compare,
          typename Allocator = std::allocator<Val> >
class avl_tree
{
public:
    typedef Key key_type;
    typedef Val value_type;
    typedef Compare value_compare;
    typedef Allocator allocator_type;

    typedef Val& reference;
    typedef Val* pointer;
    typedef size_t size_type;
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
                height_ = 1 + std::max(left_height, right_height);
                bias_   = calc_bias();
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
    };
};
}    // namespace ft
#endif
