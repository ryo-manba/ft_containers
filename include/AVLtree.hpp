#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include "iterator.hpp"

namespace ft
{

template <class T, class NodePtr, class DiffType>
class tree_iterator;

template <class T, class NodePtr, class DiffType>
class tree_const_iterator;

template <typename T, typename Compare, typename Allocator>
class AVLTree
{
public:
    typedef T value_type;
    typedef T& reference;
    typedef const T& const reference;
    typedef T* pointer;
    typedef const T* const pointer;
    typedef size_t size_type;

private:
    struct tree_node
    {
        pointer value_;
        tree_node* parent_;
        tree_node* left_;
        tree_node* right_;
        size_type height_;
        int bias;

        private:
            tree_node* root_;
            tree_node* null_node_;

        public:
        tree_node(pointer value = NULL, tree_node* parent = NULL,
                  tree_node* left = NULL, tree_node* right = NULL)
            : value_(value), parent_(parent), left_(left), right_(right)
        {
            // ダミーノードの作成
            null_node = new tree_node*;
            root = null_node;
            update_height();
        }

        tree_node(const tree_node& other)
        {
            *this = other;
        }

        virtual ~tree_node(void)
        {
            ft::stack<tree_node*> sta;

            if (root_ == null_node_;)
            {
                delete null_node_;
                return ;
            }

            if (root_->left != null_node_)
            {
                sta.push(root->left_);
            }
            if (root_->right != null_node_)
            {
                sta.push(root->right);
            }

            // BFSのようなイメージで木を辿りながらdeleteしていく
            while (!sta.empty())
            {
                tree_node* front = sta.top();
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

        tree_node& operator=(const tree_node& rhs)
        {
            if (this == &rhs)
            {
                return *this;
            }
            value_  = rhs.value_;
            left_   = rhs.left_;
            right_  = rhs.right_;
            height_ = rhs.height_;
            root_ = rhs.get_root();
            null_node_ = rhs.get_null_node();
            return *this;
        }

        // getter
        tree_node* get_root(void) const { return root_; }
        tree_node* get_null_node(void) const { return null_node_; }

        // 木の高さを更新する
        void update_height(void)
        {
            if (value_ == NULL)
            {
                height_ = 0;
            }
            else
            {
                size_type left_height = 0;
                size_type right_height = 0;

                if (left_) left_height = left_->height_;
                if (right_) right_height = right_->height_;
                height_ = 1 + std::max(left_height, right_height);
            }
        }
    };

    template <class T, class NodePtr, class DiffType>
    class tree_iterator
    {
        typedef tree_node_types<_NodePtr> NodeTypes;
        typedef NodePtr node_pointer;
        typedef typename NodeTypes::node_base_pointer node_base_pointer;
        typedef typename NodeTypes::end_node_pointer end_node_pointer;
        typedef typename NodeTypes::iter_pointer iter_pointer;
        typedef pointer_traits<node_pointer> pointer_traits;

        iter_pointer ptr_;

    public:
        typedef bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef DiffType difference_type;
        typedef value_type& reference;
        typedef NodeTypes::node_value_type_pointer pointer;

    }
};
}    // namespace ft
#endif
