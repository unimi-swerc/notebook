/// Source:
/// https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/FastSubsetTransform.h
/// Verification:
/// https://judge.yosupo.jp/submission/86705 (and)
/// https://judge.yosupo.jp/submission/86706 (xor)
/// https://codeforces.com/contest/1906/submission/237087910 (xor)
// The size of a,b MUST be a power of two.
// Time: $\mathcal{O}(N \log N)$ (con $N\leq 2^{20}$ impiega 0.75 sec)
typedef pair<__int128, __int128> pii; //pii e vi...
typedef vector<__int128> vi; //...sovrascrivono il template
void FST(vi& a, bool inv) {
  for (int n = sz(a), step = 1; step < n; step *= 2) {
    for (int i = 0; i < n; i += 2 * step) rep(j,i,i+step) {
      __int128 &u = a[j], &v = a[j + step]; tie(u, v) =
        inv ? pii(v - u, u) : pii(v, u + v); // AND
        // inv ? pii(v, u - v) : pii(u + v, u); // OR
        // pii(u + v, u - v);                   // XOR
    } //OR: $A'[j] = \sum_i A[i] I_{i \subseteq j}$, AND: $A'[j] = \sum_i A[i] I_{i \supseteq j}$
  } //XOR: $A'[j] = \sum_i A[i] (-1) ^ {|i \cap j|}$ (FWHT)
  // if (inv) for (__int128& x : a) x /= sz(a); // XOR
} //CircConv mod n: $A'[j] = \sum_i A[i] (e^{\mathrm{i} \frac{2 \pi j}{n}}) ^ i$ (FFT)
vi conv(vi a, vi b) { //tested with $a_i,b_i<10^9,N\leq 2^{20}$
  FST(a, 0); FST(b, 0);
  rep(i,0,sz(a)) a[i] *= b[i];
  FST(a, 1); return a;
} //GCD: $A'[j] = \sum_i A[i] I_{j \mid i}$, LCM: $A'[j] = \sum_i A[i] I_{i \mid j}$
