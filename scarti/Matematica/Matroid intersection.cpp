/// Source: https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/combinatorial%20(11.2)/MatroidIsect.h
/// Verification:
/// https://www.spoj.com/problems/COIN/ (ID: 32057979)
template<class M1, class M2> struct MatroidIsect {
  int n; V<bool> iset; M1 m1; M2 m2;//iset=vettore soluzione
  bool augment() {
    vi pre(n+1,-1); queue<int> q({n});
    while (sz(q)) {
      int x = q.front(); q.pop();
      if (iset[x]) {
        m1.clear(); F0R(i,n)if(iset[i] && i != x) m1.ins(i);
        F0R(i,n) if(!iset[i] && pre[i] == -1 && m1.indep(i))
          pre[i] = x, q.push(i);
      } else {
        auto backE = [&]() { // back edge
          m2.clear(); 
      F0R(c,2)F0R(i,n)if((x==i||iset[i])&&(pre[i]==-1)==c){
        if(!m2.indep(i))return c?pre[i]=x,q.push(i),i:-1;
            m2.ins(i); }
          return n; 
        };
        for (int y; (y = backE()) != -1;) if (y == n) { 
          for(; x != n; x = pre[x]) iset[x] = !iset[x];
          return 1; }
      }
    }
    return 0;//$\mathcal{O}(GI^{1.5})$ calls to oracles, where $G$ is
  } //size of ground set and $I$ is size of independent set
  MatroidIsect(int n, M1 m1, M2 m2):n(n), m1(m1), m2(m2) {
    iset.assign(n+1,0); iset[n] = 1;
    m1.clear(); m2.clear(); // greedily add to basis
    for(int i=n-1;i>=0;i--)if(m1.indep(i) && m2.indep(i))
      iset[i] = 1, m1.ins(i), m2.ins(i); 
    while (augment());
  }
};// MatroidIsect<Gmat,Cmat> M(sz(ed),Gmat(ed),Cmat(col));
