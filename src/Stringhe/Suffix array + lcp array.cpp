/// Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/strings%20(14)/Light/SuffixArray%20(14.4).h
/// Verification:
/// https://oj.uz/submission/839222 (suffix nlogn)
/// https://oj.uz/submission/839224 (suffix lineare)
/// https://codeforces.com/gym/102428/submission/220945368 (suffix nlogn)
/// https://codeforces.com/gym/102428/submission/220945587 (suffix lineare)
/// https://judge.yosupo.jp/submission/158324 (suffix nlogn)
/// https://judge.yosupo.jp/submission/158325 (suffix lineare)
/// https://kilonova.ro/submissions/47310 (suffix nlogn)
/// https://kilonova.ro/submissions/47312 (suffix lineare)
/// https://codeforces.com/gym/104373/submission/220946482 (suffix lineare)
/// https://contest.ucup.ac/submission/283618 (suffix nlogn)
// build suffix array of $S_0,\cdots,S_{n-1}$
struct SuffixArray { //tested with $n \leq 5\cdot 10^5$ (226 ms)
  string S; int N; vi sa, isa, lcp; //N=sz(S)+1=n+1
  void init(string _S) { //$\mathcal{O}(n\log n)$
  N=sz(S=_S)+1;genSa();/*vi s(N);FOR(i,0,N-1)s[i]=S[i]-'a';
sa=sa_is(s,27);isa=vi(N);FOR(i,0,N)isa[sa[i]]=i;*/genLcp();}
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
    build(N-1,lcp); // serve rmq (del booklet)
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
vi sa_is(const vi& s, int upper) { //Suffix array $\mathcal{O}(n)$
  int n=sz(s);if(!n)return {}; vi sa(n);vector<bool> ls(n);
  for(int i=n-1;i--;)ls[i]=s[i]==s[i+1]?ls[i+1]:s[i]<s[i+1];
  vi sum_l(upper), sum_s(upper);
  F0R(i,n) (ls[i] ? sum_l[s[i]+1] : sum_s[s[i]])++;
  F0R(i,upper) { 
    if (i) sum_l[i] += sum_s[i-1];
    sum_s[i] += sum_l[i];
  }
  auto induce = [&](const vi& lms) {
    fill(all(sa),-1); vi buf = sum_s;
    for (int d: lms) if (d != n) sa[buf[s[d]]++] = d;
    buf = sum_l; sa[buf[s[n-1]]++] = n-1;
    F0R(i,n){//do l-type in increasing order,suf[v]>suf[v+1]
      int v = sa[i]-1;
      if (v >= 0 && !ls[v]) sa[buf[s[v]]++] = v;
    }
    buf = sum_l;
    for(int i=n-1; i>=0; --i){
      int v=sa[i]-1;//s-type in decr. order,suf[v]<suf[v+1]
      if (v >= 0 && ls[v]) sa[--buf[s[v]+1]] = v;
    }
  };
  vi lms_map(n+1,-1), lms; int m = 0;
  FOR(i,1,n)if(!ls[i-1] && ls[i])lms_map[i]=m++,lms.pb(i);
  induce(lms);vi sorted_lms;// sorts LMS prefixes
  each(v,sa)if(lms_map[v]!=-1)sorted_lms.pb(v);
  vi rec_s(m); int rec_upper = 0; // smaller subproblem
  FOR(i,1,m){ //compare two lms substrings in sorted order
    int l=sorted_lms[i-1], r=sorted_lms[i]; bool same = 0;
    int end_l = lms_map[l]+1 < m ? lms[lms_map[l]+1] : n;
    int end_r = lms_map[r]+1 < m ? lms[lms_map[r]+1] : n;
    if(end_l-l == end_r-r){
      for (;l < end_l && s[l] == s[r]; ++l,++r);
      if (l != n && s[l] == s[r]) same = 1;
    }
    rec_s[lms_map[sorted_lms[i]]] = (rec_upper += !same);
  }
  vi rec_sa = sa_is(rec_s,rec_upper+1);
  F0R(i,m) sorted_lms[i] = lms[rec_sa[i]];
  induce(sorted_lms); return sa;
} //tested with $n \leq 5\cdot 10^5$ (80 ms),$n \leq 10^6,t\leq 10$ (600 ms)
