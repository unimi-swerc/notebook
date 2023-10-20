/// Source: 
/// https://github.com/cp-algorithms/cp-algorithms-aux/blob/master/src/polynomial.cpp
/// https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/number-theory%20(11.1)/Modular%20Arithmetic/ModSqrt.h
/// Verification:
/// https://judge.yosupo.jp/submission/139293
/// https://dmoj.ca/submission/5535996
/// https://dmoj.ca/submission/5537684
/// https://judge.yosupo.jp/submission/156783
/// https://judge.yosupo.jp/submission/156789
/// https://www.spoj.com/status/CRYPTO1,mrbrionix/ (ID: 32054385)
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
using mi = modular<mod>; using T = unsigned long long;
unsigned long long sqrt(mi a) { // Time: $\mathcal{O}(\log^2{MOD})$
    mi p = bpow(a,(mod-1)/2); // check if 0 or no sqrt
    if(p.r!=1)return p.r == 0 ? 0 : -1;//-1 if doesn't exist
    T s = mod-1; T r = 0; while (s%2 == 0) s /= 2, ++r;
    mi n = 2; while (bpow(n,(mod-1)/2).r == 1) n = T(n.r)+1;
    // n non-square, $ord(g)=2^r, ord(b)=2^m, ord(g)=2^r, m<r$
    for(mi x=bpow(a,(s+1)/2), b=bpow(a,s), g=bpow(n,s);;){
        if (b.r == 1) return min(x.r,mod-x.r); // x^2=ab
        T m = 0; for (mi t = b; t.r != 1; t *= t) ++m;
        for(int i=0;i<r-m-1;i++) g *= g; //$ord(g)=2^{m+1}$
        x*=g, g*=g, b*=g, r=m;//$ord(g)=2^m, ord(b)<2^m$
    }
} // Tonelli-Shanks algorithm for square roots mod a prime
