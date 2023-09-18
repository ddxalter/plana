#ifndef PLANA_SLICE_H_
#define PLANA_SLICE_H_

#include "plana/common.h"

namespace plana {

template<class T>
class SliceAccessor
{
  friend class Slice;
public:
  using size_type = size_t;
  using pointer = T*;
  using reference = T&;

  reference operator[](size_type i) { return data_[i]; }
  size_type size() const { return size_; }
  pointer data() const { return data_; }
  pointer begin() const { return data_; }
  pointer end() const { return data_ + size_; }
private:
  SliceAccessor() = delete;
  SliceAccessor(const SliceAccessor&) = delete;
  SliceAccessor(SliceAccessor&&) = default;
  explicit SliceAccessor(size_type size, pointer data) : size_(size), data_(data) {}
  size_type size_ = 0;
  pointer data_ = nullptr;
};

class Slice
{
public:
  using size_type = std::size_t;

  Slice() = default;
  Slice(const Slice&) = default;
  Slice(Slice&&) = default;
  Slice& operator=(const Slice&) = default;
  Slice& operator=(Slice&&) = default;

  explicit Slice(size_type first, size_type last) : first_(first), last_(last) {}

  Slice operator[](std::pair<size_type, size_type> slice)
  {
    return Slice{std::min(first_ + slice.first, last_), std::min(first_ + slice.second, last_)};
  }

  template<class VectorType>
  SliceAccessor<typename VectorType::value_type> operator()(VectorType& v)
  {
    return SliceAccessor<typename VectorType::value_type>{std::min(v.size(), last_) - first_, v.data() + first_};
  }
  template<class VectorType>
  SliceAccessor<const typename VectorType::value_type> operator()(const VectorType& v) const
  {
    return SliceAccessor<const typename VectorType::value_type>{std::min(v.size(), last_) - first_, v.data() + first_};
  }
  template<class VectorType>
  void operator()(VectorType&& v) = delete;
private:
  size_type first_ = 0;
  size_type last_ = -1;
};

} // namespace plana

#endif // PLANA_SLICE_H_