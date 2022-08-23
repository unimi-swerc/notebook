// 0-based, with n<=5000, m<=30000 run in 0.19 sec
// per i grafi bipartiti N<=100000
using pi = pair<int,int>;
#define f first
#define s second
template<class T> using V = vector<T>; 
using vi = V<int>;
using vpi = V<pi>;
#define sz(x) int((x).size())
#define rsz resize
#define pb push_back
#define ft front()
#define each(a,x) for (auto& a: x)
 
template<class F> struct Dinic {
  struct Edge { int to, rev; F cap; };
  int N; V<V<Edge>> adj;
  void init(int _N) { N = _N; adj.rsz(N); }
  pi ae(int a, int b, F cap, F rcap = 0) { 
    assert(min(cap,rcap) >= 0); // saved me > once
    adj[a].pb({b,sz(adj[b]),cap});
    adj[b].pb({a,sz(adj[a])-1,rcap});
    return {a,sz(adj[a])-1};
  }
  F edgeFlow(pi loc) { // get flow along original edge
    const Edge& e = adj.at(loc.f).at(loc.s);
    return adj.at(e.to).at(e.rev).cap;
  }
  vi lev, ptr;
  bool bfs(int s, int t) { // level=shortest dist from source
    lev = ptr = vi(N);
    lev[s] = 1; queue<int> q({s});
    while (sz(q)) { int u = q.ft; q.pop();
      each(e,adj[u]) if (e.cap && !lev[e.to]) {
        q.push(e.to), lev[e.to] = lev[u]+1;
        if (e.to == t) return 1;
      }
    }
    return 0;
  }
  F dfs(int v, int t, F flo) {
    if (v == t) return flo;
    for (int& i = ptr[v]; i < sz(adj[v]); i++) {
      Edge& e = adj[v][i];
      if (lev[e.to]!=lev[v]+1||!e.cap) continue;
      if (F df = dfs(e.to,t,min(flo,e.cap))) { 
        e.cap -= df; adj[e.to][e.rev].cap += df;
        return df; } // saturated >=1 one edge
    }
    return 0;
  }
  F maxFlow(int s, int t) {
    F tot = 0; while (bfs(s,t)) while (F df = 
      dfs(s,t,numeric_limits<F>::max())) tot += df;
    return tot;
  }
};
