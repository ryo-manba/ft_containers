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

// Pair : ft::pair<const key, value>
template <class Pair>
struct tree_node
{
    typedef tree_node* node_pointer;

    Pair* data_;
    node_pointer parent_;
    node_pointer left_;
    node_pointer right_;
    long height_;

private:
    node_pointer root_;
    node_pointer last_;

public:
    tree_node(Value* data = NULL, node_pointer parent = NULL,
              node_pointer left = NULL, node_pointer right = NULL)
        : data_(data), parent_(parent), left_(left), right_(right), height_(0)
    {
        // ダミーノードの作成
        //        last_ = new node_pointer;
        //        root_      = last_;
    }

    tree_node(const tree_node& other)
        : data_(other.data_),
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
        return last_;
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
    // 木の高さを更新する
    // 木の高さ = 1 + max(左の木の高さ, 右の木の高さ)
    void update_height(void)
    {
        if (data_ == NULL)
        {
            height_ = 0;
        }
        else
        {
            long left_height  = left_ ? left_->height_ : 0;
            long right_height = right_ ? right->height_ : 0;
            height_                = 1 + std::max(left_height, right_height);
        }
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
        return node_->data_;
    }

    pointer operator->() const
    {
        return &node_->data_;
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
        return node_->data_;
    }
    pointer operator->() const
    {
        return &node_->data_;
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
    typedef Val mapped_type;
    typedef ft::pair<const key_type, mapped_type> value_type;
    typedef Compare key_compare;
    typedef Allocator allocator_type;
    typedef typename allocator_type::size_type size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef value_type& reference;
    typedef value_type* pointer;

    typedef tree_node<value_type> node_type;
    typedef node_type* node_pointer;

private:
    node_pointer root_;
    node_pointer last_;    // 終端ノード
    size_type size_;            // マップの要素数
    key_compare comp_;
    allocator_type alloc_;

public:
    explicit tree(const allocator_type& alloc = allocator_type(),
                  const key_compare& comp     = key_compare())
        : size_(0), comp_(comp), alloc_(alloc)
    {
        last_ = create_node();
        root_ = last_;
    }
    ~tree(void)
    {
        all_clear(root_);
        delete_node(last_);
    }

    tree& operator=(const tree& other)
    {
        if (this == &other) {
            return *this;
        }
        all_clear(root_);
        comp_ = other.comp_;
        alloc_ = other.alloc_;
        for (const_iterator it = other.begin(); it != other.end(); ++it)
        {
            insert(*it);
        }
        return *this;
    }

    iterator begin()
    {
        return iterator(root_->min_node(root_));
    }
    const_iterator begin()
    {
        return const_iterator(root_->min_node(root_));
    }
    iterator end()
    {
        return iterator(root_->max_node(root_));
    }
    iterator end()
    {
        return const_iterator(root_->max_node(root_));
    }

    size_type size() const
    {
        return size_;
    }

    size_type max_size() const
    {
        return std::min(alloc_.max_size(), static_cast<size_type>(std::numeric_limits<difference_type>::max()));
    }

    node_pointer* search(const value_type& data) const
    {
        return search_node(root_, data);
    }

    // 木の中からkeyがあるか捜索する
    iterator find(const key_type& key) const
    {
        node_pointer node = find_node(root_, key);

        if (node && !comp_(key, node->data_.first))
            return iterator(node);
        return end();
    }

    const_iterator find(const key_type& key) const
    {
        node_pointer node = find_node(root_, key)

        if (node && !comp_(key, node->data_.first))
            return const_iterator(node);
        return end();
    }

    node_type* insert(const value_type& data)
    {
        root_ = insert_node(root_, data_);
        last_->left = root_;
        if (root_)
        {
            root_->parent_ = last_;
        }
        return search_node(root_, data_);
    }

    void erase(value_type data)
    {
        root_ = erase_node(root_, data_);
        last_->left = root_;
        if (root_)
        {
            root_->parent_ = last_;
        }
    }

    void erase(iterator it)
    {
        erase(*it);
    }

    void erase(iterator first, iterator last)
    {
        for (; first != last; ++first)
            erase(*first);
    }

    int erase_unique(const key_type& key)
    {
        iterator it = find(key);
        if (it == end())
            return 0;
        erase(it);
        return 1;
    }

    void swap(tree_& other)
    {
        swap(root_, other.root_);
        swap(last_, other.last_);
        swap(size_, other.size_);
        swap(comp_, other.comp_);
        swap(alloc_, other.alloc_);
    }

    /**
     * utility
     */
    // 偏りを計算する
    int calc_bias()
    {
        return left_->height_ - right_->height_;
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
        if (result == last_)
        {
            return false;
        }
        return true;
    }

    node_pointer search_node(node_pointer node, value_type& data) const
    {
        if (node == NULL)
        {
            return NULL;
        }
        // ノードよりも小さい場合はleftを探す
        if (comp_(data.first, node_->data_.first))
            return search_node(node->left, data);
        // ノードよりも大きい場合はrightを探す
        else if (comp_(node->data_.first, data.first))
            return search_node(node->right, data);
        else
            return node; //　最終的に

        node_pointer tmp = node;

        while (tmp != last_)
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

    // 再帰的に全てのnodeを削除する
    void all_clear(node_pointer node)
    {
        if (node == NULL)
            return ;
        all_clear(node->left);
        all_clear(node->right);
        delete_node(node);
    }


    node_pointer insert_node(node_pointer node, const value_type& data)
    {
        if (root_ == last_)
        {
            node_pointer new_node = create_node();
            new_node->
        }
    }


    /**
     * @brief 右回転: 傾き “-1” よりも小さい(左部分木の方が高い場合)
     * @return 回転後のroot
     * [sample]
     *       A              B
     *     /   \           /  \
     *    B     Z   -->   X    A
     *   / \                  / \
     *  X   Y                Y   Z
     */
    node_pointer rotate_right(node_pointer a)
    {
        node_pointer parent = a->parent_;
        node_pointer b = a->left_;
        node_pointer y = b->right_;

        b->right_ = a;
        a->parent_ = b;
        b->parent_ = parent;
        a->left_ = y;
        if (y)
            y->parent_ = a;
        a->update_height();
        b->update_height();
        return b;
    }

    /**
     * @brief 左回転: 傾き “1” よりも大きい(右部分木の方が高い)
     * @return 回転後のroot
     * [sample]
     *    B                A
     *   /  \            /   \
     *  X    A    -->   B     Z
     *      / \        / \
     *     Y   Z      X   Y
     */
    node_pointer rotate_left(node_pointer b)
    {
        node_pointer parent = b->parent_;
        node_pointer a = b->right_;
        node_pointer y = a->left_;

        a->left_ = b;
        b->parent_ = a;
        a->parent_ = parent;
        b->right_ = y;
        if (y)
            y->parent_ = b;
        a->update_height();
        b->update_height();
        // 回転後のrootを返す
        return a;
    }
};
}    // namespace ft
#endif
