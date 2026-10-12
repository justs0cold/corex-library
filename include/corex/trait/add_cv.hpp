#ifndef COREX_TRAIT_ADD_CV_HPP
#define COREX_TRAIT_ADD_CV_HPP

#include "corex/trait/add_const.hpp"
#include "corex/trait/add_volatile.hpp"

namespace corex {
template <typename T> struct add_cv {
  using type = corex::add_const_t<corex::add_volatile_t<T>>;
};

template <typename T> using add_cv_t = typename add_cv<T>::type;
} // namespace corex

#endif // COREX_TRAIT_ADD_CV_HPP