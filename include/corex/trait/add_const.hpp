#ifndef COREX_TRAIT_ADD_CONST_HPP
#define COREX_TRAIT_ADD_CONST_HPP

namespace corex {
template <typename T> struct add_const {
  using type = const T;
};

template <typename T> struct add_const<T &> {
  using type = T &;
};

template <typename T> struct add_const<T &&> {
  using type = T &&;
};

template <typename T> using add_const_t = typename add_const<T>::type;
} // namespace corex

#endif // COREX_TRAIT_ADD_CONST_HPP