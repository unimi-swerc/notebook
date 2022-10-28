/// Source: 
/// https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Flows%20(12.3)/MCMF.h
/// Verification:
/// https://open.kattis.com/submissions/9740395
/*Minimum-cost maximum flow, assumes no negative cycles. It's
*possible to choose negative edge costs such that the first 
*run of Dijkstra is slow, but this hasn't been an issue 
* Time: Ignoring first run of Dijkstra, $\mathcal{O}(FM\log M)$ 
* if caps are integers and $F$ is max flow. Tested
* with $N\leq 250, M\leq 5000, \text{cap}\leq 10^4, W\leq 1000$ (0.4 sec)
*/
struct MCMF { // 0-based, archi direzionati
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
