/// Source:
/// https://judge.yosupo.jp/submission/64812
/// Verification:
/// https://judge.yosupo.jp/submission/135967
/// https://atcoder.jp/contests/arc161/submissions/41812299
/// https://judge.yosupo.jp/submission/142333 (solo SCC)
/* 0-based, $X = 2*i$, $\mathit{not}(X) = 2*i+1$
 * ritorna un vector vuoto se non c'è soluzione
 * altrimenti ritorna un vector V tale che V[i] = true
 * se la variabile i deve valere true (V.size()=N)
 * tested with $N \text{(variables)}, M \text{(clauses)} \le 500000$ (0.7 sec) */
#define X first
#define Y second
typedef pair<int, int> ipair;
ipair conj(int v1, bool neg1, int v2, bool neg2) {
  return {v1 * 2 + neg1, v2 * 2 + neg2};
}
const int N = 1000111; // Time: $\mathcal{O}(N+M)$
vector<char> twoSat(int n, vector<ipair> const& cc) {
  n *= 2;
  static vector<int> e[N], eb[N];
  for (auto const& p : cc) {
    int x = p.X, y = p.Y;
    e[x].push_back(y ^ 1);
    e[y].push_back(x ^ 1);
    eb[x ^ 1].push_back(y);
    eb[y ^ 1].push_back(x);
  }
  static int order[N], oi, vis[N];
  oi = 0; // Compute SCC (Kosaraju)
  fill(vis, vis + n, 0);
  struct Internal {
    static void dfs1(int v) {
      if (vis[v]) return;
      vis[v] = 1;
      for (int nv : e[v]) dfs1(nv);
      order[oi++] = v;
    }
    static void dfs2(int v, int comp) {
      if (vis[v]) return;
      vis[v] = comp;
      for (int nv : eb[v]) dfs2(nv, comp);
    }
  };
  for (int v = 0; v < n; ++v) Internal::dfs1(v);
  fill(vis, vis + n, 0);
  int comp = 0;
  for (int i = n - 1; i >= 0; --i) {
    int v = order[i];
    if (vis[v]) continue;
    ++comp;
    Internal::dfs2(v, comp);
  }
  bool fail = false; vector<char> ans(n / 2);
  for (int v = 0; v < n; v += 2)
    if (vis[v] == vis[v + 1])
      fail = true;
    else
      ans[v / 2] = (vis[v] < vis[v + 1]);
  if (fail) ans.clear();
  for (int i = 0; i < n; ++i) {
    e[i].clear();
    eb[i].clear();
  }
  return ans;
}
