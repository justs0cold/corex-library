#ifndef COREX_TRAIT_ENABLE_IF_HPP
#define COREX_TRAIT_ENABLE_IF_HPP

namespace corex {
template <bool B, typename T = void> struct enable_if {};

template <typename T> struct enable_if<true, T> {
  using type = T;
};

template <bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;
} // namespace corex

#endif // COREX_TRAIT_ENABLE_IF_HPP