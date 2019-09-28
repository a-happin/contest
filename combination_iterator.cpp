#include <bits/stdc++.h>
#define FOR(i,b,e) for (common_type_t<decltype(b),decltype(e)> i = (b), i ## __end = (e); i < i ## __end; ++ i)
#define rep(i,n)   FOR (i, size_t{}, n)
#define ALL(x)     begin (x), end (x)
using namespace std;
using ll = int64_t;
constexpr ll inf = 2e18;

template <typename Iterator, typename F>
auto combination_call (Iterator first, Iterator last, F callback)
{
  FOR (j, first, last) FOR (i, first, j) callback (* i, * j);
}

auto main () -> int
{
  cin.tie (nullptr);
  ios::sync_with_stdio (false);

  vector <int> v (5);
  iota (ALL (v), 0);

  combination_call (ALL (v), [&] (auto x, auto y) {
    cout << "(" << x << ", " << y <<")" << endl;
  });
}
