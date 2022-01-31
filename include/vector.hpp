#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>

namespace ft {
template <typename T, typename Allocator = std::allocator<T>> class vector {

  public:
          typedef T  value_type;
          typedef size_t size_type;
          typedef T* pointer;
          typedef const pointer const_pointer;
          typedef value_type& reference;
          typedef const value_type& const_reference;
          typedef Allocator allocator_type;

          typedef pointer iterator;
          typedef const_pointer const_iterator;
          typedef std::reverse_iterator<iterator> reverse_iterator;
          typedef std::reverse_iterator<const_iterator>
          const_reverse_iterator;

  // using value_type = T;
  // using pointer = T *;
  // using const_pointer = const pointer;
  // using reference = value_type &;
  // using const_reference = const value_type &;
  // using allocator_type = Allocator;
  // using size_type = std::size_t;
  // using difference_type = std::ptrdiff_t;

  // using iterator = pointer;
  // using const_iterator = const_pointer;
  // using reverse_iterator = std::reverse_iterator<iterator>;
  // using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  // constructor
  vector() : vector(allocator_type()) {}
  explicit vector(const Allocator& alloc)
      : first(NULL), last(NULL), reserved_last(NULL), alloc(alloc) {}
  explicit vector(size_type count, const T& value = T(),
         const Allocator &alloc = Allocator())
      : vector(alloc) {
    resize(count, value);
  }

  template <typename InputIt>
  vector(InputIt first, InputIt last,
         const Allocator& alloc = Allocator(),
         typename std::enable_if<!std::is_integral<InputIt>::value,
         InputIt>::type* = NULL)
      : first(NULL), last(NULL), reserved_last(NULL), alloc(alloc) {
    reserve(std::distance(first, last));
    for (auto i = first; i != last; ++i) {
      push_back(*i);
    }
  }

  // destructor
  ~vector() {
    // 1. 要素を末尾から先頭に向かう順番で破棄
    clear();
    // 2. 生のメモリーを解放する
    deallocate();
  }

  // copy constructor
  vector(const vector& other)
      : first(NULL), last(NULL), reserved_last(NULL),
        alloc(traits::select_on_container_copy_construction(other.alloc)) {
    // コピー元の要素数を保持できるだけのストレージを確保
    reserve(other.size());
    // コピー元の要素をコピー構築
    // destはコピー先
    // [src, last)はコピー元
    for (auto dest = first, src = other.begin(), last = other.end(); src != last;
         ++dest, ++src) {
      construct(dest, *src);
    }
  }

  vector &operator=(const vector &r) {
    // 自分自身への代入なら何もしない
    if (this == &r)
      return *this;

    // 要素数が同じ
    if (size() == r.size()) {
      // 要素ごとコピー代入
      std::copy(r.begin(), r.end(), begin());
    } else {
      // 予約数が十分
      if (capacity() >= r.size()) {
        // 有効な要素はコピー
        std::copy(r.begin(), r.begin() + r.size(), begin());
        // 残りはコピー構築
        for (auto src_iter = r.begin() + r.size(), src_end = r.end();
             src_iter != src_end; ++src_iter, ++last) {
          construct(last, *src_iter);
        }
      } else // 予約数が不十分
      {
        // 要素をすべて破棄
        destroy_until(rbegin());
        // 予約
        reserve(r.size());
        // コピー構築
        for (auto src_iter = r.begin(), src_end = r.end(), dest_iter = begin();
             src_iter != src_end; ++src_iter, ++dest_iter, ++last) {
          construct(dest_iter, *src_iter);
        }
      }
    }
    return *this;
  }

  void push_back(const_reference value) {
    // 予約メモリーが足りなければ拡張
    if (size() + 1 > capacity()) {
      // 現在のストレージサイズ
      auto c = size();
      // 0の場合は1に
      if (c == 0)
        c = 1;
      else
        // それ以外の場合は2倍する
        c *= 2;

      reserve(c);
    }
    // 要素を末尾に追加
    construct(last, value);
    // 有効な要素数を更新
    ++last;
  }

  // 容量確認
  size_type size() const { return end() - begin(); }
  bool empty() const { return begin() == end(); }
  size_type capacity() const { return reserved_last - first; }

  // 要素アクセス
  reference operator[](size_type i) { return first[i]; }
  const_reference operator[](size_type i) const { return first[i]; }

  reference at(size_type i) {
    if (i >= size())
      throw std::out_of_range("index is out of range.");
    return first[i];
  }
  const_reference at(size_type i) const {
    if (i >= size())
      throw std::out_of_range("index is out of range.");
    return first[i];
  }

  // DEBUG
  reference front() { return *first; }
  const_reference front() const { return *first; }
  reference back() { return *(last - 1); }
  const_reference back() const { return *(last - 1); }

  pointer data() { return first; }
  const_pointer data() const { return first; }

  // イテレーターアクセス
  iterator begin() { return first; }
  iterator begin() const { return first; }
  iterator end() { return last; }
  iterator end() const { return last; }
  reverse_iterator rbegin() { return reverse_iterator{last}; }
  reverse_iterator rbegin() const { return reverse_iterator{last}; }
  reverse_iterator rend() { return reverse_iterator{first}; }
  reverse_iterator rend() const { return reverse_iterator{first}; }

  void clear() { destroy_until(rend()); }

  void reserve(size_type sz) {
    // すでに指定された要素数以上に予約されているなら何もしない
    if (sz <= capacity())
      return;

    // 動的メモリー確保をする
    auto ptr = allocate(sz);

    // 古いストレージの情報を保存
    auto old_first = first;
    auto old_last = last;
//    auto old_capacity = capacity();

    // 新しいストレージに差し替え
    first = ptr;
    last = first;
    reserved_last = first + sz;

    // 古いストレージから新しいストレージに要素をコピー構築
    // 実際にはムーブ構築
    for (auto old_iter = old_first; old_iter != old_last; ++old_iter, ++last) {
      // このコピーの理解にはムーブセマンティクスの理解が必要
      construct(last, std::move(*old_iter));
    }

    // 新しいストレージにコピーし終えたので古いストレージの値は破棄
    for (auto riter = reverse_iterator(old_last),
              rend = reverse_iterator(old_first);
         riter != rend; ++riter) {
      destroy(&*riter);
    }
  }

  void resize(size_type sz) {
    // 現在の要素数より少ない
    if (sz < size()) {
      auto diff = size() - sz;
      destroy_until(rbegin() + diff);
      last = first + sz;
    }
    // 現在の要素数より大きい
    else if (sz > size()) {
      reserve(sz);
      for (; last != reserved_last; ++last) {
        construct(last);
      }
    }
  }

  void resize(size_type sz, const_reference value) {
    if (sz < size()) {
      auto diff = size() - sz;
      destroy_until(rbegin() + diff);
      last = first + sz;
    } else if (sz > size()) {
      reserve(sz);
      for (; last != reserved_last; ++last) {
        construct(last, value); // ここが引数valueに変更されている
      }
    }
  }

  private:
  pointer first;
  pointer last;
  pointer reserved_last;
  allocator_type alloc;

  // ヘルパー関数
  //  typedef std::allocator_traits<allocator_type> traits;
  using traits = std::allocator_traits<allocator_type>;

  pointer allocate(size_type n) { return traits::allocate(alloc, n); }
  void deallocate() { traits::deallocate(alloc, first, capacity()); }
  void construct(pointer ptr) { traits::construct(alloc, ptr); }
  void construct(pointer ptr, const_reference value) {
    traits::construct(alloc, ptr, value);
  }

  void construct(pointer ptr, value_type &&value) {
    traits::construct(alloc, ptr, std::move(value));
  }

  void destroy(pointer ptr) { traits::destroy(alloc, ptr); }
  void destroy_until(reverse_iterator rend) {
    for (auto riter = rbegin(); riter != rend; ++riter, --last) {
      destroy(&*riter);
    }
  }
};

}; // namespace ft

#endif
