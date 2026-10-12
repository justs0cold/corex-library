#ifndef COREX_UTILITY_MOVE_HPP
#define COREX_UTILITY_MOVE_HPP

#include "corex/preprocessor/force_inline.hpp"

#include <type_traits>

namespace corex {
template <typename T>
[[nodiscard("Unused result of corex::move")]] COREX_FORCE_INLINE constexpr std::remove_reference_t<T> &&
move(T &&t) noexcept {
  return static_cast<std::remove_reference_t<T> &&>(t);
}
} // namespace corex

#endif // COREX_UTILITY_MOVE_HPP
