/// Source: https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/geometry%20(13)/Polygons/MinkowskiSum.h
/// Verification: https://open.kattis.com/submissions/12566880
vector<pt> minkowski_sum(vector<pt> a, vector<pt> b){ //$\mathcal{O}(n)$
  if (sz(a) > sz(b)) swap(a, b); if (!sz(a)) return {};
  if (sz(a) == 1) { // $A+B = \{a + b|a \in A, b \in B\}$
    for(auto& t : b){t += a.front();} return b;
  } //a,b: (strictly) convex polygons given in CCW order
  rotate(begin(a), min_element(all(a),comp()), end(a));
  rotate(begin(b), min_element(all(b),comp()), end(b));
  a.pb(a[0]), a.pb(a[1]); b.pb(b[0]), b.pb(b[1]);
  vector<pt> result; int i = 0, j = 0; T crs;
  while (i < sz(a)-2 || j < sz(b)-2) {
    result.pb(a[i]+b[j]);crs=cross(a[i+1]-a[i],b[j+1]-b[j]);
    i += (crs >= 0); j += (crs <= 0);
  } //the distance between two convex polygons P,Q ...
  return result; //... boils down to finding the smallest
} //... distance between a point in P+(−Q) and (0,0)
