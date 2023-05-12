/// Source: https://github.com/cp-algorithms/cp-algorithms-aux/blob/master/src/polynomial.cpp
/// Verification:
/// https://judge.yosupo.jp/submission/139295
/// https://judge.yosupo.jp/submission/139296
const int maxn = 1 << 20;//requires modular & fft
template<int m> struct dft {
  static constexpr int split = 1 << 15; vector<cpx> A;
  int64_t rem(int r) const {return 2 * r > m ? r - m : r;}
  dft(vector<modular<m>> const& a, size_t n): A(n) {
    for(size_t i = 0; i < min(n, a.size()); i++)
      A[i]=cpx(rem(a[i].r)%split,rem(a[i].r)/split);
    if(n)fft(A);
  }
  auto operator * (dft const& B) {
    assert(A.size() == B.A.size()); size_t n = A.size();
    if(!n) return vector<modular<m>>();
    vector<cpx> C(n), D(n);
    for(size_t i = 0; i < n; i++) {
      C[i] = A[i] * (B[i] + conj(B[(n - i) % n]));
      D[i] = A[i] * (B[i] - conj(B[(n - i) % n]));
    }
    fft(C); fft(D);
    reverse(begin(C)+1,end(C));reverse(begin(D)+1,end(D));
    int t = 2 * n; vector<modular<m>> res(n);
    for(size_t i = 0; i < n; i++) {
      modular<m> A0=llround(C[i].real()/t);
      modular<m> A1=llround(C[i].imag()/t+D[i].imag()/t);
      modular<m> A2=llround(D[i].real()/t);
      res[i] = A0 + A1 * split - A2 * split * split;
    }
    return res;
  }
  cpx operator [](int i) const {return A[i];}
};
size_t com_size(size_t as, size_t bs) {
  if(!as || !bs) return 0;
  size_t n = as + bs - 1;
  while(__builtin_popcount(n) != 1)n++; return n;
}
template<int m>
void mul(vector<modular<m>> &a, vector<modular<m>> b) {
  auto n = com_size(a.size(),b.size()), A = dft<m>(a,n);
  if(a == b) a = A * A; else a = A * dft<m>(b, n);
}
template<typename T> struct poly { vector<T> a;
  void nor() { // get rid of leading zeroes
    while(!a.empty() && a.back() == T(0)) a.pop_back();
  }
  poly(){}
  poly(T a0) : a{a0}{nor();}
  poly(const vector<T> &t) : a(t){nor();}
  poly operator += (const poly &t) {
    a.resize(max(a.size(), t.a.size()));
    for(size_t i = 0; i < t.a.size(); i++) a[i] += t.a[i];
    nor(); return *this;
  }
  poly operator -= (const poly &t) {
    a.resize(max(a.size(), t.a.size()));
    for(size_t i = 0; i < t.a.size(); i++) a[i] -= t.a[i];
    nor(); return *this;
  }
  poly operator+(const poly &t)const{return poly(*this)+=t;}
  poly operator-(const poly &t)const{return poly(*this)-=t;}
  poly moxk(size_t k) const { // get first k coefficients
    return vector<T>(begin(a), begin(a) + min(k, a.size()));
  }
  poly mul_xk(size_t k) const { // multiply by x^k
    auto res = a; res.insert(begin(res), k, 0);
    return res;
  }
  poly operator*=(const poly &t){mul(a,t.a);nor();return *this;}
  poly operator*(const poly &t)const{return poly(*this)*=t;}
  poly rev(size_t n) const { // computes x^n A(x^{-1})
    auto res = a; res.resize(max(n, res.size()));
    return vector<T>(res.rbegin(), res.rbegin() + n);
  }
  poly rev() const { return rev(deg() + 1); }
  pair<poly, poly> divmod(const poly &b) const { //a mod b
    if(deg() < b.deg()) return {poly{0}, *this};
    int d = deg() - b.deg() + 1;
    poly D=(rev().moxk(d)*b.rev().inv(d)).moxk(d).rev(d);
    return {D, *this - D * b};
  }
  poly operator%(const poly &t)const{return divmod(t).s;}
  T eval(T x) const { // evaluates in single point x
    T res(0);
    for(int i = deg(); i >= 0; i--){ res*=x; res+=a[i];}
    return res;
  }
  int deg() const { return (int)a.size() - 1; }
  bool is_zero() const { return a.empty(); }
  T operator [](int idx) const {
    return idx < 0 || idx > deg() ? T(0) : a[idx];
  }
  poly deriv() { // calculate derivative
    if(deg() + 1 < 1) return poly(T(0));
    vector<T> res(deg());
    for(int i = 1; i <= deg(); i++) res[i-1] = T(i)*a[i];
    return res;
  }
  poly mulx(T a) const { // component-wise mult. with a^k
    T cur = 1; poly res(*this);
    for(int i = 0; i <= deg(); i++){res.a[i]*=cur; cur*=a;}
    return res;
  }
  vector<T> eval(vector<poly> &tree, int v, auto l, auto r){
    if(r - l == 1) return {eval(*l)};
    else {
      auto m = l + (r - l) / 2;
      auto A=(*this%tree[2*v]).eval(tree,2*v,l,m);
      auto B=(*this%tree[2*v+1]).eval(tree,2*v+1,m,r);
      A.insert(end(A), begin(B), end(B)); return A;
    }
  }
  vector<T> eval(vector<T> x){ //eval poly in (x1, ..., xn)
    int n = x.size();
    if(is_zero()) return vector<T>(n, T(0));
    vector<poly> tree(4 * n); bld(tree, 1, all(x));
    return eval(tree, 1, all(x));
  } //$\mathcal{O}(N\log^2N)$, tested with $n\leq 2^{17}$ (2577 ms)
  poly itr(vector<poly> &tree,int v,auto l,auto r,auto ly,auto ry){
    if(r - l == 1) return {*ly / a[0]};
    else {
      auto m = l + (r - l) / 2;
      auto my = ly + (ry - ly) / 2;
      auto A=(*this%tree[2*v]).itr(tree,2*v,l,m,ly,my);
      auto B=(*this%tree[2*v+1]).itr(tree,2*v+1,m,r,my,ry);
      return A * tree[2 * v + 1] + B * tree[2 * v];
    }
  }
  static poly bld(vector<poly> &res,int v,auto L,auto R){
    if(R - L == 1) return res[v] = vector<T>{-*L, 1};
    else {
      auto M = L + (R - L) / 2;
      return res[v]=bld(res,2*v,L,M)*bld(res,2*v+1,M,R);
    }
  }
  static auto inter(vector<T> x,vector<T> y){//interpolate 
    int n = x.size(); vector<poly> tr(4 * n);
    return bld(tr,1,all(x)).deriv().itr(tr,1,all(x),all(y));
  } //$\mathcal{O}(N\log^2N)$, tested with $n \leq 2^{17}$ (2990 ms)
  poly x2() { // P(x) -> P(x^2)
    vector<T> res(2 * a.size());
    for(size_t i = 0; i < a.size(); i++)res[2*i] = a[i];
    return res;
  }
  pair<poly, poly> bisect()const{//P(x) = P0(x) + xP1(x)
    vector<T> res[2];
    res[0].reserve(deg()/2+1); res[1].reserve(deg()/2+1);
    for(int i=0;i<=deg();i++)res[i%2].push_back(a[i]);
    return {res[0], res[1]};
  }
  poly inv(int n) const { // get inverse series mod x^n
    auto Q = moxk(n);
    if(n == 1)return Q[0].inv();
    auto [P0, P1] = Q.mulx(-1).bisect();
    int N = com_size((n + 1) / 2, (n + 1) / 2);
    auto P0f = dft(P0.a, N), P1f = dft(P1.a, N);
    auto TT = dft((
      poly(P0f * P0f) - poly(P1f * P1f).mul_xk(1)
      ).inv((n + 1) / 2).a, N);
    return(poly(P0f*TT).x2()+poly(P1f*TT).x2().mul_xk(1)
      ).moxk(n);
  }
};
