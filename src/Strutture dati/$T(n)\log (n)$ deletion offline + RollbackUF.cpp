/// Source:
/// https://codeforces.com/contest/1681/submission/158216155
/// Verification:
/// https://training.olinfo.it/#/task/ois_police7 (id: 807310)
/// https://training.olinfo.it/#/task/ois_xortree2 (id: 949588)
/// https://codeforces.com/contest/1814/submission/201244020
/// https://codeforces.com/contest/1681/submission/229027300 (test del codice qua sotto, DSU compresa)
/* For a commutative data structure supporting true $\mathcal{O}(T(n))$
 * insertion, support deletion in $\mathcal{O}(T(n)\log n)$ offline. */
struct RollbackUF {
  vector<int> e; vector<pair<int,int>> st;
  RollbackUF(int n) : e(n, -1) {}
  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : find(e[x]); }
  int time() { return st.size(); }
  void rollback(int t) {
    for(int i=time();i-->t;) e[st[i].first] = st[i].second;
    st.resize(t);
  }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    st.push_back({a, e[a]}); st.push_back({b, e[b]});
    e[a] += e[b]; e[b] = a; return true;
  }
};
template<class E> struct query_tree{
  vector<vector<E>> queues; int n;//max query range, 0-based
  query_tree(int n): n(n), queues(n << 1){ }
  void insert(E e, int ql, int qr){ //add $[ql,qr)$
    assert(0 <= ql && ql <= qr && qr <= n);
    auto recurse =[&](auto self, int u, int l, int r)->void{
      if(qr <= l || r <= ql) return;
      if(ql <= l && r <= qr) queues[u].push_back(e);
      else{
        int m=l+(r - l >> 1), v=u+1, w=u+(m - l << 1);
        self(self, v, l, m), self(self, w, m, r);
      }
    };
    recurse(recurse, 0, 0, n);
  }
  // $\mathcal{O}(q \log n)$ insert calls and $\mathcal{O}(n)$ answer calls
  template<class I, class T, class R, class A>
  void solve(I insert, T time, R reverse_to, A answer){
    auto dfs = [&](auto self, int u, int l, int r)->void{
      int timer = time();
      for(auto e: queues[u]) insert(e);
      if(r - l == 1) answer(l);
      else{
        int m = l + (r - l >> 1);
        self(self,u+1,l,m), self(self,u+(m - l << 1),m,r);
      }
      reverse_to(timer);//il reverse va bene anche se...
    }; //torna indietro di una unità di tempo alla volta
    dfs(dfs, 0, 0, n);
  }
};
int main(){ //esempio, con $n\leq 5\cdot 10^5$ impiega 1.3 s
  int n; cin >> n; // tested with $n\leq 2\cdot 10^5$ (873 ms)
  vector<vector<array<int, 2>>> edge(n);
  for(auto i = 0; i < n - 1; ++ i){
    int u, v, c; cin >> u >> v >> c; -- u, -- v, -- c;
    edge[c].push_back({u, v});
  }
  query_tree<array<int, 2>> qt(n);
  for(auto c = 0; c < n; ++ c){
    for(auto [u, v]: edge[c]){
      qt.insert({u, v}, 0, c); qt.insert({u, v}, c + 1, n);
    }
  }
  RollbackUF dsu(n);
  auto insert = [&](array<int, 2> e)->void{
    dsu.join(e[0], e[1]);};
  auto time = [&]()->int{
    return dsu.time();};
  auto reverse_to = [&](int t)->void{
    dsu.rollback(t);};
  long long res = 0;
  auto answer = [&](int c)->void{
    for(auto [u, v]: edge[c])
      res += 1LL * dsu.size(u) * dsu.size(v);
  };
  qt.solve(insert, time, reverse_to, answer);
  cout << res << "\n";
}
