#ifndef LOCAL_DUMP_HPP
#define LOCAL_DUMP_HPP

namespace local
{
  // utility
  template <typename F, typename Tuple, std::size_t ... Indices>
  inline constexpr auto apply_impl (F f, Tuple && t, std::index_sequence <Indices ...>) -> decltype (auto)
  {
    return f (std::get <Indices> (std::forward <Tuple> (t)) ...);
  }
  template <typename F, typename Tuple>
  inline constexpr auto apply (F f, Tuple && t) -> decltype (auto)
  {
    return apply_impl (f, std::forward <Tuple> (t), std::make_index_sequence <std::tuple_size <std::remove_reference_t <Tuple>>::value> {});
  }

  struct dump_t {
    using R = std::ostream &;
    R stream;
    template <typename T>
    inline auto operator () (const T & x) -> std::enable_if_t <std::is_integral <T>::value, R>
    {
      return stream << std::dec << x;
    }
    inline auto operator () (const std::nullptr_t &) -> R
    {
      return stream << "nullptr";
    }
    inline auto operator () (const bool & x) -> R
    {
      return stream << std::boolalpha << x;
    }
    inline auto operator () (const char & x) -> R
    {
      return stream << x;
    }
    template <typename T>
    inline auto operator () (const T & x) -> std::enable_if_t <std::is_floating_point <T>::value, R>
    {
      return stream << std::fixed << std::setprecision (15) << x;
    }
    template <typename T>
    inline auto operator () (const T * x) -> R
    {
      return stream << "pointer to " << x;
    }
    inline auto operator () (const char * x) -> R
    {
      return stream << std::quoted (x);
    }
    inline auto operator () (const std::string & x) -> R
    {
      return stream << std::quoted (x);
    }
    template <typename T, typename U>
    inline auto operator () (const std::pair <T, U> & x) -> R
    {
      stream << "(";
      operator () (x.first);
      stream << ", ";
      operator () (x.second);
      return stream << ")";
    }
    inline auto operator () (const std::tuple <> &) -> R
    {
      return stream << "()";
    }
    template <typename T, typename ... Ts>
    inline auto operator () (const std::tuple <T, Ts ...> & x) -> R
    {
      struct dummy_t {} dummy_v;
      stream << "(";
      apply ([&] (auto && first, auto && ... rest) {
        dummy_t dummy [] = {
          (static_cast <void> (operator () (first)), dummy_v),
          (static_cast <void> (stream << ", "), static_cast <void> (operator () (rest)), dummy_v) ...
        };
        static_cast <void> (dummy);
      }, x);
      return stream << ")";
    }
    template <std::size_t N>
    inline auto operator () (const char (& x) [N]) -> R
    {
      return stream << std::quoted (x);
    }
    template <typename T, std::size_t N>
    inline auto operator () (const T (& x) [N]) -> R
    {
      stream << "[";
      auto first = std::begin (x);
      auto last = std::end (x);
      if (first != last) operator () (* first ++);
      while (first != last)
      {
        stream << ", ";
        operator () (* first ++);
      }
      return stream << "]";
    }
    template <typename T, std::size_t N>
    inline auto operator () (const std::array <T, N> & x) -> R
    {
      stream << "[";
      auto first = std::begin (x);
      auto last = std::end (x);
      if (first != last) operator () (* first ++);
      while (first != last)
      {
        stream << ", ";
        operator () (* first ++);
      }
      return stream << "]";
    }
    template <typename T>
    inline auto operator () (const std::initializer_list <T> & x) -> R
    {
      stream << "[";
      auto first = std::begin (x);
      auto last = std::end (x);
      if (first != last) operator () (* first ++);
      while (first != last)
      {
        stream << ", ";
        operator () (* first ++);
      }
      return stream << "]";
    }
    template <typename T>
    inline auto operator () (const std::vector <T> & x) -> R
    {
      stream << "[";
      auto first = std::begin (x);
      auto last = std::end (x);
      if (first != last) operator () (* first ++);
      while (first != last)
      {
        stream << ", ";
        operator () (* first ++);
      }
      return stream << "]";
    }
    template <typename T>
    inline auto operator () (const std::list <T> & x) -> R
    {
      stream << "[";
      auto first = std::begin (x);
      auto last = std::end (x);
      if (first != last) operator () (* first ++);
      while (first != last)
      {
        stream << ", ";
        operator () (* first ++);
      }
      return stream << "]";
    }
    template <typename T>
    inline auto operator () (const std::forward_list <T> & x) -> R
    {
      stream << "[";
      auto first = std::begin (x);
      auto last = std::end (x);
      if (first != last) operator () (* first ++);
      while (first != last)
      {
        stream << ", ";
        operator () (* first ++);
      }
      return stream << "]";
    }
    template <typename T>
    inline auto operator () (const std::set <T> & x) -> R
    {
      stream << "{";
      auto first = std::begin (x);
      auto last = std::end (x);
      if (first != last) operator () (* first ++);
      while (first != last)
      {
        stream << ", ";
        operator () (* first ++);
      }
      return stream << "}";
    }
    template <typename T>
    inline auto operator () (const std::multiset <T> & x) -> R
    {
      stream << "{";
      auto first = std::begin (x);
      auto last = std::end (x);
      if (first != last) operator () (* first ++);
      while (first != last)
      {
        stream << ", ";
        operator () (* first ++);
      }
      return stream << "}";
    }
    template <typename T>
    inline auto operator () (const std::unordered_set <T> & x) -> R
    {
      stream << "{";
      auto first = std::begin (x);
      auto last = std::end (x);
      if (first != last) operator () (* first ++);
      while (first != last)
      {
        stream << ", ";
        operator () (* first ++);
      }
      return stream << "}";
    }
    template <typename T>
    inline auto operator () (const std::unordered_multiset <T> & x) -> R
    {
      stream << "{";
      auto first = std::begin (x);
      auto last = std::end (x);
      if (first != last) operator () (* first ++);
      while (first != last)
      {
        stream << ", ";
        operator () (* first ++);
      }
      return stream << "}";
    }
    template <typename T, typename U>
    inline auto operator () (const std::map <T, U> & x) -> R
    {
      auto f = [&] (const auto & p) {
        operator () (p.first);
        stream << ": ";
        operator () (p.second);
      };
      stream << "{";
      auto first = std::begin (x);
      auto last = std::end (x);
      if (first != last) f (* first ++);
      while (first != last)
      {
        stream << ", ";
        f (* first ++);
      }
      return stream << "}";
    }
    template <typename T, typename U>
    inline auto operator () (const std::multimap <T, U> & x) -> R
    {
      auto f = [&] (const auto & p) {
        operator () (p.first);
        stream << ": ";
        operator () (p.second);
      };
      stream << "{";
      auto first = std::begin (x);
      auto last = std::end (x);
      if (first != last) f (* first ++);
      while (first != last)
      {
        stream << ", ";
        f (* first ++);
      }
      return stream << "}";
    }
    template <typename T, typename U>
    inline auto operator () (const std::unordered_map <T, U> & x) -> R
    {
      auto f = [&] (const auto & p) {
        operator () (p.first);
        stream << ": ";
        operator () (p.second);
      };
      stream << "{";
      auto first = std::begin (x);
      auto last = std::end (x);
      if (first != last) f (* first ++);
      while (first != last)
      {
        stream << ", ";
        f (* first ++);
      }
      return stream << "}";
    }
    template <typename T, typename U>
    inline auto operator () (const std::unordered_multimap <T, U> & x) -> R
    {
      auto f = [&] (const auto & p) {
        operator () (p.first);
        stream << ": ";
        operator () (p.second);
      };
      stream << "{";
      auto first = std::begin (x);
      auto last = std::end (x);
      if (first != last) f (* first ++);
      while (first != last)
      {
        stream << ", ";
        f (* first ++);
      }
      return stream << "}";
    }
    inline auto operator () (void) -> R
    {
      return stream << "void";
    }
  };
} // namespace local

#define dump(x) local::dump_t {std::cerr << "[" << __FILE__ << "][" << __func__ << ":" << __LINE__ << "] " #x " = "} (x) << std::endl;
#endif
