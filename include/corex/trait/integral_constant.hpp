#ifndef COREX_TRAIT_INTEGRAL_CONSTANT_HPP
#define COREX_TRAIT_INTEGRAL_CONSTANT_HPP

namespace corex {
template <typename T, T v> struct integral_constant {
  static constexpr T value = v;
  using value_type = T;
  using type = integral_constant;
  constexpr operator value_type() const noexcept { return value; }
  [[nodiscard]] constexpr value_type operator()() const noexcept {
    return value;
  }
};

using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

template <bool B> using bool_constant = integral_constant<bool, B>;
} // namespace corex

#endif // COREX_TRAIT_INTEGRAL_CONSTANT_HPP