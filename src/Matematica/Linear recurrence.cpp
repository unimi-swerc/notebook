/// Source:
/// https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/LinearRecurrence.h
/// Verification:
/// https://www.spoj.com/problems/FIBPWSUM/ (solo con N piccolo)
/* Description: Generates the k'th term of an n-order
 * linear recurrence S[i] = sum(S[i-j-1] * tr[j]),
 * given S[0...n-1] and tr[0...n-1].
 * Faster than matrix multiplication.
 * Useful together with Berlekamp-Massey.
 * Usage: linearRec({0, 1}, {1, 1}, k) // Fibonacci */
typedef vector<ll> Poly; // Time: $\mathcal{O}(n^2 \log k)$
ll linearRec(Poly S, Poly tr, ll k) {
  int n = sz(tr);
  auto combine = [&](Poly a, Poly b) {
    Poly res(n * 2 + 1);
    rep(i,0,n+1) rep(j,0,n+1)
      res[i + j] = (res[i + j] + a[i] * b[j]) % mod;
    for (int i = 2 * n; i > n; --i) rep(j,0,n)
      res[i-1-j] = (res[i-1-j] + res[i] * tr[j]) % mod;
    res.resize(n + 1);
    return res;
  };
  Poly pol(n + 1), e(pol); ll res = 0;
  pol[0] = e[1] = 1;
  for (++k; k; k /= 2) {
    if (k % 2) pol = combine(pol, e);
    e = combine(e, e);
  }
  rep(i,0,n) res = (res + pol[i + 1] * S[i]) % mod;
  return res;
}
