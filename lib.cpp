// 全部乗せ
#include <bits/stdc++.h>

// 型推論for
#define FOR(i,b,e) for (common_type_t <decltype (b), decltype (e)> i = (b), i ## __end = (e); i < i ## __end; ++ i)

// コードが短い方
//#define FOR(i,b,e) for (decay_t <decltype (true ? (b) : (e))> i = (b), i ## __end = (e); i < i ## __end; ++ i)

// repeat
#define rep(i,n) for (decay_t <decltype (n)> i = 0, i ## __len = (n); i < i ## __len; ++ i)

// repeat 1-indexed
#define rep1(i,n) for (decay_t <decltype (n)> i = 1, i ## __len = (n); i <= i ## __len; ++ i)

// repeat reverse
#define repr(i,n) for (auto i = (n); i --;)

// repeat 1-indexed reverse
#define rep1r(i,n) for (auto i = (n); i > 0; -- i)

// iterator pair
#define ALL(x) begin (x), end (x)

// デバッグ用
#define dump(x) cerr << #x " = " << boolalpha << (x) << endl;

// おまじない
using namespace std;


// とてもおおきい (dp初期化用)
template <typename T = int64_t>
static constexpr auto inf = static_cast <T> (0x0de0b6b43b9aca00);

// とてもちいさい (double比較用)
static constexpr auto EPS = 1e-9;

// 最大値更新
template <typename T, typename U>
inline constexpr auto update_max (T & a, U && b)
{
  return a < b ? static_cast <void> (a = forward <U> (b)), true : false;
}

// 最小値更新
template <typename T, typename U>
inline constexpr auto update_min (T & a, U && b)
{
  return a > b ? static_cast <void> (a = forward <U> (b)), true : false;
}

// 最大の要素
template <typename Iterator>
inline constexpr auto max_of (Iterator first, Iterator last) -> decltype (auto)
{
  return first != last ? * max_element (first, last) : throw out_of_range ("max_of");
}

// 最小の要素
template <typename Iterator>
inline constexpr auto min_of (Iterator first, Iterator last) -> decltype (auto)
{
  return first != last ? * min_element (first, last) : throw out_of_range ("min_of");
}

// 合計
template <typename Iterator>
inline auto sum_of (Iterator first, Iterator last)
{
  return accumulate (first, last, typename iterator_traits <Iterator>::value_type {});
}

// 累積和生成
// res [i] = 左から要素をi個足したときの合計
template <typename Iterator>
inline auto cumulative_sum (Iterator first, Iterator last)
{
  using T = typename iterator_traits <Iterator>::value_type;
  vector <T> res (size_t {1}, T {});
  partial_sum (first, last, back_inserter (res));
  return res;
}

// 最大公約数
template <typename T>
inline constexpr auto gcd (T m, T n) noexcept -> T
{
  return n == 0 ? abs (m) : gcd (n, m % n);
}

// 最小公倍数
template <typename T>
inline constexpr auto lcm (T m, T n) noexcept -> T
{
  auto gcd_ = gcd (m, n);
  return gcd_ == 0 ? 0 : m / gcd_ * n;
}

// 約数列挙
template <typename T>
inline auto enumerate_divisors (T n)
{
  set <T> res;
  for (T i = 1; i * i <= n; ++ i)
  {
    if (n % i == 0)
    {
      res.insert (i);
      res.insert (n / i);
    }
  }
  return res;
}

// (mod M) の世界
template <int64_t M>
struct Mod {
  using T = decltype (M);
  T n;
  static_assert (M != 0, "");
  constexpr Mod () noexcept : n {0} {}
  constexpr Mod (const T & v) noexcept : n {v >= 0 ? v % M : (v % M + M) % M} {}
  constexpr operator T () const noexcept { return n; }
  constexpr Mod & operator += (Mod m) noexcept { return * this = * this + m; }
  constexpr Mod & operator -= (Mod m) noexcept { return * this = * this - m; }
  constexpr Mod & operator *= (Mod m) noexcept { return * this = * this * m; }
  friend constexpr bool operator == (const Mod & a, const Mod & b) noexcept { return a.n == b.n; }
  friend constexpr bool operator != (const Mod & a, const Mod & b) noexcept { return ! (a == b); }
  friend constexpr auto operator + (const Mod & a, const Mod & b) noexcept { return Mod (a.n + b.n); }
  friend constexpr auto operator - (const Mod & a, const Mod & b) noexcept { return Mod (a.n - b.n); }
  friend constexpr auto operator * (const Mod & a, const Mod & b) noexcept { return Mod (a.n * b.n); }
};

// Union-Find木
// グループ分けを木構造で管理する（根が同じ <=> 同じグループに属する）
struct UnionFind
{
  using node_t = size_t;
  vector <node_t> parent;
  explicit UnionFind (node_t n) : parent (n) { for (node_t i = 0; i < n; ++ i) parent [i] = i; }
  auto root (node_t x) noexcept -> node_t { return parent [x] == x ? x : parent [x] = root (parent [x]); }
  auto merge (node_t x, node_t y) noexcept { x = root (x); y = root (y); if (x != y) parent [y] = x; }
};

// 不動点（Haskellのfix）
template <typename F>
struct Fix : private F
{
  explicit constexpr Fix (F f) noexcept : F (f) {}
  template <typename ... Args>
  constexpr auto operator () (Args && ... args) const noexcept (noexcept (F::operator () (* this, forward <Args> (args) ...))) -> decltype (auto)
  {
    return F::operator () (* this, forward <Args> (args) ...);
  }
};

// ヘルパー関数
template <typename F>
constexpr auto make_fix (F f) noexcept
{
  return Fix <F> {f};
}

// トポロジカルソート
template <typename Graph>
inline auto topological_sort (const Graph & graph)
{
  using node_t = size_t;
  enum class flag_t { YET, VISITED, DONE };
  auto n = graph.size ();
  vector <flag_t> visited (n, flag_t::YET);
  vector <node_t> res (n);
  auto res_ite = res.end ();
  auto impl = [&] (auto self, auto && from) {
    if (visited[from] == flag_t::DONE) return;
    if (visited[from] == flag_t::VISITED) throw runtime_error ("Error in topological_sort: The graph must be DAG.");
    visited[from] = flag_t::VISITED;
    for (auto && to : graph[from]) self (self, to);
    * -- res_ite = from;
    visited[from] = flag_t::DONE;
  };
  rep (i, n) impl (impl, node_t {i});
  return res;
}

// delimiter付き出力
template <typename Iterator, typename String>
inline auto ostream_join (Iterator first, Iterator last, ostream & stream, String && delimiter = " ")
{
  if (first != last) stream << * first ++;
  while (first != last) stream << delimiter << * first ++;
}

// 上のfor_each版（誰得？）
template <typename Iterator, typename F, typename String>
inline auto for_each_join (Iterator first, Iterator last, F f, String && delimiter = " ")
{
  if (first != last) f (* first ++);
  while (first != last)
  {
    f (delimiter);
    f (* first ++);
  }
}

namespace detail
{
  template <unsigned R>
  struct combination_helper
  {
    template <typename Iterator, typename F, typename ... Results>
    static constexpr auto f (Iterator begin, Iterator end, F callback, Results & ... results) -> void
    {
      for (auto ite = begin; ite < end; ++ ite)
      {
        combination_helper <R - 1>::f (next (ite), end, callback, results ..., * ite);
      }
    }
  };

  template <>
  struct combination_helper <0u>
  {
    template <typename Iterator, typename F, typename ... Results>
    static constexpr auto f (Iterator, Iterator, F callback, Results & ... results) -> void
    {
      callback (results ...);
    }
  };
} // namespace detail

template <unsigned R, typename Iterator, typename F>
inline constexpr auto combination (Iterator begin, Iterator end, F callback)
{
  return detail::combination_helper <R>::f (begin, end, callback);
}

inline auto input_vector_int (size_t n)
{
  vector <int> v;
  copy_n (istream_iterator <int> (cin), n, back_inserter (v));
  return v;
}

template <typename T>
inline auto operator << (ostream & stream, const vector <T> & x) -> ostream &
{
  stream << "[";
  ostream_join (begin (x), end (x), stream, ", ");
  return stream << "]";
}

template <typename T>
inline auto operator << (ostream & stream, const set <T> & x) -> ostream &
{
  stream << "{";
  ostream_join (begin (x), end (x), stream, ", ");
  return stream << "}";
}

template <typename T, typename U>
inline auto operator << (ostream & stream, const map <T, U> & x) -> ostream &
{
  auto f = [&] (auto && elem) {
    stream << elem.first << ": " << elem.second;
  };
  auto first = begin (x);
  auto last = end (x);
  stream << "{";
  if (first != last) f (* first ++);
  while (first != last)
  {
    stream << ", ";
    f (* first ++);
  }
  return stream << "}";
}

auto main () -> int
{
  cin.tie (nullptr);
  ios::sync_with_stdio (false);
}

