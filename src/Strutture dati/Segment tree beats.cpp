/// Source:
/// https://judge.yosupo.jp/submission/35587
/// Verification:
/// https://judge.yosupo.jp/submission/94863
/* 1-based. Estremi degli intervalli inclusi: [l,r]
 * 1 -> CHMIN, 2 -> CHMAX, 3 -> ADD. Time: $\mathcal{O}(\log{(N)})$
 * per query/update con $n,q \leq 2\cdot 10^5$ impiega 600 ms */
const int N = 200005; const long long INF = 1E16;
long long a[N];
struct node {
  long long mi, mx, mis, mxs, sum, lz;
  int mic, mxc;
  node(long long _n = 0) {
    mi = mx = _n; mic = mxc = 1;
    mis = INF; mxs = -INF;
    sum = _n; lz = 0;
  }
  node operator+(const node &oth) const {
    node ans;
    ans.sum = sum + oth.sum;
    if (mi == oth.mi) {
      ans.mi = mi; ans.mic = mic + oth.mic;
      ans.mis = min(mis, oth.mis);
    } else if (mi < oth.mi) {
      ans.mi = mi; ans.mic = mic;
      ans.mis = min(mis, oth.mi);
    } else {
      ans.mi = oth.mi; ans.mic = oth.mic;
      ans.mis = min(mi, oth.mis);
    }
    if (mx == oth.mx) {
      ans.mx = mx; ans.mxc = mxc + oth.mxc;
      ans.mxs = max(mxs, oth.mxs);
    } else if (mx > oth.mx) {
      ans.mx = mx; ans.mxc = mxc;
      ans.mxs = max(mxs, oth.mx);
    } else {
      ans.mx = oth.mx; ans.mxc = oth.mxc;
      ans.mxs = max(mx, oth.mxs);
    }
    return ans;
  }
};
struct segment_tree {
#define m (l + r) / 2
#define lc i * 2
#define rc i * 2 + 1
  node tr[4 * N];
  bool break_condition(int i, long long v, int typ) {
    if (typ == 1) {
      return tr[i].mx <= v;
    } else if (typ == 2) {
      return tr[i].mi >= v;
    } else if (typ == 3) {
      return false;
    }
  }
  bool apply_condition(int i, long long v, int typ) {
    if (typ == 1) {
      return tr[i].mxs < v;
    } else if (typ == 2) {
      return tr[i].mis > v;
    } else if (typ == 3) {
      return true;
    }
  }
  void apply(int i, int l, int r, long long v, int typ) {
    if (typ == 1) {
      tr[i].sum -= (tr[i].mx - v) * tr[i].mxc;
      if (tr[i].mi == tr[i].mx) {
        tr[i].mi = v;
      } else if (tr[i].mis == tr[i].mx) {
        tr[i].mis = v;
      }
      tr[i].mx = v;
    } else if (typ == 2) {
      tr[i].sum += (v - tr[i].mi) * tr[i].mic;
      if (tr[i].mx == tr[i].mi) {
        tr[i].mx = v;
      } else if (tr[i].mxs == tr[i].mi) {
        tr[i].mxs = v;
      }
      tr[i].mi = v;
    } else if (typ == 3) {
      tr[i].sum += (r - l + 1) * v;
      tr[i].mi += v; tr[i].mx += v;
      tr[i].mis = min(INF, tr[i].mis + v);
      tr[i].mxs = max(-INF, tr[i].mxs + v);
      tr[i].lz += v;
    }
  }
  void push(int i, int l, int r) {
    apply(lc, l, m, tr[i].lz, 3);
    apply(rc, m + 1, r, tr[i].lz, 3);
    tr[i].lz = 0;
    for (int op = 1; op <= 2; op++) {
      long long v = (op == 1 ? tr[i].mx : tr[i].mi);
      if (!break_condition(lc, v, op)) {
        apply(lc, l, m, v, op);
      }
      if (!break_condition(rc, v, op)) {
        apply(rc, m + 1, r, v, op);
      }
    }
  }
  void build(int l, int r, int i) {
    if (l == r) {
      tr[i] = node(a[l]);
      return;
    } else {
      build(l, m, lc);
      build(m + 1, r, rc);
      tr[i] = tr[lc] + tr[rc];
    }
  }
  void update(int l,int r,int i,int L,int R,long long v,
                                                int typ){
    if (l > R || r < L || break_condition(i, v, typ)) {
      return;
    } else if(L<=l && r<=R && apply_condition(i, v, typ)){
      apply(i, l, r, v, typ);
      return;
    } else {
      push(i, l, r);
      update(l, m, lc, L, R, v, typ);
      update(m + 1, r, rc, L, R, v, typ);
      tr[i] = tr[lc] + tr[rc];
    }
  }
  //ritorna la somma in [L,R]
  long long query(int l, int r, int i, int L, int R) {
    if (l > R || r < L) {
      return 0;
    } else if (L <= l && r <= R) {
      return tr[i].sum;
    } else {
      push(i, l, r);
      return query(l,m, lc, L, R)+query(m+1,r, rc, L, R);
    }
  }
} seg;
/*uso: cin >> n >> q;
for (int i = 1; i <= n; i++) cin >> a[i];
seg.build(1, n, 1); seg.update(1, n, 1, l, r, v, t);
cout << seg.query(1, n, 1, l, r) << '\n';*/
