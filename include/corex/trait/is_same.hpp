#ifndef COREX_TRAIT_IS_SAME_HPP
#define COREX_TRAIT_IS_SAME_HPP

#include "corex/trait/integral_constant.hpp"

namespace corex {
template <typename, typename> struct is_same : false_type {};

template <typename T> struct is_same<T, T> : true_type {};

template <typename T, typename U>
inline constexpr bool is_same_v = is_same<T, U>::value;
} // namespace corex

#endif // COREX_TRAIT_IS_SAME_HPP