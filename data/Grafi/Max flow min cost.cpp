//Time: Ignoring first run of Dijkstra, $O(FM\log M)$ 
 //  * if caps are integers and $F$ is max flow.
struct MCMF { 
  using F = ll; using C = ll; // flow type, cost type
  struct Edge { int to, rev; F flo, cap; C cost; };
  int N; V<C> p, dist; vpi pre; V<V<Edge>> adj;
  void init(int _N) { N = _N;
    p.rsz(N), adj.rsz(N), dist.rsz(N), pre.rsz(N); }
  void ae(int u, int v, F cap, C cost) { assert(cap >= 0); 
    adj[u].pb({v,sz(adj[v]),0,cap,cost}); 
    adj[v].pb({u,sz(adj[u])-1,0,0,-cost});
  }
  //send flow through lowest cost path
  bool path(int s, int t) {
    const C inf = numeric_limits<C>::max(); 
    dist.assign(N,inf);
    using T = pair<C,int>;
    priority_queue<T,V<T>,greater<T>> todo; 
    todo.push({dist[s] = 0,s}); 
    while (sz(todo)) { // Dijkstra
      T x = todo.top(); todo.pop(); 
      if (x.f > dist[x.s]) continue;
      //all weights should be non-negative
      each(e,adj[x.s]) {
        if (e.flo < e.cap && ckmin(dist[e.to],
            x.f+e.cost+p[x.s]-p[e.to])) {
          pre[e.to]={x.s,e.rev};
          todo.push({dist[e.to],e.to});
        }
      }
    } // if costs are doubles, add some EPS so you 
    // don't traverse ~0-weight cycle repeatedly
    return dist[t] != inf; // true if augmenting path
  }
  pair<F,C> calc(int s, int t) { assert(s != t);
    F0R(_,N) F0R(i,N) each(e,adj[i]) // Bellman-Ford
      if (e.cap) ckmin(p[e.to],p[i]+e.cost);
    F totFlow = 0; C totCost = 0;
    while (path(s,t)) { // p -> potentials for Dijkstra
      F0R(i,N)p[i]+=dist[i];//don't matter for unreachable
      F df = numeric_limits<F>::max();
      for (int x = t; x != s; x = pre[x].f) {
        Edge& e = adj[pre[x].f][adj[x][pre[x].s].rev]; 
        ckmin(df,e.cap-e.flo); }
      totFlow += df; totCost += (p[t]-p[s])*df;
      for (int x = t; x != s; x = pre[x].f) {
        Edge& e = adj[x][pre[x].s]; e.flo -= df;
        adj[pre[x].f][e.rev].flo += df;
      }
    } // get max flow you can send along path
    return {totFlow,totCost};
  }
};
