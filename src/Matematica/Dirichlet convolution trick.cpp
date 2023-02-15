/// Source:
/// https://codeforces.com/blog/entry/54150
/// Verification:
/// https://dmoj.ca/submission/4720699
/* Prefix sum of multiplicative functions :
 * $p_f$: the prefix sum of the desired $f(x)$ ($1 \leq x \leq th$).
 * $p_g$: the prefix sum of $g(x)$ ($0 \leq x \leq N$).
 *        Usually $g(x)=x^k$ or $g(x)=[x=1]$.
 * $p_c$: the prefix sum of $f*g(x)=\displaystyle\sum_{d|x}f(d)g(\frac{x}{d})$ ($0 \leq x \leq N$).
 * th: the thereshold, generally should be $n^{\frac{2}{3}}$. */
struct prefix_mul {
  typedef long long (*func) (__int128);
  func p_f, p_g, p_c;
  long long n, th, inv;
  std::unordered_map <long long, long long> mem;
  prefix_mul (func p_f, func p_g, func p_c) : 
    p_f (p_f), p_g (p_g), p_c (p_c) {}
  long long calc (long long x) {
    if (x <= th) return p_f (x);
    auto d = mem.find (x);
    if (d != mem.end ()) return d -> second;
    long long ans = 0;
    for (long long i = 2, la; i <= x; i = la + 1) {
      la = x / (x / i);
      ans=ans+((p_g(la)-p_g(i-1)+mod)%mod)*calc(x/i)%mod;
      ans %= mod;
    }
    ans = p_c (x) - ans; 
    ans=ans/inv;//if $\mathit{inv}\neq1$, use multiplicative inverse
    ans %= mod;
    return mem[x] = ans;
  }
  // Time: $\mathcal{O}(n^{\frac{2}{3}})$
  long long solve (long long n, long long th) {
    if (n <= 0) return 0;
    prefix_mul::n = n; prefix_mul::th = th;
    inv = p_g (1);
    return calc (n); 
  }
};
