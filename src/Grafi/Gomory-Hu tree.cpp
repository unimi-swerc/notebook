/// Source:
/// https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Flows%20(12.3)/GomoryHu.h
/// Verification:
/// https://www.spoj.com/problems/MCQUERY/ (id: 30634725)
/*Returns edges of Gomory-Hu tree (second element is weight)
 * Max flow between pair of vertices of undirected graph
 * is given by min edge weight along tree path.
 * Uses the fact that for any $i,j,k,$ $\lambda_{ik}\ge \min(\lambda_{ij},\lambda_{jk}),$
 * where $\lambda_{ij}$ denotes the flow between $i$ and $j.$
 * Time: $N-1$ calls to Dinic (use Max flow code), tested
 * with $T\leq 10,N \leq 150,M \leq 3000,\text{edgeweight}\leq 10^6$(0.10 s) */
using pi = pair<int,int>; //c'è già in Dinic ma vabbè
template<class F> V<pair<pi,F>> gomoryHu(int N, 
    const V<pair<pi,F>>& ed) { //nodes 0-based
  vi par(N); Dinic<F> D; D.init(N);
  vpi ed_locs; 
  each(t,ed)ed_locs.pb(D.ae(t.f.f,t.f.s,t.s,t.s));
  V<pair<pi,F>> ans;
  FOR(i,1,N) {
    each(p,ed_locs) { // reset capacities
      auto& e = D.adj.at(p.f).at(p.s);
      auto& e_rev = D.adj.at(e.to).at(e.rev);
      e.cap = e_rev.cap = (e.cap+e_rev.cap)/2;
    }
    ans.pb({{i,par[i]},D.maxFlow(i,par[i])});
    FOR(j,i+1,N)if(par[j]==par[i] && D.lev[j])par[j]=i;
  }
  return ans;
} //works also for disconnected graphs
