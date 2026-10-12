#ifndef COREX_TRAIT_CONDITIONAL_HPP
#define COREX_TRAIT_CONDITIONAL_HPP

namespace corex {
template <bool B, typename T, typename F> struct conditional {
  using type = T;
};

template <typename T, typename F> struct conditional<false, T, F> {
  using type = F;
};

template <bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;
} // namespace corex

#endif // COREX_TRAIT_CONDITIONAL_HPP