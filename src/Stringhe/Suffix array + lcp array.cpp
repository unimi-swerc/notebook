/// Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/strings%20(14)/Light/SuffixArray%20(14.4).h
/// Verification:
/// https://oj.uz/submission/675696
/// https://codeforces.com/gym/102428/submission/186962324
/// https://judge.yosupo.jp/submission/118350
// build suffix array of $S_0,\cdots,S_{n-1}$
struct SuffixArray { 
    string S; int N; vi sa, isa, lcp; //N=sz(S)+1=n+1
    void init(string _S) { //$\mathcal{O}(n\log n)$
        N = sz(S = _S)+1; genSa(); genLcp(); 
    } //tested with $n \leq 5\cdot 10^5$ (226 ms)
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
    }    //... prefisso più piccolo
    // isa[i] = x t.c. sa[x]=i
    //lcp[i]=lcp tra sa[i] e sa[i+1] ($0\leq i \leq n-1$)
    void genLcp(){
        lcp=vi(N-1); int h=0; //lcp[0]=lcp(sz(S),sa[1])=0
        F0R(b,N-1) { int a = sa[isa[b]-1];
            while (a+h < sz(S) && S[a+h] == S[b+h]) ++h;
            lcp[isa[b]-1] = h; if (h) h--; }
        build(N-1,lcp); // serve rmq (del booklet)
        //ma va modificato con vector<int>& anzichè int*
        //e V.begin() anzichè V
        //if we cut off first chars of two strings with...
    }//...lcp h then remaining portions still have lcp h-1 
    //lcp of suffixes starting at a,b
    int getLCP(int a, int b){
        if (a == b) return sz(S)-a; // a,b sono 0-based
        int l = isa[a], r = isa[b]; if (l > r) swap(l,r);
        return query(l,r); // serve rmq (del booklet)
    }
};
