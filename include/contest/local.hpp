#ifndef CONTEST_LOCAL_HPP
#define CONTEST_LOCAL_HPP
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <type_traits>
#include <tuple>
#include <array>
#include <vector>
#include <list>
#include <set>
#include <iterator>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstdint>

namespace local
{
  // type traits
  template <typename T, typename U>
  inline constexpr auto strict_type_check (U && x) noexcept -> T
  {
    static_assert (std::is_same <T, U> {}, "strict_type_check error");
    return std::forward <U> (x);
  }


  // constant
  constexpr auto EPS = 1e-9;
  constexpr auto MOD = static_cast <std::int64_t> (1e9) + 7;


  // supress warning
  inline auto maybe_unused ()
  {
    static_cast <void> (& EPS);
    static_cast <void> (& MOD);
  }


  // prototype
  inline auto print (std::ostream &, const std::string &) -> decltype (auto);

  inline auto print (std::ostream &, const char *) -> decltype (auto);

  template <typename T, typename U>
  inline auto print (std::ostream &, const std::pair <T, U> &) -> decltype (auto);

  template <typename ... Ts>
  inline auto print (std::ostream &, const std::tuple <Ts ...> &) -> decltype (auto);

  template <typename T, size_t N>
  inline auto print (std::ostream &, const T (&) [N]) -> decltype (auto);

  template <typename T, size_t N>
  inline auto print (std::ostream &, const std::array <T, N> &) -> decltype (auto);

  template <typename T>
  inline auto print (std::ostream &, const std::initializer_list <T> &) -> decltype (auto);

  template <typename T>
  inline auto print (std::ostream &, const std::vector <T> &) -> decltype (auto);

  template <typename T>
  inline auto print (std::ostream &, const std::list <T> &) -> decltype (auto);

  template <typename T>
  inline auto print (std::ostream &, const std::set <T> &) -> decltype (auto);

  template <typename T, typename U>
  inline auto print (std::ostream &, const std::map <T, U> &) -> decltype (auto);

  template <typename T>
  inline auto print (std::ostream &, const T &) -> decltype (auto);


  // utility
  template <typename F, typename Tuple, size_t ... Indices>
  inline constexpr auto apply_impl (F f, Tuple && t, std::index_sequence <Indices ...>) -> decltype (auto)
  {
    return f (std::get <Indices> (std::forward <Tuple> (t)) ...);
  }

  template <typename F, typename Tuple>
  inline constexpr auto apply (F f, Tuple && t) -> decltype (auto)
  {
    return apply_impl (f, std::forward <Tuple> (t), std::make_index_sequence <std::tuple_size <std::remove_reference_t <Tuple>>::value> {});
  }

  inline auto print_tuple_impl (std::ostream & stream) -> decltype (auto)
  {
    return stream;
  }

  template <typename T, typename ... Ts>
  inline auto print_tuple_impl (std::ostream & stream, const T & x, const Ts & ... xs) -> decltype (auto)
  {
    struct dummy_t {} dummy_v;
    dummy_t dummy [] {(static_cast <void> (print (stream, x)), dummy_v), (static_cast <void> (print (stream << ", ", xs)), dummy_v) ...};
    static_cast <void> (dummy);
    return stream;
  }

  template <typename Iterator>
  inline auto print_list_impl (std::ostream & stream, Iterator begin, Iterator end) -> decltype (auto)
  {
    if (begin != end)
    {
      print (stream, * begin ++);
      while (begin != end)
      {
        print (stream << ", ", * begin ++);
      }
    }
    return stream;
  }


  // for debug log
  inline auto print (std::ostream & stream, const std::string & s) -> decltype (auto)
  {
    stream << '"' << s << '"';
    return stream;
  }

  inline auto print (std::ostream & stream, const char * s) -> decltype (auto)
  {
    stream << '"' << s << '"';
    return stream;
  }

  template <typename T, typename U>
  inline auto print (std::ostream & stream, const std::pair <T, U> & p) -> decltype (auto)
  {
    stream << "(";
    print_tuple_impl (stream, p.first, p.second);
    stream << ")";
    return stream;
  }

  template <typename ... Ts>
  inline auto print (std::ostream & stream, const std::tuple <Ts ...> & t) -> decltype (auto)
  {
    stream << "(";
    apply ([&] (auto & ... xs) {
      print_tuple_impl (stream, xs ...);
    }, t);
    stream << ")";
    return stream;
  }

  template <typename T, size_t N>
  inline auto print (std::ostream & stream, const T (& a) [N]) -> decltype (auto)
  {
    stream << "[";
    print_list_impl (stream, a, a + N);
    stream << "]";
    return stream;
  }

  template <typename T, size_t N>
  inline auto print (std::ostream & stream, const std::array <T, N> & a) -> decltype (auto)
  {
    stream << "[";
    print_list_impl (stream, a.begin (), a.end ());
    stream << "]";
    return stream;
  }

  template <typename T>
  inline auto print (std::ostream & stream, const std::initializer_list <T> & l) -> decltype (auto)
  {
    stream << "[";
    print_list_impl (stream, l.begin (), l.end ());
    stream << "]";
    return stream;
  }

  template <typename T>
  inline auto print (std::ostream & stream, const std::vector <T> & v) -> decltype (auto)
  {
    stream << "[";
    print_list_impl (stream, v.begin (), v.end ());
    stream << "]";
    return stream;
  }

  template <typename T>
  inline auto print (std::ostream & stream, const std::list <T> & l) -> decltype (auto)
  {
    stream << "[";
    print_list_impl (stream, l.begin (), l.end ());
    stream << "]";
    return stream;
  }

  template <typename T>
  inline auto print (std::ostream & stream, const std::set <T> & s) -> decltype (auto)
  {
    stream << "{";
    print_list_impl (stream, s.begin (), s.end ());
    stream << "}";
    return stream;
  }

  template <typename T, typename U>
  inline auto print (std::ostream & stream, const std::map <T, U> & m) -> decltype (auto)
  {
    stream << "{";
    print_list_impl (stream, m.begin (), m.end ());
    stream << "}";
    return stream;
  }

  template <typename T>
  inline auto print (std::ostream & stream, const T & x) -> decltype (auto)
  {
    return stream << x;
  }

  template <typename T>
  inline auto println (std::ostream & stream, const T & x) -> decltype (auto)
  {
    return print (stream, x) << std::endl;
  }

} // namespace local

#define LOG(x) do {local::println (std::cerr << fixed << boolalpha << #x " = ", x);} while (false)


#endif

