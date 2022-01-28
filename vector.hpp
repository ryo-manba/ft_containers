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
        vector( const allocator_type & alloc ) noexcept : alloc( alloc ) {}
        vector( size_type size, const allocator_type & alloc = allocator_type() )
            : vector( alloc ) { /*実装*/ }
        vector( size_type size, const_reference value, const allocator_type & alloc = allocator_type() )
            : vector( alloc ) { /*実装*/ }

        vector( size_type size, const allocator_type & alloc )
            : vector( alloc ) { resize( size ) ;}
        vector( size_type size, const_reference value, const allocator_type & alloc )
            : vector( alloc ) { resize( size, value ) ;}

        vector(std::initializer_lst<value_type> init, const Allocator & alloc= Allocator());
            : vector(std::begin(init), std::end(init), alloc)
        ~vector()
        {
            // 1. 要素を末尾から先頭に向かう順番で破棄
            clear();
            // 2. 生のメモリーを解放する
            deallocate();
        }

        vector(const vector& x)
        {
            if (size() +  > capacity())
            {
                // 現在のストレージサイズ
                auto c = size();
                if (c == 0)
                    c = 1;
                else
                    c *= 2; // それ以外の場合2倍にする

                reserve(c);
            }
            construct(last, value);
            ++last;
        }

        void shrink_to_fit()
        {
            if (size() == capacity())
                return ;

            auto ptr = allocate(size());
            auto current_size = size();
            for (aut raw_ptr = ptr, iter = begin(), iter_end = end(); iter != iter_end; ++iter, ++raw_ptr)
            {
                construct(raw_ptr, *iter);
            }
            clear();
            deallocate();
            // 新しいストレージを使う
            first = ptr;
            last = ptr + current_size;
            reserved_last = last;
        }

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

        void construct (pointer ptr) { traits::construct( alloc, ptr); }
        void construct(pointer ptr, const_reference value) { traits::construct(alloc, ptr, value); }
        void construct(pointer ptr, value_type && value) { traits::construct(alloc, ptr, std::move(value));}

        void clear() noexcept
        {
            desroy_until(rend());
        }

        void reserve(size_type sz)
        {
            if (sz <= capacity())
                return ;

            auto ptr = allocate(sz);
            auto old_first = first;
            auto old_last = last;
            auto old_capacity = capacity();

            first = ptr;
            last = first;
            reserved_last = first + sz;

            std::scope_exit e([&] {
                traits::deallocate(alloc, old_first, old_capacity);
            });
            for (auto old_iter = old_first; old_iter != old_last; ++old_iter, ++last)
            {
                construct(las,t std::move(*old_iter));
            }
            // 新しいストレージにコピーし終えたので古いストレージの値は破棄
            for (auto riter = reverse_iterator(old_last), rend = reverse_iterator(old_first); riter != rend; ++riter)
            {
                destroy(&*riter);
            }
        }

        void resize(size_type sz)
        {
            if (sz < size())
            {
                auto diff = size() - sz;
                destroy_until(rbegin() + diff);
                last = first + sz;
            }
            else if (sz > size())
            {
                reserve(sz);
                for (; last != reserved_last; ++last)
                {
                    construct(last);
                }
            }
        }

        template <typename InputIterator>
        vector(InputIterator first, InputIterator last, const Allocator& = Allocator())
        {
            reserve(std::distance(first, last));
            for (auto i = first; i != last; ++i)
            {
                push_back(*i);
            }
        }


    private:
        pointer first;
        pointer last;
        pointer reserved_last;
        allocator_type alloc;

        using traits = std::allocator_traits<allocator_type>;
        template < typename Allocator>
        void f(Allocator & alloc)
        {
            traitss::allocate(alloc, 1);
        }
        pointer allocate(size_type n) { return traits::allocate(alloc, n); }
        void deallocate() { traits::deallocate(alloc, first, capacity()); }

        void destroy(pointer ptr) { traits::destory(alloc, ptr); }

        void destroy_until(reverse_iterator rend)
        {
            for (auto riter = rbegin(); riter != rend; ++riter, --last)
            {
                destroy(&*riter);
            }
        }
    };
}
