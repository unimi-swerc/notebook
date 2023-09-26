/// Source: https://judge.yosupo.jp/submission/154408
/// Verification:
/// Balance CEOI 2023
/// https://judge.yosupo.jp/submission/158216
/// https://www.spoj.com/problems/MATCHING/ (id: 31764370)
/// https://osijek2023s-d4.eolymp.io/problems/8
struct HopcroftKarp { //tested with $n,m\leq 1e5$ (75 ms)
  vector<int> g, l, r; int ans; // 0-based
  HopcroftKarp(int n, int m, const vector<pair<int,int>> &e)
  : g(e.size()), l(n, -1), r(m, -1), ans(0) {
    vector<int> deg(n + 1), a, p, q(n);
    for (auto &[x, y] : e) deg[x]++;
    for (int i = 1; i <= n; i++) deg[i] += deg[i - 1];
    for (auto &[x, y] : e) g[--deg[x]] = y;
    for (bool match=true; match;) {
      a.assign(n,-1), p.assign(n,-1); int t=0; match=false;
      for (int i = 0; i < n; i++)
        if (l[i] == -1) q[t++] = a[i] = p[i] = i;
      for (int i = 0; i < t; i++) {
        int x = q[i];
        if (~l[a[x]]) continue;
        for (int j = deg[x]; j < deg[x + 1]; j++) {
          int y = g[j];
          if (r[y] == -1) {
            while (~y) r[y] = x, swap(l[x], y), x = p[x];
            match = true; ans++; break;//ans=numero match
          }
          if(p[r[y]]==-1)q[t++]=y=r[y],p[y]=x,a[y]=a[x];
        }
      }
    }//nodi sx vengono matchati dando preferenza ai primi(?)
  }//nodi sx numerati da 0 a n-1, nodi dx da 0 a m-1
}; //l[i]= match del nodo sx i (-1 se non è matchato)
