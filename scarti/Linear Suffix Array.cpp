using ll = long long;
using db = long double; // or double if tight TL
using str = string;
 
using pi = pair<int,int>;
#define mp make_pair
#define f first
#define s second
 
#define tcT template<class T
tcT> using V = vector<T>; 
tcT, size_t SZ> using AR = array<T,SZ>;
using vi = V<int>;
using vb = V<bool>;
using vpi = V<pi>;
 
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define sor(x) sort(all(x))
#define rsz resize
#define pb push_back
#define ft front()
#define bk back()
 
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)
 
const int MOD = 1e9+7;
const db PI = acos((db)-1);
mt19937 rng(0); // or mt19937_64
 
tcT> bool ckmin(T& a, const T& b) {
    return b < a ? a = b, 1 : 0; } // set a = min(a,b)
tcT> bool ckmax(T& a, const T& b) {
    return a < b ? a = b, 1 : 0; } // set a = max(a,b)
 
constexpr int MAXN = 2'000'006, LOGN = 21;
int table[LOGN][MAXN]; //sparse table per il minimo
void build(int N, vector<int>& V) { //$\mathcal{O}(N\log{N})$
    copy(V.begin(), V.begin() + N, table[0]);
    for (int j = 1; j < LOGN; j++) {
        for (int i = 0; i + (1 << j) <= N; i++) {
            table[j][i]=min(table[j-1][i],
                table[j-1][i+(1<<j)/2]);
        }
    } //0-based (indici di V da 0 a N-1)
}
int query(int l, int r) { //[l, r) ($\mathcal{O}(1)$)
    int k = 31 - __builtin_clz(r - l);
    return min(table[k][l], table[k][r-(1 << k)]);
}
 
struct SuffixArray { //tested with $n \leq 5\cdot 10^5$ (226 ms)
    string S; int N; vi sa, isa, lcp; //N=sz(S)+1=n+1
    void init(string _S) { //$\mathcal{O}(n\log n)$
        N = sz(S = _S)+1; 
        vi s(N);
        for(int i=0;i<N-1;i++)s[i]=S[i]-'a';
        //genSa();
        sa = sa_is(s,27);
        isa.resize(N);
        for(int i=0;i<N;i++){
            isa[sa[i]]=i;
        }  
        genLcp();
    }
    
    vi sa_is(const vi& s, int upper) {
        int n = sz(s); if (!n) return {};
        vi sa(n); vb ls(n); /// is suffix starting at i < suffix starting at i+1
        R0F(i,n-1) ls[i] = s[i] == s[i+1] ? ls[i+1] : s[i] < s[i+1]; 
        /// s-type: less than next suffix -> ls[i] = 1 
        /// l-type: greater than next suffix -> ls[i] = 0
        vi sum_l(upper), sum_s(upper);
        F0R(i,n) (ls[i] ? sum_l[s[i]+1] : sum_s[s[i]])++; /// note that s[i] = upper-1 -> !ls[i]
        F0R(i,upper) { 
            if (i) sum_l[i] += sum_s[i-1]; /// sum_l[i] = sum_{j=0}^{i-1}(s_j+l_j)
            sum_s[i] += sum_l[i]; /// sum_s[i] = sum_{j=0}^{i-1}s_j+sum_{j=0}^{i}l_j
        }
        auto induce = [&](const vi& lms) {
            fill(all(sa),-1);
            vi buf = sum_s;
            for (int d: lms) if (d != n) sa[buf[s[d]]++] = d; /// lms is s-type, first few ...
            buf = sum_l; sa[buf[s[n-1]]++] = n-1;
            F0R(i,n) { /// do l-type in increasing order, suf[v] > suf[v+1]
                int v = sa[i]-1;
                if (v >= 0 && !ls[v]) sa[buf[s[v]]++] = v;
            }
            buf = sum_l;
            R0F(i,n) { /// do s-type in decreasing order, suf[v] < suf[v+1]
                int v = sa[i]-1;
                if (v >= 0 && ls[v]) sa[--buf[s[v]+1]] = v; /// lms is s-type, last few ...
            }
        };
        vi lms_map(n+1,-1), lms; int m = 0;
        FOR(i,1,n) if (!ls[i-1] && ls[i]) lms_map[i]=m++, lms.pb(i);
        induce(lms); // sorts LMS prefixes
        vi sorted_lms;each(v,sa)if (lms_map[v]!=-1)sorted_lms.pb(v);
        vi rec_s(m); int rec_upper = 0; // smaller subproblem
        FOR(i,1,m) { // compare two lms substrings in sorted order
            int l = sorted_lms[i-1], r = sorted_lms[i];
            int end_l = lms_map[l]+1 < m ? lms[lms_map[l]+1] : n;
            int end_r = lms_map[r]+1 < m ? lms[lms_map[r]+1] : n;
            bool same = 0; // whether lms substrings are same
            if (end_l-l == end_r-r) {
                for (;l < end_l && s[l] == s[r]; ++l,++r);
                if (l != n && s[l] == s[r]) same = 1;
            }
            rec_s[lms_map[sorted_lms[i]]] = (rec_upper += !same);
        }
        vi rec_sa = sa_is(rec_s,rec_upper+1);
        F0R(i,m) sorted_lms[i] = lms[rec_sa[i]];
        induce(sorted_lms); // sorts LMS suffixes
        return sa;
    }
    
    void genSa() { // sa has size sz(S)+1, sa[0]=sz(S)
        sa = isa = vi(N); sa[0] = N-1; iota(1+all(sa),0);
        sort(1+all(sa),[&](int a,int b){return S[a]<S[b];});
        FOR(i,1,N) { int a = sa[i-1], b = sa[i];
            isa[b] = i > 1 && S[a] == S[b] ? isa[a] : i; }
        for (int len = 1; len < N; len *= 2) { // currently
            // sorted by first len chars
            vi s(sa), is(isa), pos(N); iota(all(pos),0);
            each(t,s){
                int T=t-len;if(T>=0)sa[pos[isa[T]]++]=T;
            }
            FOR(i,1,N) {
                int a = sa[i-1], b = sa[i];
                // verify that nothing goes out of bounds
                isa[b] = is[a]==is[b]&&
                is[a+len]==is[b+len]?isa[a]:i;
            }
        }//sa[i]= indice (0-based) d'inizio i-esimo...
    }  //... prefisso più piccolo
    // isa[i] = x t.c. sa[x]=i
    //lcp[i]=lcp tra sa[i] e sa[i+1] ($0\leq i \leq n-1$)
    void genLcp(){
        lcp=vi(N-1); int h=0; //lcp[0]=lcp(sz(S),sa[1])=0
        F0R(b,N-1) { int a = sa[isa[b]-1];
            while (a+h < sz(S) && S[a+h] == S[b+h]) ++h;
            lcp[isa[b]-1] = h; if (h) h--; }
        //build(N-1,lcp); // serve rmq (del booklet)
        //ma va modificato con vector<int>& anzichè int*
        //e V.begin() anzichè V
        //if we cut off first chars of two strings with...
    } //...lcp h then remaining portions still have lcp h-1
    //lcp of suffixes starting at a,b
    int getLCP(int a, int b){
        if (a == b) return sz(S)-a; // a,b sono 0-based
        int l = isa[a], r = isa[b]; if (l > r) swap(l,r);
        return query(l,r); // serve rmq (del booklet)
    }
};
 
