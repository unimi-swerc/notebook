/// Source:
/// https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/MatrixInverse-mod.h
/// Verification:
/// https://judge.yosupo.jp/submission/109704
/* Invert matrix $A$ modulo a prime. Returns rank; result
 * is stored in $A$ unless singular (rank < n).
 * For prime powers, repeatedly set
 * $A^{-1} = A^{-1} (2I - AA^{-1}) (\text{mod } p^k)$
 * where $A^{-1}$ starts as the inverse of $A\ \text{mod } p$,
 * and $k$ is doubled in each step.
 * Time: $\mathcal{O}(n^3)$ (con $n\leq 500$ impiega 253 ms) */
const ll mod = 998244353;//1000000007; // faster if const
ll modpow(ll b, ll e) {
  ll ans = 1;
  for (; e; b = b * b % mod, e /= 2)
    if (e & 1) ans = ans * b % mod;
  return ans;
}
int matInv(vector<vector<ll>>& A) {
  int n = sz(A); vi col(n);
  vector<vector<ll>> tmp(n, vector<ll>(n));
  rep(i,0,n) tmp[i][i] = 1, col[i] = i;
  rep(i,0,n) {
    int r = i, c = i;
    rep(j,i,n) rep(k,i,n) if (A[j][k]) {
      r = j; c = k; goto found;
    }
    return i;
found:
    A[i].swap(A[r]); tmp[i].swap(tmp[r]);
    rep(j,0,n) {
      swap(A[j][i],A[j][c]),swap(tmp[j][i],tmp[j][c]);
    }
    swap(col[i], col[c]);
    ll v = modpow(A[i][i], mod - 2);
    rep(j,i+1,n) {
      ll f = A[j][i] * v % mod;
      A[j][i] = 0;
      rep(k,i+1,n) A[j][k]=(A[j][k]-f*A[i][k])%mod;
      rep(k,0,n) tmp[j][k]=(tmp[j][k]-f*tmp[i][k])%mod;
    }
    rep(j,i+1,n) A[i][j] = A[i][j] * v % mod;
    rep(j,0,n) tmp[i][j] = tmp[i][j] * v % mod;
    A[i][i] = 1;
  }
  for (int i = n-1; i > 0; --i) rep(j,0,i) {
    ll v = A[j][i];
    rep(k,0,n) tmp[j][k]=(tmp[j][k]-v*tmp[i][k])%mod;
  }
  rep(i,0,n) rep(j,0,n)
    A[col[i]][col[j]]=tmp[i][j]%mod+(tmp[i][j]<0?mod:0);
  return n;
}
