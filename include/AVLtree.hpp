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
    tree_node(Pair* data = NULL, node_pointer parent = NULL,
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
            long right_height = right_ ? right_->height_ : 0;
            height_           = 1 + std::max(left_height, right_height);
        }
    }

    // 木の偏りを返す
    long calc_balance_factor(void)
    {
        long left_height  = left_ ? left_->height_ : 0;
        long right_height = right_ ? right_->height_ : 0;

        return left_height - right_height;
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
    tree_iterator(const tree_iterator& other) : node_(other.node_)
    {
    }

    ~tree_iterator(void)
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

    friend bool operator==(const tree_iterator& lhs, const tree_iterator& rhs)
    {
        return lhs.node_ == rhs.node_;
    }

    friend bool operator!=(const tree_iterator& lhs, const tree_iterator& rhs)
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

template <class Key, class Val, class Compare = std::less<Key>,
          class Allocator = std::allocator<ft::pair<const Key, Val> > >
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

    typedef tree_iterator<value_type> iterator;
    typedef tree_const_iterator<value_type> const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    typedef tree_node<value_type> node_type;
    typedef node_type* node_pointer;

private:
    typedef typename allocator_type::template rebind<node_type>::other
        node_allocator;

    node_pointer root_;
    node_pointer last_;    // 終端ノード
    size_type size_;       // マップの要素数
    key_compare comp_;
    node_allocator alloc_;

public:
    explicit tree(const key_compare& comp     = key_compare(),
                  const allocator_type& alloc = allocator_type())
        : size_(0), comp_(comp), alloc_(node_allocator(alloc))
    {
        last_ = alloc_.allocate(1);
        alloc_.construct(last_);
        last_->left_   = NULL;
        last_->right_  = NULL;
        last_->parent_ = NULL;
        last_->height_ = 0;
        //        root_          = last_;
        root_ = NULL;
    }
    ~tree(void)
    {
        all_clear(root_);
        //        root_ = NULL;
        //        if (last_)
        //            delete_node(last_);
    }

    tree& operator=(const tree& other)
    {
        if (this == &other)
        {
            return *this;
        }
        all_clear(root_);
        comp_  = other.comp_;
        alloc_ = other.alloc_;
        for (const_iterator it = other.begin(); it != other.end(); ++it)
        {
            insert_unique(*it);
        }
        return *this;
    }

    allocator_type get_allocator() const
    {
        return alloc_;
    }

    // iterators
    iterator begin()
    {
        return iterator(root_->min_node(root_));
    }
    const_iterator begin() const
    {
        return const_iterator(root_->min_node(root_));
    }
    iterator end()
    {
        return iterator(root_->max_node(root_));
    }
    const_iterator end() const
    {
        return const_iterator(root_->max_node(root_));
    }

    // Capacity
    bool empty() const
    {
        return size_ == 0;
    }
    size_type size() const
    {
        return size_;
    }

    size_type max_size() const
    {
        return std::min(alloc_.max_size(),
                        static_cast<size_type>(
                            std::numeric_limits<difference_type>::max()));
    }

    // TODO: stubの実装
    // Modifiers
    void clear()
    {
        // stub
    }

    node_pointer insert_unique(const value_type& data)
    {
        root_ = insert_node(root_, data);

        if (root_)
        {
            root_->parent_ = last_;
        }
        return search_node(root_, data);
    }

    template <typename InputIt>
    void insert_range_unique(InputIt first, InputIt last)
    {
        // stub
    }

    void erase(value_type data)
    {
        root_       = erase_node(root_, data);
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
        for (; first != last; ++first) erase(*first);
    }

    int erase_unique(const key_type& key)
    {
        iterator it = find(key);
        if (it == end()) return 0;
        erase(it);
        return 1;
    }

    void swap(tree& other)
    {
        swap(root_, other.root_);
        swap(last_, other.last_);
        swap(size_, other.size_);
        swap(comp_, other.comp_);
        swap(alloc_, other.alloc_);
    }

    // Lookup
    size_type count(const key_type& key) const
    {
        // stub
        return 1;
    }

    // 木の中からkeyがあるか捜索する
    iterator find(const key_type& key)
    {
        node_pointer node = find_node(root_, key);

        if (node && !comp_(key, node->data_->first)) return iterator(node);
        return end();
    }

    const_iterator find(const key_type& key) const
    {
        node_pointer node = find_node(root_, key);

        if (node && !comp_(key, node->data_->first))
            return const_iterator(node);
        return end();
    }

    // TODO:stub
    ft::pair<iterator, iterator> equal_range(const key_type& key)
    {
        iterator it1, it2;
        return ft::pair<it1, it2>;
    }

    // TODO: stub
    ft::pair<const_iterator, const_iterator> equal_range(
        const key_type& key) const
    {
        const_iterator it1, it2;
        return ft::pair<it1, it2>;
    }

    // TODO: stub
    iterator lower_bound(const key_type& key)
    {
        return iterator;
    }

    // TODO: stub
    const_iterator lower_bound(const key_type& key) const
    {
        return const_iterator;
    }

    // TODO: stub
    iterator upper_bound(const key_type& key)
    {
        return iterator;
    }

    // TODO: stub
    const_iterator upper_bound(const key_type& key) const
    {
        return const_iterator;
    }

    // Observers
    key_compare key_comp() const
    {
        return comp_;
    }
    key_compare value_comp() const
    {
        return comp_;
    }

private:
    node_pointer create_node(const value_type& data)
    {
        node_pointer node;

        node = alloc_.allocate(1);
        alloc_.construct(node, data);
        node->left_   = NULL;
        node->right_  = NULL;
        node->parent_ = NULL;
        node->height_ = 1;
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
        if (node == NULL) return;
        all_clear(node->left_);
        all_clear(node->right_);
        delete_node(node);
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
        node_pointer b      = a->left_;
        node_pointer y      = b->right_;

        b->right_  = a;
        a->parent_ = b;
        b->parent_ = parent;
        a->left_   = y;
        if (y) y->parent_ = a;
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
        node_pointer a      = b->right_;
        node_pointer y      = a->left_;

        a->left_   = b;
        b->parent_ = a;
        a->parent_ = parent;
        b->right_  = y;
        if (y) y->parent_ = b;
        a->update_height();
        b->update_height();
        // 回転後のrootを返す
        return a;
    }

    /**
     * @brief 2重回転（右->左）
     * @return 回転後のroot
     * 傾き “1” より大きい（右部分木の方が高い）
     * 右の子ノードの傾き “-1” 以下（左部分木の方が高い）
     * [sample]
     *      A               B
     *    /  \            /   \
     *   W    C          A     C
     *       / \        / \   / \
     *      B   Z  --> W   X Y   Z
     *     / \
     *    X   Y
     */
    node_pointer rotate_rl(node_pointer a)
    {
        rotate_right(a->right_);
        return rotate_left(a);
    }

    /**
     * @brief 2重回転（左->右）
     * @return 回転後のroot
     * 傾き “-1” より小さい（左部分木の方が高い）
     * 左の子ノードの傾き “1” 以上（右部分木の方が高い）
     *[sample]
     *       A             B
     *      /  \         /   \
     *     C    Z       C     A
     *    / \          / \   / \
     *   W   B    --> W   X Y   Z
     *      / \
     *     X   Y
     */
    node_pointer rotate_lr(node_pointer a)
    {
        rotate_left(a->left_);
        return rotate_right(a);
    }

    // 偏りに応じてバランスを取る
    void balancing(node_pointer node)
    {
        node->update_height();
        long balance = node->calc_balance_factor();

        if (balance > 1)
        {
            if (node->left_->calc_balance_factor() < 0)
                rotate_lr(node);
            else
                rotate_right(node);
        }
        if (balance < -1)
        {
            if (node->right_->calc_balance_factor() > 0)
                rotate_rl(node);
            else
                rotate_left(node);
        }
    }

    // 再帰的に全てのnodeのバランスを取る
    void rebalancing(node_pointer node)
    {
        if (node->left_) rebalancing(node->left_);
        if (node->right_) rebalancing(node->right_);
        balancing(node);
    }
    /**
     * @brief 大小比較して適切な位置にnodeを追加する
     * 偏りに応じて回転させる
     * @param node (NULLになるまでたどっていく)
     * @param data (追加する要素)
     * @return node_pointer
     */
    node_pointer insert_node(node_pointer node, const value_type& data)
    {
        // 追加できるところだったら追加する
        if (node == NULL)
        {
            size_ += 1;
            return create_node(data);
        }
        if (comp_(
                data.first,
                node->data_->first))    // 現nodeよりも挿入したい値が小さい場合
        {
            // 左にたどっていく
            node->left_          = insert_node(node->left_, data);
            node->left_->parent_ = node;
        }
        else if (comp_(node->data_->first,
                       data.first))    // 現nodeよりも挿入したい値が大きい場合
        {
            // 右にたどっていく
            node->right_          = insert_node(node->right_, data);
            node->right_->parent_ = node;
        }
        else
        {
            // すでにkeyが存在した場合
            node->data_->second = data.second;
            return node;
        }

        // 木の偏りをもとにバランスを取る
        rebalancing(node);
        return node;
    }

    node_pointer erase_node(node_pointer node, value_type data)
    {
        if (node == NULL)
        {
            return node;
        }
        if (comp_(data.first, node->data_->first))
        {
            node->left_ = erase_node(node->left_, data);
        }
        else if (comp_(node->data_->first, data.first))
        {
            node->right_ = erase_node(node->right_, data);
        }
        else
        {
            // 単体のnode
            if ((node->left_ == NULL) || (node->right_ == NULL))
            {
                node_pointer child = node->left_ ? node->left_ : node->right_;

                // 子がない
                if (child == NULL)
                {
                    delete_node(node);
                    node = NULL;
                }
                else    // 子が1つ
                {
                    node_pointer target = node;

                    child->parent_ = target->parent_;
                    if (target->parent->right_ == target)
                        target->parent_->right_ = child;
                    else if (target->parent_->left == target)
                        target->parent_->left_ = child;
                    delete_node(target);
                    node = child;
                }
            }
            else
            {
                node_pointer new_node = get_min_node(node->right_);
                node_pointer target   = node;

                // 親ノードを新しいノードに設定する
                if (new_node->parent_->left_ == new_node)
                    new_node->parent_->left_ = NULL;
                else if (new_node->parent_->right_ == new_node)
                    new_node->parent_->right_ = NULL;

                // 新しいノードのセットアップ
                if (target->left_) new_node->left_ = target->left_;
                if (target->right_) new_node->right_ = target->right_;
                new_node->height_ = target->height;
                new_node->parent_ = target->parent_;

                // 新しいノードの子ノードのセットアップ
                if (new_node->left_) new_node->left_->parent_ = new_node;
                if (new_node->right_) new_node->right_->parent_ = new_node;
                delete_node(target);
                node = new_node;
            }
            rebalancing(node);
            return node;
        }
    }

    node_pointer search(const value_type& data) const
    {
        return search_node(root_, data);
    }

    node_pointer search_node(node_pointer node, const value_type& data) const
    {
        if (node == NULL)
        {
            return NULL;
        }
        // ノードよりも小さい場合はleftを探す
        if (comp_(data.first, node->data_->first))
            return search_node(node->left_, data);
        // ノードよりも大きい場合はrightを探す
        else if (comp_(node->data_->first, data.first))
            return search_node(node->right_, data);
        else
            return node;    //　最終的に
    }
};

}    // namespace ft

#endif
