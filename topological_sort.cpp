#include <bits/stdc++.h>
#define FOR(i,b,e) for (common_type_t<decltype(b),decltype(e)> i = (b), i ## __end = (e); i < i ## __end; ++ i)
#define rep(i,n)   FOR (i, size_t{}, n)
#define ALL(x)     begin (x), end (x)
using namespace std;
using ll = int64_t;
constexpr ll inf = 2e18;

template <typename Graph>
inline auto topological_sort (const Graph & g)
{
  using vertex_t = size_t;
  enum class flag_t : unsigned char { YET, VISITED, DONE };
  auto n = g.size ();
  vector <flag_t> visited (n, flag_t::YET);
  vector <vertex_t> res;
  auto res_ite = back_inserter (res);
  auto dfs = [&] (auto self, auto && now) {
    switch (visited [now])
    {
    case flag_t::DONE:
      return;
    case flag_t::VISITED:
      throw runtime_error ("Error in topological_sort: The graph must be DAG.");
    }
    visited [now] = flag_t::VISITED;
    for (auto && to : g [now])
    {
      self (self, to);
    }
    * res_ite ++ = now;
    visited [now] = flag_t::DONE;
  };
  rep (i, n) dfs (dfs, i);
  reverse (ALL (res));
  return res;
}

template <typename Graph, typename Container>
inline auto topological_sort_generic (const Graph & g, const Container & vertices)
{
  using vertex_t = size_t;
  enum class flag_t : unsigned char { YET, VISITED, DONE };
  auto n = vertices.size ();
  vector <flag_t> visited (n, flag_t::YET);
  vector <vertex_t> res;
  auto res_ite = back_inserter (res);
  auto dfs = [&] (auto self, auto && now) {
    switch (visited [now])
    {
    case flag_t::DONE:
      return;
    case flag_t::VISITED:
      throw runtime_error ("Error in topological_sort: The graph must be DAG.");
    }
    visited [now] = flag_t::VISITED;
    for (auto && to : g [now])
    {
      self (self, to);
    }
    * res_ite ++ = now;
    visited [now] = flag_t::DONE;
  };
  for (auto && i : vertices) dfs (dfs, i);
  reverse (ALL (res));
  return res;
}

template <typename Graph, typename Iterator>
inline auto topological_sort_generic (const Graph & g, Iterator first, Iterator last)
{
  using vertex_t = size_t;
  enum class flag_t : unsigned char { YET, VISITED, DONE };
  auto n = distance (first, last);
  vector <flag_t> visited (n, flag_t::YET);
  vector <vertex_t> res;
  auto res_ite = back_inserter (res);
  auto dfs = [&] (auto self, auto && now) {
    switch (visited [now])
    {
    case flag_t::DONE:
      return;
    case flag_t::VISITED:
      throw runtime_error ("Error in topological_sort: The graph must be DAG.");
    }
    visited [now] = flag_t::VISITED;
    for (auto && to : g [now])
    {
      self (self, to);
    }
    * res_ite ++ = now;
    visited [now] = flag_t::DONE;
  };
  FOR (ite, first, last) dfs (dfs, * ite);
  reverse (ALL (res));
  return res;
}

auto main () -> int
{
  cin.tie (nullptr);
  ios::sync_with_stdio (false);

  
}
