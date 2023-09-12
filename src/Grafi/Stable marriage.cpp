/// Source: Dariost (booklet SWERC 2019-2020 LaStatale Blue)
/// https://github.com/dariost/swerc/blob/master/src/Extra/stablemp.cpp
/// Verification:
/// https://www.spoj.com/problems/STABLEMP/ (id: 29454835)
/* Gale-Shapley algorithm for the stable marriage problem.
 * madj[i][j] is the jth highest ranked woman for man i.
 * fpref[i][j] is the rank woman i assigns to man j.
 * rank = 0 -> first preference
 * Returns a pair of vectors (mpart, fpart), where mpart[i]
 * gives the partner of man i, and fpart is analogous.
 * tested with $N\leq 500$ (0.04 sec) ($\mathcal{O}(N^2)$) */
pair<vector<int>, vector<int>>
stable_marriage(vector<vector<int>> &madj,
                vector<vector<int>> &fpref) {
  int n = madj.size(); queue<int> mfree;// 0-based
  vector<int> mpart(n, -1), fpart(n, -1), midx(n);
  for (int i = 0; i < n; i++) {
    mfree.push(i);
  }
  while (!mfree.empty()) {
    int m = mfree.front();
    mfree.pop();
    int f = madj[m][midx[m]++];
    if (fpart[f] == -1) {
      mpart[m] = f;
      fpart[f] = m;
    } else if (fpref[f][m] < fpref[f][fpart[f]]) {
      mpart[fpart[f]] = -1;
      mfree.push(fpart[f]);
      mpart[m] = f;
      fpart[f] = m;
    } else {
      mfree.push(m);
    }
  }
  return make_pair(mpart, fpart);
}
