#pragma once

#include <gtest/gtest.h>

#include <chrono>
#include <functional>

#include <utils/non_loggable.hpp>
#include <utils/strong_typedef.hpp>

void RunInCoro(std::function<void()>, size_t worker_threads = 1);

inline void TestInCoro(std::function<void()> callback,
                       size_t worker_threads = 1) {
  RunInCoro(std::move(callback), worker_threads);
}

inline constexpr std::chrono::seconds kMaxTestWaitTime(20);

// gtest-specific serializers
namespace std::chrono {

inline void PrintTo(std::chrono::seconds s, std::ostream* os) {
  *os << s.count() << "s";
}

inline void PrintTo(std::chrono::milliseconds ms, std::ostream* os) {
  *os << ms.count() << "ms";
}

inline void PrintTo(std::chrono::microseconds us, std::ostream* os) {
  *os << us.count() << "us";
}

inline void PrintTo(std::chrono::nanoseconds ns, std::ostream* os) {
  *os << ns.count() << "ns";
}
}  // namespace std::chrono

namespace formats::json {

class Value;

void PrintTo(const Value&, std::ostream*);

}  // namespace formats::json

namespace utils {

template <class Tag, class T, StrongTypedefOps Ops>
void PrintTo(const StrongTypedef<Tag, T, Ops>& v, std::ostream* os) {
  ::testing::internal::UniversalTersePrint(v.GetUnderlying(), os);
}

}  // namespace utils

#ifdef __APPLE__
#define DISABLED_IN_MAC_OS_TEST_NAME(name) DISABLED_##name
#else
#define DISABLED_IN_MAC_OS_TEST_NAME(name) name
#endif

#ifdef _LIBCPP_VERSION
#define DISABLED_IN_LIBCPP_TEST_NAME(name) DISABLED_##name
#else
#define DISABLED_IN_LIBCPP_TEST_NAME(name) name
#endif
