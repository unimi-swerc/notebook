/// Source: Bortoz
/// Verification:
/// https://www.spoj.com/problems/POLYMUL/ (id: 31738225)
/// https://judge.yosupo.jp/submission/156783
/// https://judge.yosupo.jp/submission/156789
/// https://judge.yosupo.jp/submission/156793
/// https://codeforces.com/gym/104373/submission/219925236
/// https://osijek2023s-d2.eolymp.io/problems/10
typedef complex<double> cpx;
int base=1;//tested with dft, $N\leq 2^{19}$ (500 ms)
vector<cpx> roots = {{0, 0}, {1, 0}};
vector<int> rev = {0, 1};
const double PI = acosl(-1.0);
void ensure_base(int nbase) {
  if (nbase <= base) {
    return;
  }
  rev.resize(1 << nbase);
  for (int i = 0; i < (1 << nbase); i++) {
    rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
  }
  roots.resize(1 << nbase);
  while (base < nbase) {
    double angle = 2 * PI / (1 << (base + 1));
    for (int i = 1 << (base - 1); i < (1 << base); i++) {
      roots[i << 1] = roots[i];
      roots[(i<<1)+1] = polar(1.0, angle*(2*i+1-(1<<base)));
    }
    base++;
  }
}
void fft(vector<cpx> &a) {
  int n = a.size(); int zeros = __builtin_ctz(n);
  ensure_base(zeros);
  int shift = base - zeros;
  for (int i = 0; i < n; i++) {
    if (i < (rev[i] >> shift)) {
      swap(a[i], a[rev[i] >> shift]);
    }
  }
  for (int k = 1; k < n; k <<= 1) {
    for (int i = 0; i < n; i += 2 * k) {
      for (int j = 0; j < k; j++) {
        cpx z = a[i + j + k] * roots[j + k];
        a[i + j + k] = a[i + j] - z;
        a[i + j] = a[i + j] + z;
      }
    }
  }
}
vector<cpx> fa, fb; // Time: $\mathcal{O}(N\log{N})$
vector<int> multiply(vector<int> &a, vector<int> &b) {
  int need = a.size() + b.size() - 1, nbase = 0;
  while ((1 << nbase) < need) nbase++;
  ensure_base(nbase);
  int sz = 1 << nbase;
  fa.resize(sz);
  for (int i = 0; i < sz; i++) {
    double x = (i < (int) a.size() ? a[i] : 0);
    double y = (i < (int) b.size() ? b[i] : 0);
    fa[i] = {x, y};
  }
  fft(fa);
  cpx r(0, -0.25 / sz);
  for (int i = 0; i <= (sz >> 1); i++) {
    int j = (sz - i) & (sz - 1);
    cpx z = (fa[j] * fa[j] - conj(fa[i] * fa[i])) * r;
    if (i != j) {
      fa[j] = (fa[i] * fa[i] - conj(fa[j] * fa[j])) * r;
    }
    fa[i] = z;
  }
  fft(fa);
  vector<int> res(need);
  for (int i = 0; i < need; i++) {
    res[i] = real(fa[i]) + 0.5;
  }
  return res; //be careful with int overflow
}
