#ifndef COREX_UTILITY_MAKE_ARRAY_HPP
#define COREX_UTILITY_MAKE_ARRAY_HPP

#include <array>
#include <concepts>
#include <type_traits>
#include <utility>

namespace corex {
template <std::size_t N, typename F>
  requires std::invocable<F, std::size_t>
[[nodiscard("Unused result of corex::make_array")]] constexpr auto
make_array(F &&f) noexcept(std::is_nothrow_invocable_v<F, std::size_t>) {
  return [&]<std::size_t... Is>(std::index_sequence<Is...>) {
    return std::array<std::remove_cvref_t<std::invoke_result_t<F, std::size_t>>, N>{std::forward<F>(f)(Is)...};
  }(std::make_index_sequence<N>{});
}

template <std::size_t N, typename T>
[[nodiscard("Unused result of corex::make_array")]] constexpr auto
make_array(T &&val) noexcept(std::is_nothrow_constructible_v<std::remove_cvref_t<T>, T>) {
  static_assert(std::is_copy_constructible_v<std::remove_cvref_t<T>>, "T must be copy constructible");

  if constexpr (std::is_trivially_copyable_v<std::remove_cvref_t<T>>) {
    return [&]<std::size_t... Is>(std::index_sequence<Is...>) {
      return std::array<std::remove_cvref_t<T>, N>{((void)Is, std::forward<T>(val))...};
    }(std::make_index_sequence<N>{});
  } else {
    return [&]<std::size_t... Is>(std::index_sequence<Is...>) {
      return std::array<std::remove_cvref_t<T>, N>{((void)Is, std::forward<T>(val))...};
    }(std::make_index_sequence<N>{});
  }
}

template <typename First, typename... Rest>
  requires(std::same_as<std::remove_cvref_t<First>, std::remove_cvref_t<Rest>> && ...)
[[nodiscard("Unused result of corex::make_array")]] constexpr auto
make_array(First &&first,
           Rest &&...rest) noexcept((std::is_nothrow_constructible_v<std::remove_cvref_t<First>, First> &&
                                     (std::is_nothrow_constructible_v<std::remove_cvref_t<Rest>, Rest> && ...))) {
  return std::array<std::remove_cvref_t<First>, 1 + sizeof...(Rest)>{std::forward<First>(first),
                                                                     std::forward<Rest>(rest)...};
}
} // namespace corex

#endif // COREX_UTILITY_MAKE_ARRAY_HPP