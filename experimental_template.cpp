#include <bits/stdc++.h>
#include <boost/range/irange.hpp>
//#define rep(i,n)    for (size_t i = 0, i ## __len = (n); i < i ## __len; ++ i)
#define FOR(i,b,e)  for (common_type_t <decltype (b), decltype (e)> i = (b), i ## __end = (e); i < i ## __end; ++ i)
#define FORR(i,b,e) for (common_type_t <decltype (b), decltype (e)> i = (e), i ## __begin = (b); i -- > i ## __begin;)
#define rep(i,n)    FOR (i, size_t {0}, n)
#define ALL(x)      begin (x), end (x)
using namespace std;
using ll = int64_t;
using weight_t = ll;
using edge_t = tuple <size_t, size_t, weight_t>;
using graph_t = vector <vector <size_t>>;
constexpr auto operator"" _z  (unsigned long long x) noexcept { return static_cast <size_t> (x); }
constexpr auto operator"" _ll (unsigned long long x) noexcept { return static_cast <ll> (x); }
constexpr ll inf = 0xde0b6b43b9aca00;
constexpr ll MOD = 1000000007;

template <typename T, typename U>
inline constexpr auto max (T && x, U && y) noexcept
{
  using V = common_type_t <T, U>;
  return std::max (static_cast <V> (x), static_cast <V> (y));
}
template <typename T, typename U>
inline auto irange (T && b, U && e) noexcept
{
  using V = common_type_t <T, U>;
  return boost::irange (static_cast <V> (b), static_cast <V> (e));
}
inline auto irange_n (size_t n) noexcept { return boost::irange <size_t> (0, n); }

auto main () -> int
{
  cin.tie (nullptr);
  ios::sync_with_stdio (false);

  rep (i, 10) static_assert (is_same <decltype (i), size_t> {}, "");
}
