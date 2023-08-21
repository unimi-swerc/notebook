/// Source: https://github.com/cp-algorithms/cp-algorithms-aux/blob/master/src/polynomial.cpp
/// Verification:
/// https://judge.yosupo.jp/submission/139293
/// https://dmoj.ca/submission/5535996
/// https://dmoj.ca/submission/5537684
/// https://judge.yosupo.jp/submission/156783
/// https://judge.yosupo.jp/submission/156789
template<typename T> T bpow(T x, size_t n) {
  if(n == 0) return T(1);
  else{auto t=bpow(x, n/2); t=t*t; return n%2 ? x*t : t;}
}
template<int m> struct modular {
  int r; typedef modular mo;
  constexpr modular(): r(0) {}
  constexpr modular(int64_t rr): r(rr%m){if(r<0)r+=m;}
  mo inv() const {return bpow(*this, m - 2);}
  mo operator-()const{return r ? m - r : 0;}
  mo operator*(const mo &t)const{return (ll)r*t.r%m;}
  mo operator/(const mo &t)const{return *this*t.inv();}
  mo operator+=(const mo &t){
    r += t.r; if(r >= m) r -= m; return *this;}
  mo operator-=(const mo &t){
    r -= t.r; if(r < 0) r += m; return *this;}
  mo operator+(const mo &t)const{return mo(*this)+=t;}
  mo operator-(const mo &t)const{return mo(*this)-=t;}
  mo operator*=(const mo &t){return *this=*this*t;}
  bool operator==(const mo &t)const{return r==t.r;}
  bool operator>(const mo &t)const{return r>t.r;}
  bool operator<=(const double &t)const{return r<=int(t);}
  bool operator>(const double &t)const{return r>int(t);}
};
template<int m> modular<m> fabs(modular<m> x){return x.r;}
