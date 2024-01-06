/// Source: Bortoz
/// Verification:
/// https://oj.uz/submission/745951 (senza get_pos)
/// https://oj.uz/submission/675962 (con get_pos)
/// https://codeforces.com/gym/418635/submission/187058661
/// https://evaluator.hsin.hr/events/ceoi22_2mirror/tasks/SC2022CEOI22measures/ (submission 5)
/// https://www.spoj.com/problems/CERC07S/ (id: 30636184 senza get_pos e 30636194 con get_pos)
/// http://www.usaco.org/index.php?page=viewproblem2&cpid=1357 (con get_pos)
mt19937 rng(time(nullptr));
// Time: randomized $\mathcal{O}(\log{N})$
// per $\approx 1.2\cdot 10^6$ split/merge impiega 1.2 sec
struct node {
  T val, mi; int size, rot;
  size_t prior; node *left, *right;
  //node *par=nullptr; bool isleft=0; se serve get_pos
  node(T v) : val(v), mi(v), size(1), rot(0),
       prior(rng()), left(0), right(0) {}
  node* fix() {
    mi = val, size = 1;
    if (left) {
      mi = min(mi, left->mi);
      size += left->size;
      left->rot ^= rot;
    }
    if (right) {
      mi = min(mi, right->mi);
      size += right->size;
      right->rot ^= rot;
    }
    if (rot) swap(left, right);//+ update di isleft se serve
    rot = 0;
    return this;
  }
};
node* merge(node* a, node* b) {
  if (!a) return b; a->fix();
  if (!b) return a; b->fix();
  if (a->prior > b->prior) {
    auto tmp = merge(a->right, b);
    a->right = tmp;
    //if(tmp)tmp->par = a, tmp->isleft = 0; //x get_pos
    return a->fix();
  } else {
    auto tmp = merge(a, b->left);
    b->left = tmp;
    //if(tmp)tmp->par = b, tmp->isleft = 1; //x get_pos
    return b->fix();
  }
}
//taglio subito dopo k elementi (1-based)
//es. k=1, divido il primo elemento dagli altri
pair<node*, node*> split(node* p, int k) {
  if (!p) return {nullptr, nullptr};
  p->fix();
  int sl = p->left ? p->left->size : 0;
  if (k <= sl) {
    auto [a, b] = split(p->left, k);
    //if(a) a->par = nullptr, a->isleft=0; //per get_pos
    p->left = b;
    //if(b) b->par = p, b->isleft = 1; //per get_pos
    return {a, p->fix()};
  } else {
    auto [a, b] = split(p->right, k-sl-1);
    //if(b) b->par = nullptr, b->isleft=0; //per get_pos
    p->right = a;
    //if(a) a->par = p, a->isleft = 0; //per get_pos
    return {p->fix(), b};
  }//invariante: sui due nodi di ritorno
}  //è sempre stata chiamata ->fix()
int min_pos(node* p) {
  p->fix();
  int sl = p->left ? p->left->size : 0;
  if (p->left && p->left->mi == p->mi) {
    return min_pos(p->left);
  } else if (p->right && p->right->mi==p->mi) {
    return sl + 1 + min_pos(p->right);
  } else {
    return sl;
  }
}
// build treap for [l,r)
node* build(vector<T>& A, int l, int r) {
  if (l + 1 == r) return new node(A[l]);
  int m = (l + r) / 2;
  node* a = build(A, l, m);
  node* b = build(A, m, r);
  return merge(a, b);
}
// ritorna il k-esimo nodo (0-based)
int find_kth(node* p,int pos){
  p->fix();
  int sl = p->left ? p->left->size : 0;
  if (p->left && pos < sl) {
    return find_kth(p->left,pos);
  } else if (p->right && pos > sl) {
    return find_kth(p->right,pos - sl - 1);
  } else {
    return p->val;
  }
}
// dato un node* p, ritorna la sua posizione (0-based)
// nota: non è mai stato testato insieme a rot attivo
int get_pos(node* p){ //modificare split/merge
  if(!p)return -1;  //decommentando le righe x get_pos
  bool flag = (p->par && p->par->rot);
  if(p->isleft ^ flag){
    int rightsize=0;
    if(p->right)rightsize=p->right->size;
    return get_pos(p->par)-rightsize-1;
  }else{
    int leftsize=0;
    if(p->left)leftsize=p->left->size;
    return get_pos(p->par)+leftsize+1;
  }
}
