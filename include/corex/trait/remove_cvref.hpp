#ifndef COREX_TRAIT_REMOVE_CVREF_HPP
#define COREX_TRAIT_REMOVE_CVREF_HPP

#include "corex/trait/remove_cv.hpp"
#include "corex/trait/remove_reference.hpp"

namespace corex {
template <typename T> struct remove_cvref {
  using type = corex::remove_cv_t<corex::remove_reference_t<T>>;
};

template <typename T> using remove_cvref_t = typename remove_cvref<T>::type;
} // namespace corex

#endif // COREX_TRAIT_REMOVE_CVREF_HPP