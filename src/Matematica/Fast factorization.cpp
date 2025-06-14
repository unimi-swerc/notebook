///Source:
///https://github.com/bqi343/USACO/blob/master/Implementations/content/number-theory%20(11.1)/Primality/MillerRabin.h
///Verification:
///https://dmoj.ca/submission/5161525 (solo prime())
///https://www.spoj.com/problems/FACT0/ (id: 30634459, testa anche factor_rec(), compila solo con __gcd però)
///https://www.codechef.com/viewsolution/83550834
using ul = uint64_t;
ul modMul(ul a, ul b, const ul mod) {
  ll ret = a*b-mod*(ul)((long double)a*b/mod);
  return ret+((ret<0)-(ret>=(ll)mod))*mod; }
ul modPow(ul a, ul b, const ul mod) {
  if (b == 0) return 1;
  ul res = modPow(a,b/2,mod); res = modMul(res,res,mod);
  return b&1 ? modMul(res,a,mod) : res;
}
// Deterministic primality test (up to $2^{64}$)
bool prime(ul n) { // not ll!
  if (n < 2 || n % 6 % 4 != 1) return n-2 < 2;
  ul A[]={2,325,9375,28178,450775,9780504,1795265022},
      s = __builtin_ctzll(n-1), d = n>>s;
  each(a,A) {   // ^ count trailing zeroes
    ul p = modPow(a,d,n), i = s;
    while(p != 1 && p != n-1 && a%n && i--) {
      p=modMul(p,p,n);
    }
    if (p != n-1 && i != s) return 0;
  }
  return 1;
}
// Time: $\mathcal{O}(N^{1/4})$, less for numbers with small factors
ul pollard(ul n) { // return some nontrivial factor of n
  auto f = [n](ul x) { return modMul(x, x, n) + 1; };
  ul x = 0, y = 0, t = 30, prd = 2, i = 1, q;
  while (t++ % 40 || gcd(prd, n) == 1) {
    if (x == y) x = ++i, y = f(x);
    if ((q = modMul(prd, max(x,y)-min(x,y), n))) {
      prd = q;
    }
    x = f(x), y = f(f(y));
  }
  return gcd(prd, n);
}
void factor_rec(ul n, map<ul,int>& cnt) {
  if (n == 1) return;
  if (prime(n)) { ++cnt[n]; return; }
  ul u = pollard(n);
  factor_rec(u,cnt), factor_rec(n/u,cnt);
}
