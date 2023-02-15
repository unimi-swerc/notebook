/// Source:
/// https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/GlobalMinCut.h
/// Verification:
/// https://www.spoj.com/problems/DISGRAPH/ (id: 30318042) (archi con peso = 1)
/* Find a global minimum cut in an undirected graph, 
 * as represented by an adjacency matrix. Time: $\mathcal{O}(V^3)$
 * tested with $V \leq 1400$ (12.22 sec) */
pair<int, vi> globalMinCut(vector<vi> mat) { //0-based
  pair<int, vi> best = {INT_MAX, {}};
  int n = sz(mat);//mat[i][j]=0 means there is no arc (i->j)
  vector<vi> co(n); //mat must be symmetric
  rep(i,0,n) co[i] = {i};
  rep(ph,1,n) {
    vi w = mat[0];
    size_t s = 0, t = 0;
    rep(it,0,n-ph) { // $\mathcal{O}(V^2)$ -> $\mathcal{O}(E \log V)$ with prio queue
      w[t] = INT_MIN;
      s = t, t = max_element(all(w)) - w.begin();
      rep(i,0,n) w[i] += mat[t][i];
    }
    best = min(best, {w[t] - mat[t][t], co[t]});
    co[s].insert(co[s].end(), all(co[t]));
    rep(i,0,n) mat[s][i] += mat[t][i];
    rep(i,0,n) mat[i][s] = mat[s][i];
    mat[0][t] = INT_MIN;
  }
  return best;//return {cost,node list of one of the 2 sets}
}
