#ifndef COREX_TRAIT_REMOVE_CONST_HPP
#define COREX_TRAIT_REMOVE_CONST_HPP

namespace corex {
template <typename T> struct remove_const {
  using type = T;
};

template <typename T> struct remove_const<const T> {
  using type = T;
};

template <typename T> using remove_const_t = typename remove_const<T>::type;
} // namespace corex

#endif // COREX_TRAIT_REMOVE_CONST_HPP