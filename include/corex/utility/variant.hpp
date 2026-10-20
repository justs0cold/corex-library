#ifndef COREX_UTILITY_VARIANT_HPP
#define COREX_UTILITY_VARIANT_HPP

#include <array>
#include <concepts>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <type_traits>

namespace corex {
namespace detail {
template <typename T, typename U = T>
concept Comparable = requires(T t, U u) {
  { t < u } -> std::convertible_to<bool>;
};
} // namespace detail

inline constexpr auto max(const auto &first, const auto &...args)
  requires(detail::Comparable<decltype(first), decltype(args)> && ...)
{
  auto result = first;
  ((result = (result < args) ? args : result), ...);
  return result;
}

template <typename T> static constexpr void destroy_type(std::byte *data) noexcept {
  std::destroy_at(reinterpret_cast<T *>(data));
}

template <typename... Ts> class variant {
public:
  constexpr variant() noexcept(std::is_nothrow_default_constructible_v<Ts...[0]>) : index(0) {
    std::construct_at(reinterpret_cast<Ts...[0] *>(storage.data()));
  }

  template <typename T>
    requires(!std::same_as<std::decay_t<T>, variant> && (... || std::same_as<std::decay_t<T>, Ts>))
  constexpr variant(T &&val) {
    constexpr std::size_t target_index = []<std::size_t... Is>(std::index_sequence<Is...>) {
      return ((std::same_as<std::decay_t<T>, Ts...[Is]> ? Is : 0) + ...);
    }(std::index_sequence_for<Ts...>{});

    index = target_index;
    std::construct_at(reinterpret_cast<Ts...[target_index] *>(storage.data()), std::forward<T>(val));
  }
  constexpr ~variant() { destroy_table[index](storage.data()); }

  template <std::size_t Idx>
  constexpr Ts...[Idx]& get() {
    if (index != Idx) {
      throw std::runtime_error("bad variant access");
    }
    return *reinterpret_cast<Ts...[Idx]*>(storage.data());
  }

  template <std::size_t Idx>
  constexpr const Ts...[Idx]& get() const {
    if (index != Idx) {
      throw std::runtime_error("bad variant access");
    }
    return *reinterpret_cast<const Ts...[Idx]*>(storage.data());
  }

private: 
  static constexpr std::size_t storage_size = max(sizeof(Ts)...);
  static constexpr std::size_t storage_align = max(alignof(Ts)...);

  alignas(storage_align) std::array<std::byte, storage_size> storage;
  std::size_t index;

  static constexpr inline void (*destroy_table[])(std::byte *) = {&destroy_type<Ts>...};
};
} // namespace corex

#endif // COREX_UTILITY_VARIANT_HPP