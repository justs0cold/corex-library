#ifndef COREX_TRAIT_REMOVE_CV_HPP
#define COREX_TRAIT_REMOVE_CV_HPP

#include "corex/trait/remove_const.hpp"
#include "corex/trait/remove_volatile.hpp"

namespace corex {
template <typename T> struct remove_cv {
  using type = corex::remove_const_t<corex::remove_volatile_t<T>>;
};

template <typename T> using remove_cv_t = typename remove_cv<T>::type;
} // namespace corex

#endif // COREX_TRAIT_REMOVE_CV_HPP