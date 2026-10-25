#ifndef COREX_TRAIT_IS_POINTER_HPP
#define COREX_TRAIT_IS_POINTER_HPP

#include "corex/trait/integral_constant.hpp"

namespace corex {
template <typename T> struct is_pointer : false_type {};

template <typename T> struct is_pointer<T *> : true_type {};

template <typename T> struct is_pointer<T *const> : true_type {};

template <typename T> struct is_pointer<T *volatile> : true_type {};

template <typename T> struct is_pointer<T *const volatile> : true_type {};

template <typename T> inline constexpr bool is_pointer_v = is_pointer<T>::value;
} // namespace corex

#endif // COREX_TRAIT_IS_POINTER_HPP
