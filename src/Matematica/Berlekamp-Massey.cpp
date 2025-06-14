/// Source:
/// https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/BerlekampMassey.h
/// https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/ModPow.h
/// Verification:
/// https://judge.yosupo.jp/submission/86740
/// https://www.spoj.com/problems/FIBPWSUM/ (id 29456798)
/* Description: Recovers any n-order linear recurrence
 * relation from the first $2n$ terms of the recurrence.
 * Useful for guessing linear recurrences after brute-
 * forcing the first terms. Should work on any field,
 * but numerical stability for floats is not guaranteed.
 * Output will have size $<n$. Time: $\mathcal{O}(N^2)$.
 * Usage: berlekampMassey({0, 1, 1, 3, 5, 11}) // {1, 2}*/
const ll mod = 1000000007; // faster if const
ll modpow(ll b, ll e) {
  ll ans = 1;
  for (; e; b = b * b % mod, e /= 2)
    if (e & 1) ans = ans * b % mod;
  return ans;
}
//con $n\leq 10^4$ impiega 211 ms
vector<ll> berlekampMassey(vector<ll> s) {
  int n = sz(s), L = 0, m = 0; ll b = 1;
  vector<ll> C(n), B(n), T;
  C[0] = B[0] = 1;
  rep(i,0,n) { ++m;
    ll d = s[i] % mod;
    rep(j,1,L+1) d = (d + C[j] * s[i - j]) % mod;
    if (!d) continue;
    T = C; ll coef = d * modpow(b, mod-2) % mod;
    rep(j,m,n) C[j] = (C[j] - coef * B[j - m]) % mod;
    if (2 * L > i) continue;
    L = i + 1 - L; B = T; b = d; m = 0;
  }
  C.resize(L + 1); C.erase(C.begin());
  for (ll& x : C) x = (mod - x) % mod;
  return C;
}
