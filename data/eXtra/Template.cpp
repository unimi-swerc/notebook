#include<bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
//------------------------------------------------
using ll = long long;
using db = long double;
using ul = uint64_t;
using pi = pair<int,int>;
#define f first
#define s second
template<class T> using V = vector<T>; 
using vi = V<int>;
using vb = V<bool>;
using vpi = V<pi>;

#define ft front()
#define sz(x) int((x).size())
#define rsz resize
#define pb push_back
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define each(a,x) for (auto& a: x)
#define eb emplace_back
#define bk back()
#define all(x) begin(x), end(x)

template<class T> bool ckmin(T& a, const T& b) {
  return b < a ? a = b, 1 : 0; } // set a = min(a,b)
  
template<class T> bool ckmax(T& a, const T& b) {
  return a < b ? a = b, 1 : 0; } // set a = max(a,b)
