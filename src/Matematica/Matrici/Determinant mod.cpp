/// Source:
/// https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/IntDeterminant.h
/// Verification:
/// https://judge.yosupo.jp/submission/94007
/* Calculates determinant using modular arithmetics
 * Destroys the matrix.
 * Time: $\mathcal{O}(N^3)$, con $N\leq 500$ impiega 327 ms
 */
const ll mod = 12345;//non per forza primo
ll det(vector<vector<ll>>& a) {
  int n = sz(a); ll ans = 1;
  rep(i,0,n) {
    rep(j,i+1,n) {
      while (a[j][i] != 0) { // gcd step
        ll t = a[i][i] / a[j][i];
        if (t) rep(k,i,n)
          a[i][k] = (a[i][k] - a[j][k] * t) % mod;
        swap(a[i], a[j]);
        ans *= -1;
      }
    }
    ans = ans * a[i][i] % mod;
    if (!ans) return 0;
  }
  return (ans + mod) % mod;
}
