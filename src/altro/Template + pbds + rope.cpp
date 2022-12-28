/// Source:
/// https://github.com/bqi343/USACO/blob/master/Implementations/content/contest/TemplateShort.cpp
/// https://github.com/kth-competitive-programming/kactl/blob/main/content/contest/template.cpp
/// https://codeforces.com/blog/entry/11080
/// https://www.geeksforgeeks.org/stl-ropes-in-c/
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag, 
tree_order_statistics_node_update> ordered_set;
#include <ext/rope>
using namespace __gnu_cxx;
//------------------------------------------------
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
//------------------------------------------------
using ll = long long;
#define f first
#define s second
template<class T> using V = vector<T>; 
using vi = V<int>;
using vpi = V<pair<int,int>>;

#define sz(x) int((x).size())
#define pb push_back
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define each(a,x) for (auto& a: x)
#define all(x) begin(x), end(x)

template<class T> bool ckmin(T& a, const T& b) {
    return b < a ? a = b, 1 : 0; } // set a = min(a,b)
