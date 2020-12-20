pair<vector<int>, vector<int>> manacher(string S) {
  int N = S.size();
  vector<int> even(N);
  vector<int> odd(N);
  for (int i = 0, l = 0, r = -1; i < N; i++) {
    int k = (i > r) ? 0 : min(even[l+r-i+1], r-i+1);
    while (0 <= i-k-1 && i+k<N && S[i-k-1] == S[i+k])
      k++;
    even[i] = k--;
    if (i + k > r) {
        l = i - k - 1;
        r = i + k ;
    }
  }
  for (int i = 0, l = 0, r = -1; i < N; i++) {
    int k = (i > r) ? 1 : min(odd[l + r - i], r - i + 1);
    while (0 <= i - k && i + k < N && S[i - k] == S[i + k])
      k++;
    odd[i] = k--;
    if (i + k > r) {
      l = i - k;
      r = i + k;
    }
  }
  return {even, odd};
}
