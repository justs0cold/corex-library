#ifndef COREX_TRAIT_ADD_LVALUE_REFERENCE_HPP
#define COREX_TRAIT_ADD_LVALUE_REFERENCE_HPP

namespace corex {
template <typename T> struct add_lvalue_reference {
  using type = T &;
};

template <> struct add_lvalue_reference<void> {
  using type = void;
};

template <> struct add_lvalue_reference<const void> {
  using type = const void;
};

template <> struct add_lvalue_reference<volatile void> {
  using type = volatile void;
};

template <> struct add_lvalue_reference<const volatile void> {
  using type = const volatile void;
};

template <typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
} // namespace corex

#endif // COREX_TRAIT_ADD_LVALUE_REFERENCE_HPP