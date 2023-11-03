/// Source:
/// https://judge.yosupo.jp/submission/72135
/// Verification:
/// https://judge.yosupo.jp/submission/145806
// Min Cost Circulation w/ Supplies and Demands (0-based)
using i128 = __int128_t; //Time: $\mathcal{O}(M^2 \log U \log M)$
template<class T> bool ckmax(T& a, const T& b) {
  return a < b ? a = b, 1 : 0; }
struct CapacityScaling {//Tested with $M<10^3,U<10^9$(33 ms)
  using Flow=int64_t;using Cost=int64_t;using V_id=int32_t;
  using E_id = int32_t; Cost INF = 1; i128 ans_delta = 0;
  struct Edge{V_id src, dst; Flow flow, cap; Cost cost;};
  int N; V<Flow> B; V<V<E_id>> G; V<Cost> P; V<Edge> E;
  V<E_id> pre_edge;
  void init(int _N) { N = _N; B.resize(N); G.resize(N+1);
    P.resize(N+1); pre_edge.resize(N+1); }
  E_id ae(V_id a, V_id b, Flow l, Flow u, Cost c) {
    G[a].pb(sz(E)); E.pb(Edge{a,b,0,u-l,c});
    G[b].pb(sz(E)); E.pb(Edge{b,a,0,0,-c});
    ans_delta += l*c; B[a] -= l, B[b] += l;
    return sz(E)-2;
  }
  V_id backtrack(V_id x, Flow delta) { assert(delta > 0);
    while (pre_edge[x] != -1) {
      E[pre_edge[x]].flow += delta;
      assert(E[pre_edge[x]].flow <= E[pre_edge[x]].cap);
      E[pre_edge[x]^1].flow -= delta;
      x = E[pre_edge[x]].src;
    }
    return x;
  }
  void saturate_negative(Flow delta) {
    F0R(e,sz(E)) {
      Flow rcap = E[e].cap-E[e].flow; assert(rcap >= 0);
      rcap -= rcap%delta;
      Cost rcost = P[E[e].src]+E[e].cost-P[E[e].dst];
      if (rcost < 0) {
        E[e].flow += rcap; E[e^1].flow -= rcap;
        B[E[e].src] -= rcap; B[E[e].dst] += rcap;
      }
    }
  }
  V_id dual(Flow delta) {
    using T = pair<Cost,int>;
    priority_queue<T,V<T>,greater<T>> pq;
    V<Cost> add(N, numeric_limits<Cost>::max());
    F0R(i,N) if (B[i] >= delta) {
      pq.push({add.at(i) = 0,i});
      pre_edge[i] = -1;
    }
    Cost farthest = 0;
    while (sz(pq)) {
      auto p = pq.top(); pq.pop();
      if (p.f > add.at(p.s)) continue;
      farthest = p.f;
      if (B[p.s] <= -delta) {
        F0R(i,N) P.at(i) += min(add.at(i),farthest);
        return p.s;
      }
      each(e,G[p.s]) if (E[e].cap-E[e].flow >= delta)
        if(ckmin(add[E[e].dst],
          p.f+E[e].cost+P[E[e].src]-P[E[e].dst])){
        pre_edge[E[e].dst] = e;
        pq.push({add.at(E[e].dst),E[e].dst});
      }
    }
    return -1;
  }
  void primal(V_id dst, Flow delta) {
    int src = backtrack(dst,delta);
    B.at(src) -= delta; B.at(dst) += delta;
  }
  i128 solve(bool &ok) {
    Flow max_cap = 1;
    each(b,B) ckmax(max_cap,abs(b));
    each(e,E) ckmax(max_cap,e.cap);
    Flow delta = 1; while (delta < max_cap) delta *= 2;
    for (; delta; delta /= 2) {
      saturate_negative(delta);
      while (true) {
        int t = dual(delta);
        if (t == -1) break;
        primal(t,delta);
      }
    }
    F0R(i,N) if (B[i] != 0) return ok=false;
    i128 ans = ans_delta; ok=true;
    for(E_id i=0;i<sz(E);i+=2)ans+=E[i].flow*E[i].cost;
    return ans;
  }
};
/*CapacityScaling NS; NS.init(n);
  for(int i=0;i<n;++i)cin>>NS.B[i];//vertex supply (out-in)
  if (n == 0) { cout << 0 << endl; return 0; }
  for(int i = 0; i < m; ++i){//l,u,k,NS.b[i] anche negativi
  cin >> a >> b >> l >> u >> k; lo[i] = l; //arco i-esimo
  assert(2 * i == NS.ae(a, b, l, u, k));}//(archi 0-based)
  auto cost = NS.solve(tmp); //tmp è falso se infeasible
  NS.E[2 * i].flow + lo[i] = flusso arco i-esimo */
