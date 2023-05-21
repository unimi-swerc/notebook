/// Source: MrBrionix (partendo da quello senza lazy propagation)
/// Verification:
/// https://judge.yosupo.jp/submission/118384 (senza get_pos)
/// https://judge.yosupo.jp/submission/118385 (cont get_pos)
typedef long long T;
mt19937 rng(time(NULL));
constexpr long long mod = 998244353;
// $N\le 500K, Q\le 100K$ (685 ms)
// $N\le 500K, Q\le 500K$ (2900 ms)
struct node {
  int val, mi;
  T sum, lazy1, lazy2;
  int size, rot;
  size_t prior;
  node *left, *right;
  //node *par=nullptr; bool isleft=0; //se serve get_pos
  node(T v) : val(v), mi(v), sum(v), lazy1(1), lazy2(0),
      size(1), rot(0), prior(rng()), left(0), right(0) {}
  static inline void combine(T a, T b, T &c, T &d){
    c=(a*c)%mod;
    d=(a*d+b)%mod;
  }
  //push lazy e calcolo info a partire dai figli
  //convenzione: info vere = info + lazy
  node* fix() {
    mi = val, size = 1, sum = val;
    if (left) {
      left->rot ^= rot;
      mi = min(mi, left->mi);
      sum+=(left->sum*left->lazy1+
      left->size*left->lazy2);
      combine(lazy1,lazy2,left->lazy1,left->lazy2);
      size += left->size;
    }
    if (right) {
      right->rot ^= rot;
      mi = min(mi, right->mi);
      sum+=(right->sum*right->lazy1+
      right->size*right->lazy2);
      combine(lazy1,lazy2,right->lazy1,right->lazy2);
      size += right->size;
    }
    sum%=mod;
    sum= ((sum*lazy1) + (lazy2*size))%mod;
    val = (lazy1*val+lazy2)%mod;
    if (rot) swap(left, right);//+ update di isleft se serve
    rot = lazy2 = 0;
    lazy1 = 1;
    return this;
  }
};
