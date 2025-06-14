/// Source: Dariost (booklet SWERC 2019-2020 LaStatale Blue)
/// https://github.com/dariost/swerc/blob/master/src/Graphs/edmonds_blossom.hpp
/// Verification:
/// https://judge.yosupo.jp/submission/86633
/// https://projecteuler.net/problem=871 (solo su meduse ma vabbè)
const int maxn = 505; //with $N\leq 500$ run in 8 ms
struct EdmondsStruct { // Complexity: $\mathcal{O}(VE)$?
  int vis[maxn], par[maxn], orig[maxn];
  int match[maxn], aux[maxn], t, n;
  vector <int> conn[maxn]; queue <int> q;
  void add(int u, int v) { // 1-based
    conn[u].push_back(v), conn[v].push_back(u);
  } // nota: u != v (no self-loop)
  // total number of nodes
  void init(int _n) {
    n = _n, t = 0;
    for (int i = 0; i <= n; ++i) {
      conn[i].clear();
      match[i] = aux[i] = par[i] = 0;
    }
  }
  void augment(int u, int v) {
    int pv = v, nv;
    do {
      pv = par[v], nv = match[pv];
      match[v] = pv, match[pv] = v;
      v = nv;
    } while (u != pv);
  }
  int lca(int v, int w) {
    ++t;
    while (1) {
      if (v) {
        if (aux[v] == t) return v;
        aux[v] = t;
        v = orig[par[match[v]]];
      }
      swap(v, w);
    }
  }
  void blossom(int v, int w, int a) {
    while (orig[v] != a) {
      par[v] = w;
      w = match[v];
      if (vis[w] == 1) q.push(w), vis[w] = 0;
      orig[v] = orig[w] = a;
      v = par[w];
    }
  }
  bool bfs(int u) {
    fill(vis + 1, vis + 1 + n, -1);
    iota(orig + 1, orig + n + 1, 1);
    q = queue <int> (); q.push(u); vis[u] = 0;
    while (!q.empty()) {
      int v = q.front(); q.pop();
      for (int x: conn[v]) {
        if (vis[x] == -1) {
          par[x] = v, vis[x] = 1;
          if (!match[x]) return augment(u, x), 1;
          q.push(match[x]); vis[match[x]] = 0;
        }
        else if (vis[x] == 0 && orig[v] != orig[x]){
          int a = lca(orig[v], orig[x]);
          blossom(x, v, a); blossom(v, x, a);
        }
      }
    }
    return 0;
  }
  int max_match() { //match[i]=0 -> not matched
    int ans = 0; vector <int> V(n - 1);
    iota(V.begin(), V.end(), 1);
    // shuffle(V.begin(), V.end(), mt19937(1007050321));
    for (auto x: V) if (!match[x]) {
      for (auto y: conn[x]) if (!match[y]) {
        match[x] = y, match[y] = x;
        ++ans; break;
      }
    }
    for (int i = 1; i <= n; ++i)
    if (!match[i] && bfs(i)) ++ans;
    return ans;
  }
};
