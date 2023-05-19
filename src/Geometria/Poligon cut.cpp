/// Source: https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/PolygonCut.h
/// Verification:
/// https://icpc.kattis.com/submissions/11083198
/* Returns a vector with the vertices of a polygon
 * with everything to the left of the line going
 * from s to e cut away. (Time: $\mathcal{O}(N)$). Usage:
 * vector<pt> p = ...; //va bene sia orario che antiorario
 * p = polygonCut(p, pt{0,0}, pt{1,0});
 * pt e tutto il resto devono essere complex<double>, tested
 * cutting a rectangle $10^4$ times (EPS = $10^{-3}$, 0.0 sec) */
vector<pt> polygonCut(const vector<pt>& poly, pt s, pt e){
  vector<pt> res;
  rep(i,0,sz(poly)) {
    pt cur = poly[i], prev = i ? poly[i-1] : poly.back();
    bool side = cross(e-s, cur-s) < -1e-9;
    if (side != (cross(e-s, prev-s) < -1e-9)){
      pt out;
      lineIntersection(line(s,e), line(cur,prev), out);
      res.push_back(out);
    }
    if(side) res.push_back(cur);
  }
  return res;
}
