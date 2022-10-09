/// Source:
/// https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/FastSubsetTransform.h
/// Verification:
/// https://judge.yosupo.jp/submission/86705
/// https://judge.yosupo.jp/submission/86706
// The size of a must be a power of two.
// Time: $\mathcal{O}(N \log N)$ (con $N\leq 2^20$ impiega 0.75 sec)
typedef pair<__int128, __int128> pii;
typedef vector<__int128> vi;
void FST(vi& a, bool inv) {
  for (int n = sz(a), step = 1; step < n; step *= 2) {
    for (int i = 0; i < n; i += 2 * step) rep(j,i,i+step) {
      __int128 &u = a[j], &v = a[j + step]; tie(u, v) =
        inv ? pii(v - u, u) : pii(v, u + v); // AND 
        // inv ? pii(v, u - v) : pii(u + v, u); // OR
        // pii(u + v, u - v);                   // XOR
    }
  }
  // if (inv) for (__int128& x : a) x /= sz(a); // XOR
}
vi conv(vi a, vi b) {
  FST(a, 0); FST(b, 0);
  rep(i,0,sz(a)) a[i] *= b[i];
  FST(a, 1); return a;
}
