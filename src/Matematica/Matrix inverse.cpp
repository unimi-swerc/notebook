/// Source:
/// https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/MatrixInverse.h
/// Verification:
/// https://judge.yosupo.jp/submission/139307
/* Invert matrix $A$ modulo a prime. Returns rank; result
 * is stored in $A$ unless singular (rank < n).
 * For prime powers, repeatedly set
 * $A^{-1} = A^{-1} (2I - AA^{-1}) (\text{mod } p^k)$
 * where $A^{-1}$ starts as the inverse of $A\ \text{mod } p$,
 * and $k$ is doubled in each step.
 * Time: $\mathcal{O}(n^3)$ (con $n\leq 500$ impiega 253 ms) */
typedef modular<mod> T; //oppure double
int matInv(vector<vector<T>>& A) {
  int n = sz(A); vi col(n);
  vector<vector<T>> tmp(n, vector<T>(n));
  rep(i,0,n) tmp[i][i] = 1, col[i] = i;
  rep(i,0,n) {
    int r = i, c = i;
    rep(j,i,n) rep(k,i,n)
    if (fabs(A[j][k]) > fabs(A[r][c]))
      r = j, c = k;
    if (fabs(A[r][c]) <= 1e-12) return i;
    A[i].swap(A[r]); tmp[i].swap(tmp[r]);
    rep(j,0,n)
    swap(A[j][i], A[j][c]), swap(tmp[j][i], tmp[j][c]);
    swap(col[i], col[c]);
    T v = A[i][i];
    rep(j,i+1,n) {
      T f = A[j][i] / v;
      A[j][i] = 0;
      rep(k,i+1,n) A[j][k] -= f*A[i][k];
      rep(k,0,n) tmp[j][k] -= f*tmp[i][k];
    }
    rep(j,i+1,n) A[i][j] = A[i][j]/v;
    rep(j,0,n) tmp[i][j] = tmp[i][j]/v;
    A[i][i] = T(1);
  }
  // forget A at this point, just eliminate tmp backward
  for (int i = n-1; i > 0; --i) rep(j,0,i) {
    T v = A[j][i];
    rep(k,0,n) tmp[j][k] -= v*tmp[i][k];
  }
  rep(i,0,n) rep(j,0,n) A[col[i]][col[j]] = tmp[i][j];
  return n;
}
