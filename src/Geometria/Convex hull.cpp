/// Source: Bortoz
/// Verification:
/// https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=6958898#1
/// https://cses.fi/problemset/result/5356197/
vector<pt> convexHullHalf(vector<pt>& v) {
  vector<pt> st;
  for (pt p: v) {
    // >= 0 se si considerano solo gli estremi del ch
    while (st.size() >= 2 &&
                orient(st[st.size()-2],st.back(),p)>0) {
        st.pop_back();
    }
    st.push_back(p);
  }
  return st;
}
//return clockwise Hull starting from lefmost point
vector<pt> convexHull(vector<pt> v) { //$\mathcal{O}(n\log{n})$
  sort(v.begin(), v.end(), [](pt a, pt b) {
    return make_pair(a.x, a.y) < make_pair(b.x, b.y);
  }); //in case of tie start from the lowest point
  auto up = convexHullHalf(v);
  reverse(v.begin(), v.end());
  auto down = convexHullHalf(v);
  up.pop_back(), down.pop_back();
  up.insert(up.end(), down.begin(), down.end());
  return up;
}
