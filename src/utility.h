#pragma once
#include <type_traits>

using size_t_ = unsigned int;
using nullptr_t_ = decltype(nullptr);

template <typename T>
using remove_reference_t_ = typename std::remove_reference<T>::type;

template <typename T>
decltype(auto) move_(T&& arg) {
  return static_cast<remove_reference_t_<T>&&>(arg);
}