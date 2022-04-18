vector<int> suffix_array(int N, string S) {
  vector<int> ret(N), rnk(2 * N), tmp(N);
  for (int i = 0; i < N; i++) {
    ret[i] = i, rnk[i] = S[i];
  }
  for (int k = 1; k < N; k <<= 1) {
    sort(ret.begin(), ret.end(), [&](int a, int b) {
      return make_pair(rnk[a], rnk[a + k]) < 
        make_pair(rnk[b], rnk[b + k]);
    });
    tmp[ret[0]] = 1;
    for (int i = 1; i < N; i++) {
      tmp[ret[i]] = tmp[ret[i - 1]] + 
        (rnk[ret[i]] != rnk[ret[i - 1]]
         || rnk[ret[i] + k] != rnk[ret[i - 1] + k]);
    }
    copy(tmp.begin(), tmp.end(), rnk.begin());
    if (rnk[ret.back()] == N) break;
  }
  return ret;
}
