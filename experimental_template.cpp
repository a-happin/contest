#include <bits/stdc++.h>
#include <boost/range/irange.hpp>
//#define rep(i,n)    for (size_t i = 0, i ## __len = (n); i < i ## __len; ++ i)
#define FOR(i,b,e)  for (common_type_t <decltype (b), decltype (e)> i = (b), i ## __end = (e); i < i ## __end; ++ i)
#define FORR(i,b,e) for (common_type_t <decltype (b), decltype (e)> i = (e), i ## __begin = (b); i -- > i ## __begin;)
#define rep(i,n)    FOR (i, 0_zu, n)
#define ALL(x)      begin (x), end (x)

#define RECURSIVE_LAMBDA(...)	[&] (auto self, __VA_ARGS__)
#define RECURSIVE_CALL(...)	self (self, __VA_ARGS__)
#define INVOKE(f,...)		f (f, __VA_ARGS__)

using namespace std;
using zu = size_t;
using ll = int64_t;
using vertex_t = zu;
using weight_t = ll;
using edge_t = tuple <vertex_t, vertex_t, weight_t>;
using graph_t = vector <vector <vertex_t>>;

constexpr ll inf = 0xde0b6b43b9aca00;
constexpr ll MOD = 1000000007;
constexpr auto operator"" _zu (unsigned long long x) noexcept { return static_cast <size_t> (x); }
constexpr auto operator"" _ll (unsigned long long x) noexcept { return static_cast <int64_t> (x); }

inline auto irange (size_t n) noexcept { return boost::irange (0_zu, n); }
template <typename Iterator>
inline auto cumulative_sum (Iterator first, Iterator last)
{
  using T = typename iterator_traits <Iterator>::value_type;
  vector <T> res;
  res.emplace_back ();
  partial_sum (first, last, back_inserter (res));
  return res;
}

auto main () -> int
{
  cin.tie (nullptr);
  ios::sync_with_stdio (false);

  constexpr auto n = 10_zu;
  rep (i, 10) static_assert (is_same <decltype (i), size_t> {}, "");
  for (auto i : irange (n)) static_assert (is_same <decltype (i), size_t> {}, "");
  for (auto i : boost::irange (1_zu, n + 1)) static_assert (is_same <decltype (i), size_t> {}, "");

}
