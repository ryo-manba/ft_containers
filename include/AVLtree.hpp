#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include "iterator.hpp"

namespace ft {

template<typename T, typename Compare, typename Allocator>
class AVLTree
{
public:
    typedef T value_type;
    typedef T& reference;
    typedef const T& const reference;
    typedef T* pointer;
    typedef size_t size_type;

private:

struct node
{
    pointer value_;
    node* left_;
    node* right_;
    size_type height_;

    node(pointer value = NULL, node* left = NULL, node* right = NULL)
    : value_(value), left_(left), right_(right), height(1)
    { }

    node(const node& other) { *this = other; }
    ~node(void) { }

    node& operator=(const node& rhs)
    {
        if (this == &rhs) {
            return *this;
        }
        value_ = rhs.value_;
        left_ = rhs.left_;
        right_ = rhs.right_;
        height_ = rhs.height_;
    }
    return *this;
};
};
}
#endif
