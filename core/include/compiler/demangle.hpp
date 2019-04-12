#pragma once

#include <chrono>
#include <string>
#include <typeindex>

namespace compiler {

std::string GetTypeName(const std::type_index& type);

namespace detail {

template <class T>
struct TypeNameHelper {
  static std::string Get() { return GetTypeName(typeid(T)); }
};

template <>
struct TypeNameHelper<std::string> {
  static std::string Get() { return "std::string"; }
};

template <>
struct TypeNameHelper<std::chrono::nanoseconds> {
  static std::string Get() { return "std::chrono::nanoseconds"; }
};

template <>
struct TypeNameHelper<std::chrono::microseconds> {
  static std::string Get() { return "std::chrono::microseconds"; }
};

template <>
struct TypeNameHelper<std::chrono::milliseconds> {
  static std::string Get() { return "std::chrono::milliseconds"; }
};

template <>
struct TypeNameHelper<std::chrono::seconds> {
  static std::string Get() { return "std::chrono::seconds"; }
};

template <>
struct TypeNameHelper<std::chrono::minutes> {
  static std::string Get() { return "std::chrono::minutes"; }
};

template <>
struct TypeNameHelper<std::chrono::hours> {
  static std::string Get() { return "std::chrono::hours"; }
};

template <>
struct TypeNameHelper<std::chrono::steady_clock::time_point> {
  static std::string Get() { return "std::chrono::steady_clock::time_point"; }
};

template <>
struct TypeNameHelper<std::chrono::system_clock::time_point> {
  static std::string Get() { return "std::chrono::system_clock::time_point"; }
};

}  // namespace detail

// GetTypeName(typeidT)) outputs the type, not the alias. For std::chrono
// functions it gives unreadable results:
//     std::chrono::duration<long, std::ratio<1l, 1l> > - it's `seconds`
//
// The `GetTypeName<T>()` provides a more readable output.
template <typename T>
std::string GetTypeName() {
  return detail::TypeNameHelper<T>::Get();
}
}  // namespace compiler