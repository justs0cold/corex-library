#ifndef COREX_TRAIT_REMOVE_REFERENCE_HPP
#define COREX_TRAIT_REMOVE_REFERENCE_HPP

namespace corex {
template <typename T> struct remove_reference {
  using type = T;
};

template <typename T> struct remove_reference<T &> {
  using type = T;
};

template <typename T> struct remove_reference<T &&> {
  using type = T;
};

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;
} // namespace corex

#endif // COREX_TRAIT_REMOVE_REFERENCE_HPP