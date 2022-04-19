typedef long long ll;
struct line {
    ll a, b;

    line(ll aa, ll bb) : a(aa), b(bb) {}

    line() = default;

    ll calc(ll x) {
        return x * a + b;
    }
};

/* li chao tree per il minimo
  esempio di utilizzo:
  cords.emplace_back(-INF);
    cords.emplace_back(INF);
    cords.emplace_back(coordinate x utilizzate)
    LiChaoTree T(cords);
    
    per trovare il minimo y in x=p
    T.query(p); //ritorna >=3e18 se non esiste alcun punto
    
    per aggiungere una linea y=ax+b in [l,r)
    T.addLine(l, r, a, b);
*/
struct LiChaoTree {
    const ll INFLL = 4e18;
    vector<int> X;
    vector<line> t;
    int n;

    int getId(int x) {
        int d = lower_bound(X.begin(), X.end(), x) - X.begin();
        assert(0 <= d && d < X.size() && X[d] == x);
        return d;
    }

    explicit LiChaoTree(const vector<int> &id) {
        X = id;
        sort(X.begin(), X.end());
        X.erase(unique(X.begin(), X.end()), X.end());
        n = X.size();
        t.assign(4 * n + 1, line(0, INFLL));
    }

    void go(int v, int tl, int tr, line c) {
        if (t[v].calc(X[tl]) > c.calc(X[tl])) {
            swap(t[v], c);
        }
        if (t[v].calc(X[tr]) <= c.calc(X[tr])) return;
        int tm = (tl + tr) / 2;
        if (t[v].calc(X[tm]) > c.calc(X[tm])) swap(t[v], c);
        if (t[v].calc(X[tl]) < c.calc(X[tl])) {
            go(2 * v + 1, tm + 1, tr, c);
        } else {
            go(2 * v, tl, tm, c);
        }
    }

    void addLine(int v, int tl, int tr, int l, int r, line c) {
        if (l > tr || r < tl) return;
        if (l <= tl && tr <= r) {
            go(v, tl, tr, c);
        } else {
            int tm = (tl + tr) / 2;
            addLine(2 * v, tl, tm, l, r, c);
            addLine(2 * v + 1, tm + 1, tr, l, r, c);
        }
    }

    void addLine(int le, int ri, ll a, ll b) {
        int l = getId(le);
        int r = getId(ri) - 1;
        line c(a, b);
        addLine(1, 0, n - 1, l, r, c);
    }

    ll get(int v, int tl, int tr, int pos) {
        ll val = t[v].calc(X[pos]);
        if (tl == tr) {
            return val;
        }
        int tm = (tl + tr) / 2;
        if (pos <= tm) return min(val, get(2 * v, tl, tm, pos));
        else return min(val, get(2 * v + 1, tm + 1, tr, pos));
    }

    ll query(int p) {
        int pos = getId(p);
        return get(1, 0, n - 1, pos);
    }
};
