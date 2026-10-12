#ifndef COREX_PREPROCESSOR_FWD_HPP
#define COREX_PREPROCESSOR_FWD_HPP

#define COREX_FWD(...) static_cast<decltype(__VA_ARGS__) &&>(__VA_ARGS__)

#endif // COREX_PREPROCESSOR_FWD_HPP