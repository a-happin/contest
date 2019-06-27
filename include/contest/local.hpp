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
#include <map>
#include <algorithm>
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
  template <typename T>
  inline auto print (std::ostream &, const T &) -> decltype (auto);
  inline auto print (std::ostream &, const std::string &) -> decltype (auto);
  inline auto print (std::ostream &, const char *) -> decltype (auto);


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

  template <typename T, typename ... Ts>
  inline auto print_tuple_impl (std::ostream & stream, const T & x, const Ts & ... xs) -> decltype (auto)
  {
    int dummy [] {(static_cast <void> (print (stream, x)), 0), (static_cast <void> (stream << ", "), static_cast <void> (print (stream, xs)), 0) ...};
    static_cast <void> (dummy);
    return stream;
  }


  // operator overload
  template <typename T, typename U>
  inline auto operator << (std::ostream & stream, const std::pair <T, U> & p) -> decltype (auto)
  {
    stream << "(";
    return print_tuple_impl (stream, p.first, p.second) << ")";
  }

  template <typename ... Ts>
  inline auto operator << (std::ostream & stream, const std::tuple <Ts ...> & t) -> decltype (auto)
  {
    stream << "(";
    apply ([&] (auto && ... xs) {
      print_tuple_impl (stream, xs ...);
    }, t);
    return stream << ")";
  }

  template <typename T, size_t N>
  inline auto operator << (std::ostream & stream, const std::array <T, N> & a) -> decltype (auto)
  {
    stream << "[";
    apply ([&] (const auto & ... xs) {
      print_tuple_impl (stream, xs ...);
    }, a);
    return stream << "]";
  }

  template <typename T>
  inline auto operator << (std::ostream & stream, const std::vector <T> & v) -> decltype (auto)
  {
    stream << "[";
    if (! v.empty ())
    {
      auto ite = v.begin ();
      print (stream, * ite);
      for (++ ite; ite != v.end (); ++ ite)
      {
        stream << ", ";
        print (stream, * ite);
      }
    }
    return stream << "]";
  }

  template <typename T>
  inline auto operator << (std::ostream & stream, const std::list <T> & v) -> decltype (auto)
  {
    stream << "[";
    if (! v.empty ())
    {
      auto ite = v.begin ();
      print (stream, * ite);
      for (++ ite; ite != v.end (); ++ ite)
      {
        stream << ", ";
        print (stream, * ite);
      }
    }
    return stream << "]";
  }

  template <typename T>
  inline auto operator << (std::ostream & stream, const std::set <T> & s) -> decltype (auto)
  {
    stream << "{";
    if (! s.empty ())
    {
      auto ite = s.begin ();
      print (stream, * ite);
      for (++ ite; ite != s.end (); ++ ite)
      {
        stream << ", ";
        print (stream, * ite);
      }
    }
    return stream << "}";
  }

  template <typename T, typename U>
  inline auto operator << (std::ostream & stream, const std::map <T, U> & m) -> decltype (auto)
  {
    stream << "{";
    if (! m.empty ())
    {
      auto ite = m.begin ();
      print (stream, ite -> first) << ": ";
      print (stream, ite -> second);
      for (++ ite; ite != m.end (); ++ ite)
      {
        stream << ", ";
        print (stream, ite -> first) << ": ";
        print (stream, ite -> second);
      }
    }
    return stream << "}";
  }


  // debug log
  template <typename T>
  inline auto print (std::ostream & stream, const T & x) -> decltype (auto)
  {
    return stream << x;
  }

  inline auto print (std::ostream & stream, const std::string & x) -> decltype (auto)
  {
    return stream << '"' << x << '"';
  }

  inline auto print (std::ostream & stream, const char * x) -> decltype (auto)
  {
    return stream << '"' << x << '"';
  }

  template <typename T>
  inline auto println (std::ostream & stream, const T & x) -> decltype (auto)
  {
    return print (stream, x) << '\n';
  }



} // namespace local

#define LOG(x) do {std::cerr << #x " = "; local::println (std::cerr, (x));} while (false)


#endif

