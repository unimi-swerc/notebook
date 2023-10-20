/// Source: https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/data-structures/LeftistHeap.h
/// Verification:
///
///
/* Persistent meldable heap. Time: $\mathcal{O}(\log N)$ per meld.
 * Memory: $\mathcal{O}(\log N)$ per meld if copy==true, else $\mathcal{O}(1)$.*/
typedef array<ll,2> KEY; //array<ll,3> per directed mst
typedef struct Heap* ph;
struct Heap { // min heap
  ph l = nullptr, r = nullptr;
  int s = 0; KEY v; // s: path to leaf
  Heap(KEY _v):v(_v) {}
  ll delta = 0;//x i lazy update, somma delta a tutto l'heap
  void prop(bool copy = false) {
    if(delta!=0){
      v[0] += delta;
      if (l){
        if(copy)l = new Heap(*l);
        l->delta += delta;
      }
      if (r){
        if(copy)r = new Heap(*r);
        r->delta += delta;
      }
      delta = 0;
    }
  }
  KEY top() { prop(); return v; }
};
ph meld(ph p, ph q, bool copy = false) {
  if (!p || !q) return p?:q;
  p->prop(copy), q->prop(copy);
  if (p->v > q->v) swap(p,q);
  ph P = (copy ? new Heap(*p) : p);
  P->r = meld(P->r,q);
  if (!P->l || P->l->s < P->r->s) swap(P->l,P->r);
  P->s = (P->r?P->r->s:0)+1; return P;
}
ph ins(ph p, KEY v,bool copy = false) {
  if(p)p->prop(copy); return meld(p,new Heap(v),copy); }
ph pop(ph p, bool copy = false) {
  p->prop(copy); return meld(p->l,p->r,copy); }
