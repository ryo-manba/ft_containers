#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
template <class T1, class T2>
struct pair
{
    typedef T1 first_type;
    typedef T2 second_type;

    T1 first;
    T2 second;

    pair() : first(), second()
    {
    }
    pair(const T1& t1, const T2& t2) : first(t1), second(t2)
    {
    }

    template <class U1, class U2>
    pair(const pair<U1, U2>& other) : first(other.first), second(other.second)
    {
    }

    pair& operator=(const pair& other)
    {
        if (this == &other)
        {
            return *this;
        }
        first  = other.first;
        second = other.second;
        return *this;
    }
};

template <class T1, class T2>
bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <class T1, class T2>
bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return !(lhs == rhs);
}

template <class T1, class T2>
bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return lhs.first < rhs.first ||
           (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template <class T1, class T2>
bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return rhs < lhs;
}

template <class T1, class T2>
bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return !(lhs < rhs);
}

template <class T1, class T2>
bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return !(rhs < lhs);
}

template <class T1, class T2>
pair<T1, T2> make_pair(T1 first, T2 second)
{
    return pair<T1, T2>(first, second);
}

}    // namespace ft

#endif
