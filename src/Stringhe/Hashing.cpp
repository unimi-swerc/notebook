/// Source:
/// https://github.com/bqi343/USACO/blob/master/Implementations/content/strings%20(14)/Light/HashRange%20(14.2).h
/// https://codeforces.com/blog/entry/60442
/// Verification:
/// https://www.facebook.com/codingcompetitions/hacker-cup/2022/round-3/problems/C/my-submissions (submission 28 dicembre 2022)
/// https://itacpc22.kattis.com/submissions/10162065
/// https://atcoder.jp/contests/abc284/submissions/37859337
/// tal_rotori
// Polynomial hash for substrings with two bases
mt19937 rng((uint64_t) chrono::duration_cast<chrono::
    nanoseconds>(chrono::high_resolution_clock::now()
                            .time_since_epoch()).count());
constexpr uint64_t MOD = (1ull<<61) - 1; //1e9+7ll;
uint64_t modmul(uint64_t a, uint64_t b){ //solo con $2^{61}-1$
  uint64_t l1=(uint32_t)a,h1=a>>32,l2=(uint32_t)b,h2=b>>32;
  uint64_t l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
  uint64_t ret=(l&MOD)+(l>>61)+(h<<3)+(m>>29)+(m<<35>>3)+1;
  ret = (ret & MOD) + (ret>>61);
  ret = (ret & MOD) + (ret>>61);
  return ret-1;
}
using H = array<long long,2>; //array<int,2>;
H makeH(char c) { return {c,c}; }
uniform_int_distribution<ll> BDIST(0.1*MOD,0.9*MOD);//<int>
const H base{BDIST(rng),BDIST(rng)};
H operator+(H l, H r) { 
  F0R(i,2) if ((l[i] += r[i]) >= MOD) l[i] -= MOD;
  return l; }
H operator-(H l, H r) { 
  F0R(i,2) if ((l[i] -= r[i]) < 0) l[i] += MOD;
  return l; }
H operator*(H l, H r) { 
  F0R(i,2) l[i] = modmul(l[i],r[i]);//(ll)l[i]*r[i]%MOD;
  return l; }
// H& operator+=(H& l, H r) { return l = l+r; }
// H& operator-=(H& l, H r) { return l = l-r; }
// H& operator*=(H& l, H r) { return l = l*r; }
V<H> pows{{1,1}};
struct HashRange { // 0-based, estremi l e r sono inclusi
  string S; V<H> cum{{}};
  void add(char c){S+=c; cum.pb(base*cum.back()+makeH(c));}
  void add(string s) { each(c,s) add(c); }
  void extend(int len) { while (sz(pows) <= len) 
    pows.pb(base*pows.back()); }
  H hash(int l, int r) { int len = r+1-l; extend(len);
    return cum[r+1]-pows[len]*cum[l]; }
};
