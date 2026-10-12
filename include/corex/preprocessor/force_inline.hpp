#ifndef COREX_PREPROCESSOR_FORCE_INLINE_HPP
#define COREX_PREPROCESSOR_FORCE_INLINE_HPP

#if defined(_MSC_VER)
#define COREX_FORCE_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#define COREX_FORCE_INLINE inline __attribute__((always_inline))
#else
#define COREX_FORCE_INLINE inline
#endif

#endif // COREX_PREPROCESSOR_FORCE_INLINE_HPP