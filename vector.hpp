#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

namespace ft
{
    template <typename T, typename Allocator =  std::allocator<T> >
    class vector
    {

    public:
        using value_type = T;
        using pointer    = T *;
        using const_pointer = const_pointer;
        using reference     = value_type &;
        using const_reference = const value_type &;

        using allocator_type = Allocator;

        using iterator = pointer;
        using const_iterator = const_pointer;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator =std::reverse_iterator<const_iterator>;

        vector(std::size_t n = 0, Allocator a = Allocator());
        ~vector();
        vector(const vector& x);
        vector& operator =(const vector& x);

        void push_back(const T& x);
        T& operator [](std::size_t i) noexcept;

        iterator begin() noexcept { return first ; }
        iterator begin() const noexcept { return first ; }
        iterator end() noexcept { return last ; }
        iterator end() const noexcept { return last ; }
        reverse_iterator rbegin() noexcept { return reverse_iterator{ last } ; }
        reverse_iterator rbegin() const noexcept { return reverse_iterator{ last } ; }
        reverse_iterator rend() noexcept { return reverse_iterator{ first } ; }
        reverse_iterator rend() const noexcept { return reverse_iterator{ first } ; }

        size_type size() const noexcept
        {
            return end() - begin();
        }
        bool empty() const noexcept
        {
            return size() == 0;
//            return begin() == end();
        }
        size_type capacity() const noexcept
        {
            return reserved_last - first;
        }

        reference operator[](size_type i) { return first[i]; }
        const_reference operator[](size_type i) const { return first[i]; }

        reference at(size_type i)
        {
            if (i >= size())
                throw std::out_of_range("index is out of range.");
            return first[i];
        }
        const_reference at(size_type i) const
        {
            if (i >= size())
                throw std::out_of_range("index is out of range.");
            return first[i];
        }

        reference front() { return first; }
        const_reference front() const { return first; }
        reference back() { return last - 1; }
        const_reference back() const { return last - 1; }

        pointer data() noexcept { return first; }
        const_pointer data() const noexcept { return first; }

    private:
        pointer first;
        pointer last;
        pointer reserved_last;
        allocator_type alloc;
    };
}
