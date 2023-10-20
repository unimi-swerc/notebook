/// Source: Bortoz + https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/HullDiameter.h
/// Verification:
/// https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7820016#1
/// https://cses.fi/problemset/result/6102150/
/// https://qoj.ac/submission/166610
/// https://open.kattis.com/submissions/12056337
vector<pt> convexHullHalf(vector<pt>& v) {
  vector<pt> st;
  for (pt p: v) {
    // $\geq 0$ se si considerano solo gli estremi del ch
    while (st.size() >= 2 &&
                orient(st[st.size()-2],st.back(),p)>0) {
      st.pop_back();
    }
    st.push_back(p);
  }
  return st;
}
//return clockwise hull starting from lefmost point
vector<pt> convexHull(vector<pt> v) { //$\mathcal{O}(n\log{n})$
  sort(v.begin(), v.end(), [](pt a, pt b) {
    return make_pair(a.X, a.Y) < make_pair(b.X, b.Y);
  }); //in case of tie start from the lowest point
  auto up = convexHullHalf(v);
  reverse(v.begin(), v.end());
  auto down = convexHullHalf(v);
  up.pop_back(), down.pop_back();
  up.insert(up.end(), down.begin(), down.end());
  return up;
}
//Returns square of greatest distance between 2 points in $P$
T diameter(vector<pt> S) { //$\mathcal{O}(N)$ given convex hull
  S = convexHull(S); reverse(S.begin(),S.end());
  int n = S.size(), j = n < 2 ? 0 : 1; T res=0;
  for(int i=0;i<j;i++)for (;; j = (j + 1) % n) {
    res = max(res, norm(S[i] - S[j]));
    if(cross(S[(j+1)%n]-S[j],S[i+1]-S[i])>=0)break;
  }
  return res;
} //Nota: vanno considerati solo gli estremi del convex hull
