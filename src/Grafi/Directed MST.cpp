/// Source: https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/DirectedMST.h
/// Verification:
///
// 0-based, requires RollbackUF and Leftist heap,$\mathcal{O}(E \log V)$
pair<ll, vi> dmst(int n, int r, vector<KEY>& g) {
  RollbackUF uf(n); vector<ph> heap(n,nullptr);
  for(KEY e : g) heap[e[2]] = meld(heap[e[2]],new Heap{e});
  ll res = 0; vi seen(n, -1), path(n), par(n);
  seen[r] = r;
  vector<KEY> Q(n), in(n, {0,-1,-1}), comp;
  deque<tuple<int, int, vector<KEY>>> cycs;
  rep(s,0,n) {
    int u = s, qi = 0, w;
    while (seen[u] < 0) {
      if(!heap[u])return {-1,{}};//if no MST exist returns 1
      KEY e = heap[u]->top();
      heap[u]->delta -= e[0]; heap[u] = pop(heap[u]);
      Q[qi] = e, path[qi++] = u, seen[u] = s;
      res += e[0], u = uf.find(e[1]);
      if (seen[u] == s) { /// found cycle, contract
        ph cyc = nullptr;
        int end = qi, time = uf.time();
        do cyc = meld(cyc, heap[w = path[--qi]]);
        while (uf.join(u, w));
        u = uf.find(u), heap[u] = cyc, seen[u] = -1;
        cycs.push_front({u, time, {&Q[qi], &Q[end]}});
      }
    }
    rep(i,0,qi) in[uf.find(Q[i][2])] = Q[i];
  }
  for (auto& [u,t,comp] : cycs) { // restore sol (optional)
    uf.rollback(t); KEY inEdge = in[u];
    for (auto& e : comp) in[uf.find(e[2])] = e;
    in[uf.find(inEdge[2])] = inEdge;
  }
  rep(i,0,n) par[i] = in[i][1];
  return {res, par};
}
