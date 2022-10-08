int sa[MAXN], rnk[2*MAXN], lcp[MAXN], tmp[MAXN];
void suffix_array(int N, const string& S) {
  //se usi suffix_array() più di una volta azzera rnk qua
  for (int i = 0; i < N; i++) {
    sa[i] = i, rnk[i] = S[i];
  }
  for (int k = 1; k < N; k *= 2) {
    sort(sa, sa + N, [&](int a, int b) {
      return tie(rnk[a],rnk[a+k]) < tie(rnk[b],rnk[b+k]);
    });
    tmp[sa[0]] = 1;
    for (int i = 1; i < N; i++) {
      tmp[sa[i]] = tmp[sa[i-1]] + (rnk[sa[i]] !=
        rnk[sa[i-1]] || rnk[sa[i]+k] != rnk[sa[i-1]+k]);
    }
    copy(tmp, tmp + N, rnk);
    if (rnk[sa[N - 1]] == N) break;
  }
}
void lcp_array(int N, const string& S) {
  for (int i = 0, k = 0; i < N; i++) {
    int j = sa[rnk[i]];
    while (i+k < N && j+k < N && S[i+k] == S[j+k]) k++;
    lcp[rnk[i] - 1] = k;
    k = max(k - 1, 0);
  }
}
