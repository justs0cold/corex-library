#ifndef COREX_UTILITY_TUPLE_HPP
#define COREX_UTILITY_TUPLE_HPP

#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>

namespace corex {
template <typename... Ts> struct tuple {};

template <> struct tuple<> {
  constexpr tuple() noexcept = default;

  constexpr tuple(const tuple &) noexcept = default;
  constexpr tuple(tuple &&) noexcept = default;

  constexpr tuple &operator=(const tuple &) noexcept = default;
  constexpr tuple &operator=(tuple &&) noexcept = default;

  constexpr ~tuple() noexcept = default;
};

template <typename T, typename... Ts> struct tuple<T, Ts...> {
  T value;
  [[no_unique_address]]
  tuple<Ts...> rest;

  constexpr tuple() noexcept(std::is_nothrow_default_constructible_v<T> &&
                             (std::is_nothrow_default_constructible_v<Ts> && ...))
    requires(std::default_initializable<T> && (std::default_initializable<Ts> && ...))
      : value(), rest() {}

  template <typename U, typename... Us>
    requires(sizeof...(Ts) == sizeof...(Us))
  explicit(sizeof...(Us) == 0) constexpr tuple(U &&first, Us &&...remaining) noexcept(
      std::is_nothrow_constructible_v<T, U &&> && std::is_nothrow_constructible_v<tuple<Ts...>, Us &&...>)
      : value(std::forward<U>(first)), rest(std::forward<Us>(remaining)...) {}

  constexpr tuple(const tuple &) = default;
  constexpr tuple(tuple &&) = default;

  constexpr tuple &operator=(const tuple &) = default;
  constexpr tuple &operator=(tuple &&) = default;

  constexpr ~tuple() noexcept = default;

  template <std::size_t Idx> constexpr decltype(auto) get(this auto &&self) noexcept {
    if constexpr (Idx == 0) {
      return std::forward<decltype(self)>(self).value;
    } else {
      return std::forward<decltype(self)>(self).rest.template get<Idx - 1>();
    }
  }
};

template <typename... Ts> tuple(Ts &&...) -> tuple<std::unwrap_ref_decay_t<Ts>...>;

template <std::size_t Idx, typename T> struct tuple_element;

template <std::size_t Idx, typename... Ts> struct tuple_element<Idx, tuple<Ts...>> {
  using type = Ts...[Idx];
};

template <std::size_t Idx, typename T> using tuple_element_t = typename tuple_element<Idx, T>::type;

template <typename T> struct tuple_size;

template <typename... Ts> struct tuple_size<tuple<Ts...>> : std::integral_constant<std::size_t, sizeof...(Ts)> {};

template <typename T> inline constexpr std::size_t tuple_size_v = tuple_size<T>::value;

template <typename... Ts>
constexpr tuple<std::unwrap_ref_decay_t<Ts>...>
make_tuple(Ts &&...args) noexcept(std::is_nothrow_constructible_v<tuple<std::unwrap_ref_decay_t<Ts>...>, Ts &&...>) {
  return tuple<std::unwrap_ref_decay_t<Ts>...>(std::forward<Ts>(args)...);
}

template <typename... Ts> constexpr tuple<Ts &&...> forward_as_tuple(Ts &&...args) noexcept {
  return tuple<Ts &&...>(std::forward<Ts>(args)...);
}

namespace detail {
template <typename Target, typename... Ts>
struct count_occurrences : std::integral_constant<std::size_t, (std::is_same_v<Target, Ts> + ... + 0)> {};

template <typename Target, typename... Ts>
inline constexpr std::size_t count_occurrences_v = count_occurrences<Target, Ts...>::value;

template <typename T, typename... Ts>
  requires(detail::count_occurrences_v<T, Ts...> == 1)
constexpr std::size_t find_type_index() {
  return []<std::size_t... Idxs>(std::index_sequence<Idxs...>) {
    return ((std::is_same_v<T, Ts> ? Idxs : 0) + ... + 0);
  }(std::make_index_sequence<sizeof...(Ts)>{});
}

template <typename T1, typename T2> struct tuple_concat;

template <typename... Ts1, typename... Ts2> struct tuple_concat<corex::tuple<Ts1...>, corex::tuple<Ts2...>> {
  using type = corex::tuple<Ts1..., Ts2...>;
};

template <typename T1, typename T2> using tuple_concat_t = typename tuple_concat<T1, T2>::type;

template <typename Result, typename T1, typename T2, std::size_t... Idxs1, std::size_t... Idxs2>
constexpr Result expand_tuple(
    T1 &&t1, T2 &&t2, std::index_sequence<Idxs1...> /*unused*/,
    std::index_sequence<Idxs2...> /*unused*/) noexcept(noexcept(Result(std::forward<T1>(t1).template get<Idxs1>()...,
                                                                       std::forward<T2>(t2)
                                                                           .template get<Idxs2>()...))) {
  return Result(std::forward<T1>(t1).template get<Idxs1>()..., std::forward<T2>(t2).template get<Idxs2>()...);
}

template <typename T1, typename T2>
constexpr auto tuple_cat_impl(T1 &&t1, T2 &&t2) -> tuple_concat_t<std::remove_cvref_t<T1>, std::remove_cvref_t<T2>> {
  using concatenated_tuple = tuple_concat_t<std::remove_cvref_t<T1>, std::remove_cvref_t<T2>>;

  return expand_tuple<concatenated_tuple>(std::forward<T1>(t1), std::forward<T2>(t2),
                                          std::make_index_sequence<corex::tuple_size_v<std::remove_cvref_t<T1>>>{},
                                          std::make_index_sequence<corex::tuple_size_v<std::remove_cvref_t<T2>>>{});
}
} // namespace detail

template <std::size_t Idx, typename... Ts> constexpr decltype(auto) get(corex::tuple<Ts...> &t) {
  return std::forward<decltype(t)>(t).template get<Idx>();
}

template <std::size_t Idx, typename... Ts> constexpr decltype(auto) get(const corex::tuple<Ts...> &t) {
  return std::forward<decltype(t)>(t).template get<Idx>();
}

template <std::size_t Idx, typename... Ts> constexpr decltype(auto) get(corex::tuple<Ts...> &&t) {
  return std::move(t).template get<Idx>();
}

template <std::size_t Idx, typename... Ts> constexpr decltype(auto) get(const corex::tuple<Ts...> &&t) {
  return std::move(t).template get<Idx>();
}

template <typename U, typename... Ts>
  requires(detail::count_occurrences_v<U, Ts...> == 1)
constexpr decltype(auto) get(corex::tuple<Ts...> &t) {
  return std::forward<decltype(t)>(t).template get<detail::find_type_index<U, Ts...>()>();
}

template <typename U, typename... Ts>
  requires(detail::count_occurrences_v<U, Ts...> == 1)
constexpr decltype(auto) get(const corex::tuple<Ts...> &t) {
  return std::forward<decltype(t)>(t).template get<detail::find_type_index<U, Ts...>()>();
}

template <typename U, typename... Ts>
  requires(detail::count_occurrences_v<U, Ts...> == 1)
constexpr decltype(auto) get(corex::tuple<Ts...> &&t) {
  return std::move(t).template get<detail::find_type_index<U, Ts...>()>();
}

template <typename U, typename... Ts>
  requires(detail::count_occurrences_v<U, Ts...> == 1)
constexpr decltype(auto) get(const corex::tuple<Ts...> &&t) {
  return std::move(t).template get<detail::find_type_index<U, Ts...>()>();
}

template <typename T> constexpr decltype(auto) tuple_cat(T &&tuple) { return std::forward<T>(tuple); }

template <typename T1, typename T2, typename... Rest> constexpr auto tuple_cat(T1 &&t1, T2 &&t2, Rest &&...rest) {
  if constexpr (sizeof...(Rest) == 0) {
    return detail::tuple_cat_impl(std::forward<T1>(t1), std::forward<T2>(t2));
  } else {
    return corex::tuple_cat(detail::tuple_cat_impl(std::forward<T1>(t1), std::forward<T2>(t2)),
                            std::forward<Rest>(rest)...);
  }
}
} // namespace corex

template <typename... Ts> struct std::tuple_size<corex::tuple<Ts...>> : corex::tuple_size<corex::tuple<Ts...>> {};

template <std::size_t Idx, typename... Ts>
struct std::tuple_element<Idx, corex::tuple<Ts...>> : corex::tuple_element<Idx, corex::tuple<Ts...>> {};

#endif // COREX_UTILITY_TUPLE_HPP