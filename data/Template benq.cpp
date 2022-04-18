using ll = long long;
using pi = pair<int,int>;
#define f first
#define s second
template<class T> using V = vector<T>; 
using vi = V<int>;
using vb = V<bool>;
using vpi = V<pi>;

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
