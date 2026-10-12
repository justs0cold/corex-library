#ifndef COREX_UTILITY_FORWARD_HPP
#define COREX_UTILITY_FORWARD_HPP

#include <type_traits>

namespace corex {
template <typename T>
constexpr T &&forward(std::remove_reference_t<T> &arg) noexcept {
  return static_cast<T &&>(arg);
}

template <typename T>
constexpr T &&forward(std::remove_reference_t<T> &&arg) noexcept {
  static_assert(
      !std::is_lvalue_reference_v<T>,
      "bad corex::forward call: cannot forward an rvalue as an lvalue");
  return static_cast<T &&>(arg);
}
} // namespace corex

#endif // COREX_UTILITY_FORWARD_HPP