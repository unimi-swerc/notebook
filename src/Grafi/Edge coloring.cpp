/// Source:
/// https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/EdgeColoring.h
/// Verification:
/// https://open.kattis.com/submissions/9761499
/* Description: Given a simple, undirected graph with max
 * degree $D$, computes a ($D + 1$)-coloring of the edges such
 * that no neighboring edges share a color.
 * ($D$-coloring is NP-hard, but can be done for bipartite
 * graphs by repeated matchings of max-degree nodes.)
 * Time: $\mathcal{O}(NM)$. Tested with $N \leq 100, M \leq 5000$ (<0.1 sec)*/
vi edgeColoring(int N, vector<pii> eds) { //nodes 0-based
  vi cc(N + 1), ret(sz(eds)), fan(N), free(N), loc;
  for (pii e : eds) ++cc[e.first], ++cc[e.second];
  int u, v, ncols = *max_element(all(cc)) + 1;
  vector<vi> adj(N, vi(ncols, -1));
  for (pii e : eds) {
    tie(u, v) = e;
    fan[0] = v;
    loc.assign(ncols, 0);
    int at = u, end = u, d, c = free[u], ind = 0, i = 0;
    while (d = free[v], !loc[d] && (v = adj[u][d]) != -1)
      loc[d] = ++ind, cc[ind] = d, fan[ind] = v;
    cc[loc[d]] = c;
    for(int cd = d; at != -1; cd ^= c ^ d, at = adj[at][cd])
      swap(adj[at][cd], adj[end = at][cd ^ c ^ d]);
    while (adj[fan[i]][d] != -1) {
      int left = fan[i], right = fan[++i], e = cc[i];
      adj[u][e] = left;
      adj[left][e] = u;
      adj[right][e] = -1;
      free[right] = e;
    }
    adj[u][d] = fan[i];
    adj[fan[i]][d] = u;
    for (int y : {fan[0], u, end})
      for (int& z = free[y] = 0; adj[y][z] != -1; z++);
  }
  rep(i,0,sz(eds))
    for (tie(u, v) = eds[i]; adj[u][ret[i]] != v;) ++ret[i];
  return ret; //ret[i]= color of the i-th edge
}
