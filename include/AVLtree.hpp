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

    Pair data_;
    node_pointer parent_;
    node_pointer left_;
    node_pointer right_;
    long height_;

public:
    tree_node(node_pointer parent = NULL, node_pointer left_ = NULL,
              node_pointer right_ = NULL)
        : parent_(parent), left_(left_), right_(right_), height_(0)
    {
    }
    tree_node(Pair p)
        : data_(p), parent_(NULL), left_(NULL), right_(NULL), height_(0)
    {
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
    /**
     * utility
     */
    node_pointer get_max_node(node_pointer node) const
    {
        node_pointer maxi = node;

        while (maxi->right_)
        {
            maxi = maxi->right_;
        }
        return maxi;
    }

    node_pointer get_min_node(node_pointer node) const
    {
        node_pointer mini = node;

        while (mini->left_)
        {
            mini = mini->left_;
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
            return get_min_node(node->right_);
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
    typedef std::bidirectional_iterator_tag iterator_category;
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
    tree_iterator(const tree_iterator& other) : node_(other.base())
    {
    }
    tree_iterator& operator=(const tree_iterator& other)
    {
        if (this == &other)
        {
            return *this;
        }
        node_ = other.base();
        return *this;
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

    node_pointer base() const
    {
        return node_;
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
    tree_const_iterator(const tree_iterator& other) : node_(other.base())
    {
    }
    tree_const_iterator(const tree_const_iterator& other) : node_(other.base())
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

    node_pointer base() const
    {
        return node_;
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
    node_pointer last_;    // end()用のダミーノード
    size_type size_;       // マップの要素数
    key_compare comp_;
    node_allocator alloc_;

public:
    explicit tree(const key_compare& comp     = key_compare(),
                  const allocator_type& alloc = allocator_type())
        : root_(NULL), size_(0), comp_(comp), alloc_(node_allocator(alloc))
    {
        init_tree();
    }
    tree(const tree& other)
    {
        init_tree();
        root_  = NULL;
        size_  = 0;
        comp_  = other.comp_;
        alloc_ = other.alloc_;
        insert_range_unique(other.begin(), other.end());
    }

    ~tree(void)
    {
        all_clear(root_);
        root_ = NULL;
        delete_node(last_);
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
        return iterator(last_->get_min_node(last_));
    }
    const_iterator begin() const
    {
        return const_iterator(last_->get_min_node(last_));
    }
    iterator end()
    {
        return iterator(last_);
    }
    const_iterator end() const
    {
        return const_iterator(last_);
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

    // Modifiers
    void clear()
    {
        all_clear(root_);
        root_        = NULL;    // NULL埋めしないとデストラクターでダブルフリーしちゃう
        size_        = 0;    // clearを呼んだあとはsizeが0になる
        last_->left_ = NULL;
    }

    // 追加したノードのイテレータと挿入したかを表すbool値
    ft::pair<iterator, bool> insert_unique(const value_type& data)
    {
        // 既に要素が存在する場合は挿入しない
        node_pointer p = search_node(root_, data);
        if (p) return ft::make_pair(iterator(p), false);

        root_        = insert_node(root_, data);
        last_->left_ = root_;    // begin()用
        if (root_) root_->parent_ = last_;
        p = search_node(root_, data);
        return ft::make_pair(iterator(p), true);
    }

    // hintの親を見て
    // less<int>()(2, 3) // true
    // less<int>()(3, 3) // false
    // TODO:
    // 現状nodeを追加した後で全てのノードに対してバランスを取る処理を行っている
    //       追加したノードから親を辿りながらバランスを取るように変更する
    iterator insert_unique(iterator hint, const value_type& data)
    {
        // 挿入ノードとhintの値が同じ場合
        if (hint.base()->data_.first == data.first)
        {
            return hint;
        }

        bool is_correct_hint = false;
        if (hint.base()->parent_)
        {
            // 親よりも大きいかつ右の子ノード
            if (comp_(hint.base()->parent_->data_.first,
                      hint.base()->data_.first) &&
                tree_is_right_child(hint.base()))
            {
                // 挿入ノードがhintの親よりも大きい必要がある
                if (comp_(hint.base()->parent_->data_.first, data.first))
                {
                    is_correct_hint = true;
                }
            }
            // 親よりも小さいかつ左の子ノード
            else if (comp_(hint.base()->data_.first,
                           hint.base()->parent_->data_.first) &&
                     tree_is_left_child(hint.base()))
            {
                // 挿入ノードがhintの親よりも小さい必要がある
                if (comp_(data.first, hint.base()->parent_->data_.first))
                {
                    is_correct_hint = true;
                }
            }
        }
        if (is_correct_hint)
        {
            size_ += 1;
            // hintよりも大きい場合
            if (comp_(hint.base()->data_.first, data.first) &&
                (hint.base()->right_ != NULL))
            {
                //                root_ = insert_node(hint.base(), data);
                hint.base()->right_ = create_node(data);
                root_               = rebalance(root_);
                return hint.base()->right_;
            }
            if (comp_(data.first, hint.base()->data_.first) &&
                (hint.base()->left_ != NULL))
            {
                //                root_ = insert_node(hint.base(), data);
                hint.base()->left_ = create_node(data);
                root_ =
                    rebalance(root_);    // 全てのノードに対してバランスを取る
                return hint.base()->left_;
            }
        }
        // hintが正しくないのでルートから挿入する
        root_ = insert_node(root_, data);
        return search_node(root_, data);
    }

    template <typename InputIt>
    void insert_range_unique(InputIt first, InputIt last)
    {
        for (; first != last; ++first)
        {
            insert_unique(*first);
        }
    }

    void erase(value_type data)
    {
        root_        = erase_node(root_, data);
        last_->left_ = root_;
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
        while (first != last) erase(first++);
    }

    size_type erase_unique(const key_type& key)
    {
        iterator it = find(key);
        if (it == end()) return 0;
        erase(it);
        return 1;
    }

    void swap(tree& other)
    {
        std::swap(root_, other.root_);
        std::swap(last_, other.last_);
        std::swap(size_, other.size_);
        std::swap(comp_, other.comp_);
        std::swap(alloc_, other.alloc_);
    }

    // Lookup
    size_type count(const key_type& key) const
    {
        if (find(key) == end()) return 0;
        return 1;
    }

    // 木の中からkeyがあるか捜索する
    iterator find(const key_type& key)
    {
        node_pointer node = search_node(root_, ft::make_pair(key, mapped_type()));

        if (node) // && !comp_(key, node->data_.first))
        {
            return iterator(node);
        }
        return end();
    }

    const_iterator find(const key_type& key) const
    {
        node_pointer node = search_node(root_, ft::make_pair(key, mapped_type()));

        if (node && !comp_(key, node->data_.first)) return const_iterator(node);
        return end();
    }

    ft::pair<iterator, iterator> equal_range(const key_type& key)
    {
        iterator it1 = lower_bound(key);
        iterator it2 = upper_bound(key);

        return ft::make_pair(it1, it2);
    }

    ft::pair<const_iterator, const_iterator> equal_range(
        const key_type& key) const
    {
        const_iterator it1 = lower_bound(key);
        const_iterator it2 = upper_bound(key);

        return ft::make_pair(it1, it2);
    }

    // key以上の値を返す
    // なかったらendを返す
    // less<int>()(2, 3) // true
    // less<int>()(3, 3) // false
    iterator lower_bound(const key_type& key)
    {
        for (iterator it = begin(); it != end(); ++it)
        {
            if (!comp_(it->first, key))
            {
                return it;
            }
        }
        return end();
    }

    const_iterator lower_bound(const key_type& key) const
    {
        for (const_iterator it = begin(); it != end(); ++it)
        {
            if (!comp_(it->first, key))
            {
                return it;
            }
        }
        return end();
    }

    // keyより大きい値を返す
    // less<int>()(2, 3) // true
    // less<int>()(3, 3) // false
    iterator upper_bound(const key_type& key)
    {
        for (iterator it = begin(); it != end(); ++it)
        {
            if (comp_(key, it->first))
            {
                return it;
            }
        }
        return end();
    }

    const_iterator upper_bound(const key_type& key) const
    {
        for (const_iterator it = begin(); it != end(); ++it)
        {
            if (comp_(key, it->first))
            {
                return it;
            }
        }
        return end();
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
    void init_tree()
    {
        last_ = alloc_.allocate(1);
        alloc_.construct(last_);
        last_->left_   = NULL;
        last_->right_  = NULL;
        last_->parent_ = NULL;
        last_->height_ = 0;
    }

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

    // 木の高さを更新する
    // 木の高さ = 1 + max(左の木の高さ, 右の木の高さ)
    void update_height(node_pointer node)
    {
        if (node == NULL)
        {
            return;
        }
        else
        {
            long left_height  = node->left_ ? node->left_->height_ : 0;
            long right_height = node->right_ ? node->right_->height_ : 0;
            node->height_     = 1 + std::max(left_height, right_height);
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
        node_pointer b      = a->left_;
        node_pointer y      = b->right_;

        b->right_  = a;
        a->parent_ = b;
        b->parent_ = parent;
        a->left_   = y;
        if (y) y->parent_ = a;
        update_height(a);
        update_height(b);
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
        update_height(a);
        update_height(b);
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
        a->right_ = rotate_right(a->right_);
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
        a->left_ = rotate_left(a->left_);
        return rotate_right(a);
    }

    // 偏りに応じてバランスを取る
    // 回転後のrootを返す
    node_pointer balancing(node_pointer node)
    {
        update_height(node);
        long balance = node->calc_balance_factor();

        if (balance > 1)
        {
            if (node->left_->calc_balance_factor() < 0)
                return rotate_lr(node);
            else
                return rotate_right(node);
        }
        if (balance < -1)
        {
            if (node->right_->calc_balance_factor() > 0)
                return rotate_rl(node);
            else
                return rotate_left(node);
        }
        return node;
    }

    node_pointer rebalance(node_pointer node)
    {
        if (node->parent_)
            if (node->right_) return rebalance(node->right_);
        if (node->left_) return rebalance(node->left_);
        return balancing(node);
    }

    /**
     * @brief
     * 大小比較して適切な位置にnodeを追加する
     * 偏りに応じて回転させる
     * 要素を挿入後再帰的にバランスを取りながらrootまでたどっていく
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
        if (comp_(data.first,
                  node->data_.first))    // 現nodeよりも挿入したい値が小さい場合
        {
            // 左にたどっていく
            node->left_          = insert_node(node->left_, data);
            node->left_->parent_ = node;
        }
        else if (comp_(node->data_.first,
                       data.first))    // 現nodeよりも挿入したい値が大きい場合
        {
            // 右にたどっていく
            node->right_          = insert_node(node->right_, data);
            node->right_->parent_ = node;
        }
        else
        {
            // すでにkeyが存在した場合
            return node;
        }

        // 木の偏りをもとにバランスを取る
        return balancing(node);
    }

    // less<int>()(2, 3) // true
    // less<int>()(3, 3) // false
    node_pointer erase_node(node_pointer node, value_type data)
    {
        if (node == NULL)
        {
            return node;
        }
        // 現在地よりもdataが小さい場合
        if (comp_(data.first, node->data_.first))
        {
            node->left_ = erase_node(node->left_, data);
        }
        // 現在地よりもdataが大きい場合
        else if (comp_(node->data_.first, data.first))
        {
            node->right_ = erase_node(node->right_, data);
        }
        // 削除するノード
        else
        {
            if ((node->left_ == NULL) || (node->right_ == NULL))
            {
                node_pointer child = node->left_ ? node->left_ : node->right_;

                // 葉っぱの場合は削除するだけ
                if (child == NULL)
                {
                    delete_node(node);
                    node = NULL;
                }
                else    // 子が1つのときは入れ替えるだけ
                {
//                    debug(1);
//                    print(node->data_.first);
//                    print(child->data_.first);
//                    std::swap(&(node->data_), &(child->data_));
//                    delete_node(child);

                    node_pointer target = node;

                    // つなぎ替える
                    child->parent_ = target->parent_;
                    if (target->parent_->right_ == target)
                        target->parent_->right_ = child;
                    else if (target->parent_->left_ == target)
                        target->parent_->left_ = child;
                    delete_node(target);
                    node = child;
                }
            }
            else // 子供が2つあるノード
            {
                // 左側の部分木のノードの最大ノード
                node_pointer left_child_max = node->left_->get_max_node(node->left_);
                node_pointer target   = node;

                // 親ノードを新しいノードに設定する
                if (left_child_max->parent_->left_ == left_child_max)
                    left_child_max->parent_->left_ = NULL;
                else if (left_child_max->parent_->right_ == left_child_max)
                    left_child_max->parent_->right_ = NULL;

                // 削除ノードの子を新しいノードに付け替える
                if (target->left_) left_child_max->left_ = target->left_;
                if (target->right_) left_child_max->right_ = target->right_;
                left_child_max->height_ = target->height_;
                left_child_max->parent_ = target->parent_;

                // 新しいノードの子ノードの親を設定する
                if (left_child_max->left_) left_child_max->left_->parent_ = left_child_max;
                if (left_child_max->right_) left_child_max->right_->parent_ = left_child_max;
                delete_node(target);
                node = left_child_max;
            }
        }
        if (node) balancing(node);
        return node;
    }

    // keyがある : その要素を返す
    // keyがない : NULL
    node_pointer search_node(node_pointer node, const value_type& data) const
    {
        if (node == NULL)
        {
            return NULL;
        }
        // ノードよりも小さい場合はleftを探す
        if (comp_(data.first, node->data_.first))
            return search_node(node->left_, data);
        // ノードよりも大きい場合はrightを探す
        else if (comp_(node->data_.first, data.first))
            return search_node(node->right_, data);
        else
            return node;    // keyが見つかった場合
    }

    bool tree_is_left_child(node_pointer x)
    {
        return x == x->parent_->left_;
    }
    bool tree_is_right_child(node_pointer x)
    {
        return x == x->parent_->right_;
    }
};

}    // namespace ft

#endif
