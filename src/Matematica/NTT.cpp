/// Source: bortoz
/// Verification:
/// https://www.hackerearth.com/submission/72599930/
/// https://judge.yosupo.jp/submission/86597
/// https://judge.yosupo.jp/submission/86600
ll MOD;//Time:$\mathcal{O}(N\log{N})$, con $N\leq 2^19$ impiega 465 ms
ll MOD1=104857601,MOD2=469762049,MOD3=998244353;
int base = 1;
vector<int> roots = {0, 1};
vector<int> rev = {0, 1};
int max_base = -1;
int root = -1;
int ipow(int b, int e) {
  int r = 1;
  while (e > 0) {
    if (e % 2) r = (ll) r * b % MOD;
    e /= 2;
    b = (ll) b * b % MOD;
  }
  return r;
}
void init() {
  int tmp = MOD - 1;
  max_base = 0;
  while (tmp % 2 == 0) {
    tmp /= 2;
    max_base++;
  }
  root = 2;
  while (ipow(root, (MOD - 1) >> 1) == 1) {
    root++;
  }
  root = ipow(root, (MOD - 1) >> max_base);
}
void reset(){ //for changing the MOD
  max_base=root=-1;
  base=1;
}
void ensure_base(int nbase) {
  if (max_base == -1) init();
  if (nbase <= base) return;
  rev.resize(1 << nbase);
  for (int i = 0; i < (1 << nbase); i++) {
    rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
  }
  roots.resize(1 << nbase);
  while (base < nbase) {
    int z = ipow(root, 1 << (max_base - 1 - base));
    for (int i = 1 << (base - 1); i < (1 << base); i++) {
      roots[i << 1] = roots[i];
      roots[(i << 1) + 1] = (ll) roots[i] * z % MOD;
    }
    base++;
  }
}
void fft(vector<int> &a) {
  int n = a.size();
  int zeros = __builtin_ctz(n);
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
        int x = a[i + j];
        int y = (ll) a[i + j + k] * roots[j + k] % MOD;
        a[i + j] = x + y - MOD;
        if (a[i + j] < 0) a[i + j] += MOD;
        a[i + j + k] = x - y + MOD;
        if (a[i + j + k] >= MOD) a[i + j + k] -= MOD;
      }
    }
  }
}
vector<int> multiply(vector<int> a, vector<int> b) {
  int need = a.size() + b.size() - 1;
  int nbase = 0;
  while ((1 << nbase) < need) nbase++;
  ensure_base(nbase);
  int sz = 1 << nbase;
  a.resize(sz);
  b.resize(sz);
  fft(a);
  fft(b);
  int inv_sz = ipow(sz, MOD - 2);
  for (int i = 0; i < sz; i++) {
    a[i] = (ll) a[i] * b[i] % MOD * inv_sz % MOD;
  }
  reverse(a.begin() + 1, a.end());
  fft(a);
  a.resize(need);
  return a;
}
