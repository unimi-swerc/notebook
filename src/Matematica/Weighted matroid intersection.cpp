/// Source: https://github.com/hitonanode/cplib-cpp/blob/master/combinatorial_opt/matroid_intersection.hpp
/// Verification:
/// https://www.spoj.com/problems/COIN/ (ID: 32072307)
/// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1605
/// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_B
template <class M1, class M2, class T = int>
bool augment(M1 &m1, M2 &m2, V<bool> &I, V<T> &w = {}) {
  const int n = m1.size(); m1.set(I); m2.set(I);
  auto weight=[&](int e){return w.empty()?T():w[e]*(n+1);};
  const int gs = n, gt = n + 1; shortest_path<T> sssp(n+2);
  for (int e = 0; e < n; ++e) {
    if (I.at(e)) continue;
    auto c1 = m1.circuit(e), c2 = m2.circuit(e);
    if (c1.empty()) sssp.add_edge(e, gt, T());
    for (int f : c1)
      if (f != e) sssp.add_edge(e, f, -weight(f) + T(1));
    if (c2.empty()) sssp.add_edge(gs, e, weight(e) + T(1));
    for (int f : c2)
      if (f != e) sssp.add_edge(f, e, weight(e) + T(1));
  } //sssp.solve=bellman-ford, retrieve_path=any (min) path
  sssp.solve(gs, gt);auto aug_path=sssp.retrieve_path(gt);
  if(aug_path.empty()) return false;
  for (auto e : aug_path)
    if (e != gs and e != gt) I.at(e) = !I.at(e);
  return true;
} //minimum weight matroid intersection, weights is 0-based
template <class M1, class M2, class T = int> //$\mathcal{O}(Cn^2 + n^3)$
V<bool> MatroidIntersection(M1 m1,M2 m2,V<T> weights ={}){
  const int n = m1.size(); vector<bool> I(n);
  if (weights.empty()) { //n=weights.size(),C=circuit query
    m1.set(I); m2.set(I); // m.size() = n, I[i] = true if...
    for (int e = 0; e < n; ++e) // ...element i is taken
      if (m1.circuit(e).empty() && m2.circuit(e).empty()) {
      I.at(e) = true; m1.set(I); m2.set(I);
    } // m.circuit(e) = {} if I+e is independent, else...
  } // ...is the circuit that contains e
  while (augment(m1, m2, I, weights)); return I;
} // tested with $t\leq 15, n\leq 600$ (0.32 sec)
