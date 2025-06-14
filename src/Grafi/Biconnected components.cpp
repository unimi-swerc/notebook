/// Source:
/// https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/BiconnectedComponents.h
/// Verification:
/// https://judge.yosupo.jp/submission/110010
/// https://evaluator.hsin.hr/tasks/HONI222337skrivaca/ (submission 2)
/// https://kilonova.ro/submissions/154619
/// https://qoj.ac/submission/304390
/// https://codeforces.com/contest/1510/submission/243246546
/* Finds all biconnected components in an undirected graph,
 * and runs a callback for the edges in each. In a
 * biconnected component there are at least two distinct
 * paths between any two nodes. Note that a node can be in
 * several components. An edge which is not in a component
 * is a bridge, i.e., not part of any cycle.
 * It works also on disconnected graphs. Usage:
 *  int eid = 0; ed.resize(N); //0-based
 *  for each edge (a,b) {
 *    ed[a].emplace_back(b, eid);
 *    ed[b].emplace_back(a, eid++); }
 *  bicomps([&](const vi& edgelist) {...});
 * Time: $\mathcal{O}(E + V)$. Tested with $N,M \leq 5\cdot 10^5$ (728 ms)
 * it works also with multiple edges (but no self-loops) */
vi num, st; vector<vector<pii>> ed; int Time;
template<class F> int dfs(int at, int par, F& f) {
  int me = num[at] = ++Time, e, y, top = me;
  for (auto pa : ed[at]) if (pa.second != par) {
    tie(y, e) = pa;
    if (num[y]) {
      top = min(top, num[y]);
      if (num[y] < me)
        st.push_back(e);
    } else {
      int si = sz(st); int up = dfs(y, e, f);
      top = min(top, up);
      if (up == me) {
        st.push_back(e);
        f(vi(st.begin() + si, st.end()));
        st.resize(si);
      }
      else if (up < me) st.push_back(e);
      else{/* e is a bridge, call f(vi(1,e))
            for obtaining 2-vertex components */}
    }
  }
  return top;//idea per block cut tree: collego ogni
} //nodo con un nodo che rappresenta la sua bicomp.
template<class F> void bicomps(F f) { //0-based
  num.assign(sz(ed), 0);
  rep(i,0,sz(ed)) if (!num[i]) dfs(i, -1, f);
} //don't forget single-vertex components (if needed)
