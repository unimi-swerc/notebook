/// Source:
/// https://cp-algorithms.com/geometry/convex_hull_trick.html
/// Verification:
/// https://www.hackerrank.com/contests/alten-coding-challenge/challenges/approvazione/submissions/code/1338547243
vector<pt> hull, vecs;
// Add line k*x+b, k deve essere crescente
void add_line(ll k, ll b) { //ammortized $\mathcal{O}(n)$
  pt nw = {k, b}; //rappresento la retta come un punto...
  while(!vecs.empty()&&dot(vecs.back(),nw-hull.back())<0){
    hull.pop_back();
    vecs.pop_back();
  }
  if(!hull.empty()) {
    vecs.push_back(complex<ll>(1i)*(nw - hull.back()));
  }
  hull.push_back(nw); // ...e tengo il lower convex hull
}
ll get(ll x) { // Min query, $\mathcal{O}(\log{n})$
  pt query = {x, 1}; //cerca il minimo k*x+1*b
  auto it = lower_bound(vecs.begin(), vecs.end(), query,
              [](pt a, pt b) { return cross(a, b) > 0; });
  return dot(query, hull[it - vecs.begin()]);
}
