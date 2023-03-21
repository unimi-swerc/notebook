/// Source: https://github.com/dariost/swerc/blob/master/src/Extra/welzl.cpp
/// Verification:
/// https://www.spoj.com/problems/QCJ4/ (ID: 31063280)
/* Welzl's algorithm: minimum enclosing circle in expected
 * linear time. If there are any duplicate points in the
 * input, be sure to remove them first. */
typedef pair<pt, long double> circle;
circle b_md(const vector<pt>& R) {
  if (R.size() == 0) {
    return {{0, 0}, -1};
  } else if (R.size() == 1) {
    return {R[0], 0};
  } else if (R.size() == 2) {
    return {(R[0] + R[1]) * .5l, abs(R[0] - R[1]) * .5l};
  } else {
    pt center = circumCenter(R[0], R[1], R[2]);
    return {center, abs(R[0] - center)};
  }
}
circle b_minidisk(vector<pt>& P, int i, vector<pt> R) {
  if (i == P.size() || R.size() == 3) {
    return b_md(R);
  } else {
    auto [center, rad] = b_minidisk(P, i + 1, R);
    if (abs(P[i] - center) > rad) {
      R.push_back(P[i]);
      return b_minidisk(P, i + 1, R);
    }
    return {center, rad};
  }
}
circle minidisk(vector<pt> P) { // Call this function.
  shuffle(P.begin(), P.end(), rng);
  return b_minidisk(P, 0, {});
}
