#include <bits/stdc++.h>

#ifdef LOCAL
  #include <contest/local.hpp>
#else
  #define LOG(...) do {} while (false)
#endif

#define REP(i,n) for (decay_t <decltype (n)> i = 0, i ## __len = (n); i < i ## __len; ++ i)
#define ALL(x) (x).begin (), (x).end ()

using namespace std;

template <typename T>
inline constexpr auto gcd (T m, T n) noexcept -> T
{
  return n == 0 ? m : gcd (n, m % n);
}

template <typename T>
inline constexpr auto lcm (T m, T n) noexcept -> T
{
  return m / gcd (m, n) * n;
}

template <typename Iterator>
inline auto print_list_impl (ostream & stream, Iterator begin, Iterator end, const char * delimiter = " ") -> decltype (auto)
{
  auto ite = begin;
  if (ite != end)
  {
    stream << * ite ++;
    while (ite != end)
    {
      stream << delimiter << * ite ++;
    }
  }
  return stream;
}


namespace detail
{
  template <typename Iterator, typename F, typename T>
  inline auto combination (Iterator begin, Iterator end, unsigned r, F callback, vector <T> & res) -> void
  {
    if (r == 0u)
    {
      callback (res);
    }
    else
    {
      for (auto ite = begin; ite < end; ++ ite)
      {
        res.push_back (cref (* ite));
        combination (next (ite), end, r - 1, callback, res);
        res.pop_back ();
      }
    }
  }
} // namespace detail

template <typename Iterator, typename F>
inline auto combination (Iterator begin, Iterator end, unsigned r, F callback)
{
  using t = reference_wrapper <add_const_t <decay_t <decltype (* begin)>>>;
  vector <t> res;
  return detail::combination (begin, end, r, callback, res);
}

auto main () -> int
{
  cin.tie (nullptr);
  ios::sync_with_stdio (false);
  cout << fixed << boolalpha;

  vector <int> v {1,2,3,4,45,5,6,4};

  double pi [] = {3.14159, 2653589, 79};

  map <int, string> m;

  m.emplace (0, "hoge");
  m.emplace (1, "fooo");
  m.emplace (-2, "ayo");
  m.emplace (32, "figa");

  tuple <int, bool, long double> t = make_tuple (1, false, 423.44);

  LOG (v);
  LOG (pi);
  LOG (m);
  LOG (true);

  LOG (t);

  combination (pi, pi + 3, 2, [&] (auto && res) {
    LOG (res);
  });
}

