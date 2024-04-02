/// Source: https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/data-structures/LeftistHeap.h
/// Verification:
/// https://open.kattis.com/submissions/13365429 (usato lazy ma non persistent)
/// https://judge.yosupo.jp/submission/200139 (usato persistente ma non lazy)
/// https://codeforces.com/contest/1942/submission/254690952 (usato persistente ma non lazy)
/* Persistent meldable heap. Time: $\mathcal{O}(\log N)$ per meld.
 * Memory: $\mathcal{O}(\log N)$ per meld if copy==true, else $\mathcal{O}(1)$.*/
typedef array<ll,2> KEY; //array<ll,3> per directed mst
typedef shared_ptr<struct Heap> ph; //oppure struct Heap* ph
template<class... Args> //con copy=true diventa persistente
static ph make_ph(Args&&... args){ //utile con persistenza
    return make_shared<Heap>(forward<Args>(args)...);
} //altrimenti metti new Heap(forward<Args>(args)...);
struct Heap { // min heap wrt KEY
  ph l = nullptr, r = nullptr;
  int s = 0; KEY v; // s: path to leaf
  Heap(KEY _v):v(_v) {}
  ll delta = 0;//x i lazy update, somma delta a tutto l'heap
  void prop(bool copy = false) {
    if(delta!=0){
      v[0] += delta; // chiave += delta
      if (l){
        if(copy)l = make_ph(*l);
        l->delta += delta;
      }
      if (r){
        if(copy)r = make_ph(*r);
        r->delta += delta;
      }
      delta = 0;
    }
  }
  KEY top() { prop(); return v; }
};//$\mathcal{O}(n^2)$ meld,$n \leq 2500$->4.0 s|$\mathcal{O}(m)$ meld,$m \leq 3\cdot 10^5$->750 ms
ph meld(ph p, ph q, bool copy = false) { //con $n \leq 2500$...
  if (!p || !q) return p?:q; //l'Heap è non persistente...
  p->prop(copy), q->prop(copy);//e usa ph = struct Heap*
  if (p->v > q->v) swap(p,q);
  ph P = (copy ? make_ph(*p) : p);
  P->r = meld(P->r,q);
  if (!P->l || P->l->s < P->r->s) swap(P->l,P->r);
  P->s = (P->r?P->r->s:0)+1; return P;
} //esempio d'uso: vedi directed MST
ph ins(ph p, KEY v,bool copy = false) {
  if(p)p->prop(copy); return meld(p,make_ph(v),copy); }
ph pop(ph p, bool copy = false) {
  p->prop(copy); return meld(p->l,p->r,copy); }
