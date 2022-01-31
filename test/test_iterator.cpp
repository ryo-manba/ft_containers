#include "iterator.hpp"

/*
 * 入力イテレーター(Input Iterator)
 * 出力イテレーター(Output Iterator)
 * 前方イテレーター(Forward Iterator)
 * 双方向イテレーター(Bidirectional Iterator)
 * ランダムアクセスイテレーター(Random Access Iterator)
 **/

// Random Access Iterator
template < typename RandomAccessIterator >
void f( RandomAccessIterator i, int n  )
{
    i + n ;
    i - n ;
    n + i ; // i+nと同じ
    n - i ; // n-iと同じ

    i + (-n) ; // i - nと同じ

    // i = i + n ; と同じ
    i += n ;
    // i = i - n ; と同じ
    i -= n ;
}

template < typename RandomAccessIterator >
void f( RandomAccessIterator a, RandomAccessIterator b )
{
    b - a ; // aからbまでの距離
    a - b ; // bからaまでの距離
}

template < typename RandomAccessIterator >
void f( RandomAccessIterator a )
{
    auto b = a ;
    // bはaより3進んでいる
    ++b ; ++b ; ++b ;
    b - a ; // 3
    a - b ; // -3
}

template < typename RandomAccessIterator >
void f( RandomAccessIterator i, std::size_t n )
{
    // *(i + n) ; と同じ
    i[n] ;
}

template < typename RandomAccessIterator >
void f( RandomAccessIterator i, RandomAccessIterator j )
{
    i   <   j ;
    i   >   j ;
    i   <=  j ;
    i   >=  j ;
}

template < typename Iterator >
void f( Iterator i )
{
    // jはn+1番目を指す
    auto j = i + 1 ;

    i < j ; // true
    i > j ; // false
}

template < typename Iterator >
void f( Iterator i, Iterator j )
{
    i == j ;
    i != j ;
}

template < typename Iterator >
void f( Iterator i )
{
    auto j = i ;
    i == j ;    // true
    ++j ;
    i = j ;     // false
}

// 双方向イテレーター
template < typename BidirectionalIterator >
void f( BidirectionalIterator i )
{
    ++i ; // i+1
    --i ; // i-1

    // r1, r2は変更する前のiの値
    auto r1 = i++ ;
    auto r2 = i-- ;
}

template < typename BidirectionalIterator >
BidirectionalIterator
nth_next( BidirectionalIterator iter, std::size_t n )
{
    for ( std::size_t i = 0 ; i != n ; ++i )
        ++iter ;
    return iter ;
}

// 前方イテレーター
template < typename ForwardIterator >
void f( ForwardIterator i )
{
    ++i ;
}

template < typename ForwardIterator >
void f( ForwardIterator i )
{
    // 動かす前の値を保持
    auto prev = i ;
    // 次の要素を指す
    ++i ;
    // 動かす前の値も次の要素を指すようにする
    ++prev ;

    // true
    bool b = ( i == prev ) ;

    // r1, r2は同じ要素を指す
    auto & r1 = *i ;
    auto & r2 = *prev ;
}

// 入力イテレーター
template < typename InputIterator >
void f( InputIterator i, InputIterator j )
{
    // 比較
    bool b1 = (i == j) ;
    bool b2 = (i != j) ;

    // 参照
    *i ;
    // (*i).m と同じ
    i->m ;

    // インクリメント
    ++i ;
    i++ ;
}

template < typename InputIterator >
void f( InputIterator i )
{
    // OK
    auto value = *i ;
    // エラー
    *i = value ;
}

// 出力イテレーター
template < typename OutputIterator >
void f( OutputIterator i, typename OutputIterator::value_type v )
{
    // 参照への代入
    *i = v ;

    // インクリメント
    ++i ;
    i++ ;
}

template < typename OutputIterator >
void f( OutputIterator i )
{
    // 意味がな
    auto value = *i ;
}


