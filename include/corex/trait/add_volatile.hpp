#ifndef COREX_TRAIT_ADD_VOLATILE_HPP
#define COREX_TRAIT_ADD_VOLATILE_HPP

namespace corex {
template <typename T> struct add_volatile {
  using type = volatile T;
};

template <typename T> struct add_volatile<T &> {
  using type = T &;
};

template <typename T> struct add_volatile<T &&> {
  using type = T &&;
};

template <typename T> using add_volatile_t = typename add_volatile<T>::type;
} // namespace corex

#endif // COREX_TRAIT_ADD_VOLATILE_HPP