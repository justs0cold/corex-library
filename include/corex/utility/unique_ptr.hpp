#ifndef COREX_UTILITY_UNIQUE_PTR_HPP
#define COREX_UTILITY_UNIQUE_PTR_HPP

#include "corex/utility/move.hpp"

#include <type_traits>
#include <utility>

namespace corex {
template <typename T> struct default_delete {
  constexpr default_delete() noexcept = default;

  template <typename U>
    requires(std::is_convertible_v<U *, T *>)
  constexpr explicit default_delete(const default_delete<U> & /*unused*/) noexcept {}

  constexpr void operator()(T *ptr) const { delete ptr; }
};

template <typename T> struct default_delete<T[]> {
  constexpr void operator()(T *ptr) const { delete[] ptr; }
};

template <typename T, typename Deleter = default_delete<T>> class unique_ptr {
public:
  constexpr unique_ptr() noexcept : ptr_(nullptr) {}
  constexpr explicit unique_ptr(T *ptr) noexcept : ptr_(ptr) {}

  constexpr unique_ptr(unique_ptr &&other) noexcept : ptr_(other.ptr_), deleter_(corex::move(other.deleter_)) {
    other.ptr_ = nullptr;
  }

  constexpr unique_ptr &operator=(unique_ptr &&other) noexcept {
    if (this != &other) {
      if (ptr_) {
        deleter_(ptr_);
      }

      ptr_ = other.ptr_;
      deleter_ = corex::move(other.deleter_);

      other.ptr_ = nullptr;
    }

    return *this;
  }

  // Copy semantics disabled for exclusive ownership
  unique_ptr(const unique_ptr &) = delete;
  unique_ptr &operator=(const unique_ptr &) = delete;

  constexpr ~unique_ptr() noexcept {
    if (ptr_) {
      deleter_(ptr_);
    }
  }

  [[nodiscard("Unused result of corex::unique_ptr::get")]] constexpr T *get() const noexcept { return ptr_; }

  [[nodiscard("Unused result of corex::unique_ptr::operator*")]] constexpr T &operator*() const noexcept {
    return *ptr_;
  }

  [[nodiscard("Unused result of corex::unique_ptr::operator->")]] constexpr T *operator->() const noexcept {
    return ptr_;
  }

  [[nodiscard("Unused result of corex::unique_ptr::operator bool")]] constexpr explicit operator bool() const noexcept {
    return ptr_ != nullptr;
  }

private:
  T *ptr_ = nullptr;
  [[no_unique_address]] Deleter deleter_{};
};

template <typename T, typename... Args>
[[nodiscard("Unused result of corex::make_unique")]] constexpr unique_ptr<T> make_unique(Args &&...args) {
  return unique_ptr<T>(new T(std::forward<Args>(args)...));
}
} // namespace corex

#endif // COREX_UTILITY_UNIQUE_PTR_HPP
