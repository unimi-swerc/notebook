/// Source (e verification):
/// https://judge.yosupo.jp/submission/61173 (poi MrBrionix ha modificato un pezzo per farlo funzionare con funzioni generiche che si intersecano al più una volta)
/// Verification:
/// https://judge.yosupo.jp/submission/109983
/// https://www.hackerearth.com/submission/76633561/
/// https://dmoj.ca/submission/4972352
/* Lichao tree per il minimo. Utilizzo:
 * int root = -1; //creo un nuovo lichao tree
 * //update: aggiungo k*x+b in [l,r) ($\mathcal{O}(\log{n})$)
 * root = insertLine(root, -C, C, l, r, Line(k, b));
 * //query: trovo il min in x (se non c'è ritorna INF)
 * ll res = getMinPoint(root, -C, C, x); ($\mathcal{O}(\log{n})$)
 * con $n,q \leq 2\cdot 10^5$ impiega 651 ms */
const ll INF = (ll)4e18;
const ll C = (ll)1e9 + 7;
struct Line {
  ll k, b;
  Line() : k(), b(INF) {}
  Line(ll _k, ll _b) : k(_k), b(_b) {}
  ll eval(const ll &x) const { //se non è una linea...
    return k * x + b; //modificare qua
  }
};
struct Node {
  int l, r;
  Line L;
  Node() : l(-1), r(-1), L() {}
};
const int S = (int)8e6;
Node tree[S];
int treeSz;
int getNewNode() {
  tree[treeSz] = Node();
  return treeSz++;
}
int insertLine(int v, ll l, ll r, ll ql, ll qr, Line L) {
  if (l >= qr || ql >= r) return v;
  if (v == -1) {
    v = getNewNode();
    if (ql <= l && r <= qr) {
      tree[v].L = L;
      return v;
    }
  }
  ll m = l + (r - l) / 2;
  if (ql <= l && r <= qr) {
    if (L.eval(m) < tree[v].L.eval(m))
      swap(L, tree[v].L);
    if (L.eval(l) >= tree[v].L.eval(l) && 
      L.eval(r - 1) >= tree[v].L.eval(r - 1)) return v;
    if (L.eval(r - 1) < tree[v].L.eval(r - 1))
      tree[v].r = insertLine(tree[v].r, m, r, ql, qr, L);
    else
      tree[v].l = insertLine(tree[v].l, l, m, ql, qr, L);
    return v;
  }
  if (L.eval(max(l, ql)) >= tree[v].L.eval(max(l, ql))
    && L.eval(min(r, qr)-1)>=tree[v].L.eval(min(r, qr)-1)) 
    return v;
  tree[v].l = insertLine(tree[v].l, l, m, ql, qr, L);
  tree[v].r = insertLine(tree[v].r, m, r, ql, qr, L);
  return v;
}
ll getMinPoint(int v, ll l, ll r, ll x) {
  if (v == -1) return INF;
  if (x < l || x >= r) return INF;
  ll m = l + (r - l) / 2;
  ll ans = tree[v].L.eval(x);
  ans = min(ans, getMinPoint(tree[v].l, l, m, x));
  ans = min(ans, getMinPoint(tree[v].r, m, r, x));
  return ans;
}
