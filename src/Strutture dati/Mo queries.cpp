/// Source:
/// https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/MoQueries.h
/// Verification:
/// https://www.hackerearth.com/submission/72640530/ (moTree)
/// https://www.spoj.com/problems/DQUERY/ (mo, id: 30185129)
/// https://training.olinfo.it/#/task/ois_notdivisible (moTree, id: 949678)
/// ois notdivisible
// If values are on tree edges, change $\texttt{step}$ to add/remove 
// the edge $(a, c)$ and remove the initial $\texttt{add}$ call 
// (but keep $\texttt{in}$) Time: $\mathcal{O}(N \sqrt{Q})$
// add a[ind] (end = 0 or 1)
void add(int ind, int end) { return; } 
// remove a[ind]
void del(int ind, int end) { return; } 
// compute current answer
int calc() { return 0; } 
// Q[i] = [l,r) query, 0-based
//con $n \leq 3\cdot 10^4, q \leq 2\cdot 10^5$, O(1) add/del/calc impiega 0.39 sec
vi mo(vector<pii> Q) { 
  int L = 0, R = 0, blk = 350; // $\approx N / \sqrt{Q}$
  vi s(sz(Q)), res = s;
#define K(x) pii(x.first/blk, x.second ^ -(x.first/blk & 1))
  iota(all(s), 0);
  sort(all(s), [&](int s, int t){ return K(Q[s])<K(Q[t]);});
  for (int qi : s) {
    pii q = Q[qi];
    while (L > q.first) add(--L, 0);
    while (R < q.second) add(R++, 1);
    while (L < q.first) del(L++, 0);
    while (R > q.second) del(--R, 1);
    res[qi] = calc();
  }
  return res;
}
// Q[i] = [l,r] query, 0-based
vi moTree(vector<array<int,2>> Q,vector<vi>& ed,int root=0){
  int N = sz(ed), pos[2] = {}, blk = 350; // $\approx N / \sqrt{Q}$
  vi s(sz(Q)), res = s, I(N), L(N), R(N), in(N), par(N);
  add(0, 0), in[0] = 1;
  auto dfs = [&](int x, int p, int dep, auto& f) -> void {
    par[x] = p;
    L[x] = N;
    if (dep) I[x] = N++;
    for (int y : ed[x]) if (y != p) f(y, x, !dep, f);
    if (!dep) I[x] = N++;
    R[x] = N;
  };
  dfs(root, -1, 0, dfs);
#define K(x) pii(I[x[0]] / blk, I[x[1]] ^ -(I[x[0]]/blk &1))
  iota(all(s), 0);
  sort(all(s), [&](int s, int t){return K(Q[s])<K(Q[t]); });
  for (int qi : s) rep(end,0,2) {
    int &a = pos[end], b = Q[qi][end], i = 0;
#define step(c) { if (in[c]) { del(a, end); in[a] = 0; } \
                  else { add(c, end); in[c] = 1; } a = c; }
    while (!(L[b] <= L[a] && R[a] <= R[b]))
      I[i++] = b, b = par[b];
    while (a != b) step(par[a]);
    while (i--) step(I[i]);
    if (end) res[qi] = calc();
  }
  return res;
}
