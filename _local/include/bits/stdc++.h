#pragma once
// bits/stdc++.h — includes all standard C++ headers (GCC compat for macOS)
#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <climits>
#include <cfloat>
#include <numeric>
#include <optional>
#include <variant>
#include <string_view>
#include <charconv>
#include <filesystem>

/* ---------------------------------------------------------------------
   GNU compatibility shims.
   The real Fastenal OA compiles with g++ 9.2.0 (libstdc++). This local
   practice build uses Apple clang (libc++), which lacks some GNU
   extensions competitive C++ leans on. Without these, code that is
   perfectly valid on the actual test fails here — the practice
   environment must not lie about what compiles.
   --------------------------------------------------------------------- */
#if defined(_LIBCPP_VERSION)
namespace __oa_gnu {
  template <class T> T gcd_(T a, T b) { while (b) { T t = a % b; a = b; b = t; }
                                        return a < 0 ? -a : a; }
  template <class T> T lcm_(T a, T b) { return b ? (a / gcd_(a, b)) * b : T(0); }
}
// libc++'s own headers are all included above, so these macros only ever
// rewrite the candidate's code, never the standard library's.
#define __gcd  __oa_gnu::gcd_
#define __lcm  __oa_gnu::lcm_
#endif
