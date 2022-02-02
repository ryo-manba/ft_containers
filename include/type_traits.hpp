#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft
{

// integral_constant
// is_integral / enable_ifで使う構造体
template <typename Tp, Tp v>
struct integral_constant
{
    static const Tp value = v;
    typedef Tp value_type;
    typedef integral_constant<Tp, v> type;
    const value_type operator()() const { return value; }
};

template <typename Tp, Tp v>
const Tp integral_constant<Tp, v>::value;

/// The type used as a compile-time boolean with true value.
typedef integral_constant<bool, true> true_type;

/// The type used as a compile-time boolean with false value.
typedef integral_constant<bool, false> false_type;

/// is_same
template <typename Tp, typename Up>
struct is_same : public false_type
{
};

template <typename Tp>
struct is_same<Tp, Tp> : public true_type
{
};

// Const-volatile modifications.

/// remove_const
template <typename Tp>
struct remove_const
{
    typedef Tp type;
};

template <typename Tp>
struct remove_const<Tp const>
{
    typedef Tp type;
};

/// remove_volatile
template <typename Tp>
struct remove_volatile
{
    typedef Tp type;
};

template <typename Tp>
struct remove_volatile<Tp volatile>
{
    typedef Tp type;
};

/// remove_cv
template <typename Tp>
struct remove_cv
{
    typedef Tp type;
};

template <typename Tp>
struct remove_cv<const Tp>
{
    typedef Tp type;
};

template <typename Tp>
struct remove_cv<volatile Tp>
{
    typedef Tp type;
};

template <typename Tp>
struct remove_cv<const volatile Tp>
{
    typedef Tp type;
};

/// 整数型以外はfalseを返す
template <typename>
struct is_integral_helper : public false_type
{
};

template <>
struct is_integral_helper<bool> : public true_type
{
};

template <>
struct is_integral_helper<char> : public true_type
{
};

template <>
struct is_integral_helper<signed char> : public true_type
{
};

template <>
struct is_integral_helper<wchar_t> : public true_type
{
};

template <>
struct is_integral_helper<short> : public true_type
{
};

template <>
struct is_integral_helper<unsigned short> : public true_type
{
};

template <>
struct is_integral_helper<int> : public true_type
{
};

template <>
struct is_integral_helper<unsigned int> : public true_type
{
};

template <>
struct is_integral_helper<long> : public true_type
{
};

template <>
struct is_integral_helper<unsigned long> : public true_type
{
};

/// is_integral
template <typename Tp>
struct is_integral
    : public is_integral_helper<typename remove_cv<Tp>::type>::type
{
};

// Primary template.
// Define a member typedef @c type only if a boolean constant is true.
// bool値がtrueの場合のみtypeを定義する
template <bool, typename Tp = void>
struct enable_if
{
};

// Partial specialization for true.
template <typename Tp>
struct enable_if<true, Tp>
{
    typedef Tp type;
};

// Primary template.
/// Define a member typedef @c type to one of two argument types.
template <bool Cond, typename Iftrue, typename Iffalse>
struct conditional
{
    typedef Iftrue type;
};

// Partial specialization for false.
template <typename Iftrue, typename Iffalse>
struct conditional<false, Iftrue, Iffalse>
{
    typedef Iffalse type;
};

}    // namespace ft
#endif
