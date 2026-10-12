#ifndef COREX_TRAIT_REMOVE_VOLATILE_HPP
#define COREX_TRAIT_REMOVE_VOLATILE_HPP

namespace corex {
template <typename T> struct remove_volatile {
  using type = T;
};

template <typename T> struct remove_volatile<volatile T> {
  using type = T;
};

template <typename T>
using remove_volatile_t = typename remove_volatile<T>::type;
} // namespace corex

#endif // COREX_TRAIT_REMOVE_VOLATILE_HPP