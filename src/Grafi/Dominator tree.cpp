/// Source:
/// https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Advanced/DominatorTree.h
/// Verification:
/// https://judge.yosupo.jp/submission/110351
/// https://contest.yandex.ru/yacup/contest/42237/problems/B/
/* Assuming that all nodes are reachable from $root,$ $a$
 * dominates $b$ iff every path from $root$ to $b$ passes through
 * $a$. Time:$\mathcal{O}(M\log N)$, tested with $N,M\leq 200000$ (153 ms)*/
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
template<int SZ> struct Dominator { //0-based
  vi adj[SZ], ans[SZ]; //input edges, dominator tree edges
  vi radj[SZ], child[SZ], sdomChild[SZ];
  int label[SZ], rlabel[SZ], sdom[SZ], dom[SZ], co = 0;
  int par[SZ], bes[SZ]; 
  void ae(int a, int b) { adj[a].pb(b); }
  int get(int x) { // DSU with path compression
    // get vertex with smallest sdom on path to root
    if (par[x] != x) {
      int t = get(par[x]); par[x] = par[par[x]];
      if (sdom[t] < sdom[bes[x]]) bes[x] = t;
    }
    return bes[x];
  } 
  void dfs(int x) { // create DFS tree
    label[x] = ++co; rlabel[co] = x; 
    sdom[co] = par[co] = bes[co] = co;
    each(y,adj[x]) {
      if (!label[y]) {
        dfs(y); child[label[x]].pb(label[y]); }
      radj[label[y]].pb(label[x]);
    }
  }
  void init(int root) {
    dfs(root);
    ROF(i,1,co+1) {
      each(j,radj[i]) ckmin(sdom[i],sdom[get(j)]);
      if (i > 1) sdomChild[sdom[i]].pb(i);
      each(j,sdomChild[i]) {
        int k = get(j);
        if (sdom[j] == sdom[k]) dom[j] = sdom[j];
        else dom[j] = k;
      }
      each(j,child[i]) par[j] = i;
    }
    FOR(i,2,co+1) {
      if (dom[i] != sdom[i]) dom[i] = dom[dom[i]];
      ans[rlabel[dom[i]]].pb(rlabel[i]);
    }//ans[i]=children of i in the tree rooted in root
  } //note that if a node isn't reachable...
};  //... it will not be in the tree (but init() works)
