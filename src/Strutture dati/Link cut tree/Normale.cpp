/// Source:
/// https://judge.yosupo.jp/submission/13926 (completo)
/// https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Advanced/LCT.h (ridotto)
/// Verification:
/// https://judge.yosupo.jp/submission/139388 (completo)
/// https://judge.yosupo.jp/submission/139389 (completo)
/// https://judge.yosupo.jp/submission/139390 (completo)
/// https://codeforces.com/contest/1681/submission/205638292 (ridotto)
/// https://judge.yosupo.jp/submission/139391 (ridotto)
/// https://judge.yosupo.jp/submission/139392 (ridotto)
/// https://qoj.ac/submission/168154 (ridotto)
typedef long long ll;
#define F0R(i,a) for (int i = (0); i < (a); ++i)
const int MX = 2e5+5;
/* Link-Cut Tree. Given a function $f(1 \ldots N) \rightarrow 1 \ldots N$,
 * evaluates $f^b(a)$ for any $a,b$. $\texttt{sz}$ is for path queries; 
 * $\texttt{sub}$, $\texttt{vsub}$ are for subtree queries. $\texttt{x->access()}$
 * brings $\texttt{x}$ to the top and propagates it; its left subtree
 * will be the path from $\texttt{x}$ to the root and its right
 * subtree will be empty. Then $\texttt{sub}$ will be the number of
 * nodes in the connected component of $\texttt{x}$ and $\texttt{vsub}$ will be
 * the number of nodes under $\texttt{x}$.
 * Use $\texttt{makeRoot}$ for arbitrary path queries.
 * Time: $\mathcal{O}(\log{N})$
 * Usage: FOR(i,1,N+1) {
 *   LCT[i]=new snode(i); link(LCT[1],LCT[2],1);} 
 * RIDOTTO: testato su vertex add + path sum
 * e su vertex add + subtree sum
 * con $N,M \leq 2\cdot 10^5$ impiega 539 ms
 * COMPLETO: testato come RIDOTTO e anche 
 * su Subtree add + Subtree sum
 * con $N,M \leq 2\cdot 10^5$ impiega 0.9/1.1 sec 
 *la versione ridotta è senza subtree update, usare solo uno
 *dei due codici tra VERSIONE COMPLETA e VERSIONE RIDOTTA*/
typedef struct snode* sn;
struct snode { //////// VARIABLES
  sn p, c[2]; // parent, children
  bool flip = 0; // subtree flipped or not
  int sz; // value in node, # nodes in current splay tree
  // VERSIONE COMPLETA ###############################
  ll sub; // numero di nodi nella sua componente
  ll vsub = 0; //num nodi nel suo sottoalbero (lui escluso)
  ll val; // dato contenuto nel nodo
  ll sum; // somma dal nodo alla sua radice
  ll vsubSum = 0; //somma del suo sottoalbero (lui escluso)
  ll subSum = 0; //somma della sua componente
  ll addPath = 0, addVir = 0; //lazy val
  snode(ll _val) : val(_val) {
    p = c[0] = c[1] = NULL; calc(); }
  friend int getSz(sn x) { return x?x->sz:0; }
  friend ll getSub(sn x) { return x?x->sub:0; }
  friend ll getSum(sn x) { return x?x->sum:0; }
  friend ll getSubSum(sn x) { return x?x->subSum:0; }
  void inc(ll x) {
    prop();
    ll old = subSum;
    addPath += x; addVir += x;
    vsubSum += x*vsub; subSum += x*vsub;
    prop();
    assert(subSum-old == x*sub);
  }
  void prop() { // lazy prop
    subSum += addPath*(sub-vsub); 
    // ^^ addVir is already included in subSum
    F0R(i,2) if (c[i]) {
      c[i]->addPath += addPath; c[i]->addVir += addPath;
      c[i]->vsubSum += c[i]->vsub*addPath;
      c[i]->subSum += c[i]->vsub*addPath;
    }
    val += addPath; addPath = 0;
    if (!flip) return;
    swap(c[0],c[1]); flip = 0;
    F0R(i,2) if (c[i]) c[i]->flip ^= 1;
  }
  void calc() { // recalc vals
    F0R(i,2) if (c[i]) c[i]->prop();
    sz = 1+getSz(c[0])+getSz(c[1]);
    sub = 1+getSub(c[0])+getSub(c[1])+vsub;
    sum = val+getSum(c[0])+getSum(c[1]);
    subSum = val+getSubSum(c[0])+getSubSum(c[1])+vsubSum; 
    // ^^ assume vsub, vsubSum are OK
  }
  // VERSIONE RIDOTTA #############################
  ll sub, vsub = 0; // vsub stores sum of virtual children
  ll val, sum;
  snode(ll _val) : val(_val) {
    p = c[0] = c[1] = NULL; calc(); }
  friend int getSz(sn x) { return x?x->sz:0; }
  friend ll getSub(sn x) { return x?x->sub:0; }
  friend ll getSum(sn x) { return x?x->sum:0; }
  void prop() { // lazy prop
    if (!flip) return;
    swap(c[0],c[1]); flip = 0;
    F0R(i,2) if (c[i]) c[i]->flip ^= 1;
  }
  void calc() { // recalc vals
    F0R(i,2) if (c[i]) c[i]->prop();
    sz = 1+getSz(c[0])+getSz(c[1]);
    sub = val+getSub(c[0])+getSub(c[1])+vsub;
    sum = val+getSum(c[0])+getSum(c[1]);
  }
  // ################################################
  //////// SPLAY TREE OPERATIONS
  int dir() {
    if (!p) return -2;
    F0R(i,2) if (p->c[i] == this) return i;
    return -1; // p is path-parent pointer
  } // -> not in current splay tree
  // test if root of current splay tree
  bool isRoot() { return dir() < 0; } 
  friend void setLink(sn x, sn y, int d) {
    if (y) y->p = x;
    if (d >= 0) x->c[d] = y; }
  void rot() { // assume p and p->p propagated
    assert(!isRoot()); int x = dir(); sn pa = p;
    setLink(pa->p, this, pa->dir());
    setLink(pa, c[x^1], x); setLink(this, pa, x^1);
    pa->calc(); calc();
  }
  void splay() {
    while (!isRoot() && !p->isRoot()) {
      p->p->prop(), p->prop(), prop();
      dir() == p->dir() ? p->rot() : rot();
      rot();
    }
    if (!isRoot()) p->prop(), prop(), rot();
    prop();
  }
  sn fbo(int b) { // find by order
    prop(); int z = getSz(c[0]); // of splay tree
    if (b == z) { splay(); return this; }
    return b < z ? c[0]->fbo(b) : c[1] -> fbo(b-z-1);
  }
  //////// BASE OPERATIONS
  // VERSIONE COMPLETA ###################################
  void access() { // bring this to top of tree, propagate
    for (sn v = this, pre = NULL; v; v = v->p) { 
      v->splay(); // now switch virtual children
      if (pre) {
        pre->inc(v->addVir); pre->prop();
        v->vsub -= pre->sub; v->vsubSum -= pre->subSum;
      }
      if (v->c[1]) {
        v->c[1]->prop();
        v->vsub += v->c[1]->sub;
        v->vsubSum += v->c[1]->subSum;
        v->c[1]->inc(-v->addVir);
      }
      v->c[1] = pre; v->calc(); pre = v;
    }
    splay(); assert(!c[1]); // right subtree is empty
  }
  // VERSIONE RIDOTTA ##############################
  void access() { // bring this to top of tree, propagate
    for (sn v = this, pre = NULL; v; v = v->p) {
      v->splay(); // now switch virtual children
      if (pre) v->vsub -= pre->sub;
      if (v->c[1]) v->vsub += v->c[1]->sub;
      v->c[1] = pre; v->calc(); pre = v;
    }
    splay(); assert(!c[1]); // right subtree is empty
  }
  // #################################################
  void makeRoot() { 
    access(); flip ^= 1; access();
    assert(!c[0] && !c[1]); }
  //////// QUERIES
  friend sn lca(sn x, sn y) {
    if (x == y) return x;
    x->access(), y->access(); if (!x->p) return NULL;
    x->splay();
    return x->p?:x; // y was below x in latter case
  } // access at y did not affect x -> not connected
  friend bool connected(sn x, sn y) { return lca(x,y); } 
  // # nodes above
  int distRoot() { access(); return getSz(c[0]); } 
  sn getRoot() { // get root of LCT component
    access(); sn a = this; 
    while (a->c[0]) a = a->c[0], a->prop();
    a->access(); return a;
  }
  sn getPar(int b) { // get b-th parent on path to root
    access(); b = getSz(c[0])-b; assert(b >= 0);
    return fbo(b);
  } // can also get min, max on path to root, etc
  //////// MODIFICATIONS
  void set(int v) { access(); val = v; calc(); } 
  friend void link(sn x, sn y, bool force = 0) { 
    assert(!connected(x,y)); 
    if (force) y->makeRoot(); // make x par of y
    else { y->access(); assert(!y->c[0]); }
    x->access(); setLink(y,x,0); y->calc();
  }
  friend void cut(sn y) { // cut y from its parent
    y->access(); assert(y->c[0]);
    y->c[0]->p = NULL; y->c[0] = NULL; y->calc(); }
  friend void cut(sn x, sn y) { // if x, y adj in tree
    x->makeRoot(); y->access(); 
    assert(y->c[0] == x && !x->c[0] && !x->c[1]);
    cut(y); }
};
sn LCT[MX]; int N,Q;
int main() { //utilizzo versione completa
  cin>>N>>Q;
  vector<int> A(N);
  for(int i=0;i<N;i++)cin>>A[i];
  F0R(i,N) LCT[i] = new snode(A[i]);
  F0R(i,N-1) {
    int u,v; cin>>u>>v;
    link(LCT[u],LCT[v],1);
  }
  F0R(i,Q) {
    int t; cin>>t;
    if (t == 0) {
      int u,v,w,x; cin>>u>>v>>w>>x;
      cut(LCT[u],LCT[v]);link(LCT[w],LCT[x],1);
    } else if (t == 1) {
      /*//point update (aggiungi x al nodo p)
        int p,x; cin>>p>>x;
        LCT[p]->access();
        LCT[p]->val += x;
        LCT[p]->calc();*/
      //subtree update 
      // (radice=p, aggiungi x al sottoalbero di v)
      int v,p,x; cin>>v>>p>>x;
      LCT[p]->makeRoot();
      cut(LCT[v]);
      LCT[v]->inc(x);
      link(LCT[p],LCT[v],1);
    } else {
      int u,v; cin>>u>>v;
      /*//path query (query nel path tra u e v)
        LCT[u]->makeRoot();
        LCT[v]->access();
        cout<<(LCT[v]->sum)<<"\n";*/
      //subtree query
      // (v=radice, query sul sottoalbero di u)
      LCT[v]->makeRoot();LCT[u]->access();
      cout<<(LCT[u]->vsubSum + LCT[u]->val)<<"\n";
    }
  }
}
/* utilizzo versione ridotta
 * subtree query (v=radice) è leggermente diverso:
 * LCT[v]->makeRoot();
 * LCT[u]->access();
 * cout<<(LCT[u]->vsub + LCT[u]->val)<<"\n";
 * tutto il resto è uguale al link cut tree completo */
