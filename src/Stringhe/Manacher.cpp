/// Source: Bortoz
/// Verification:
/// https://www.spoj.com/problems/NUMOFPAL/ (id: 29983634)
pair<vector<int>, vector<int>> manacher(string S) {
  int N = S.size(); //Time: $\mathcal{O}(N)$
  vector<int> even(N), odd(N);
  for (int i=0, l=0, r=-1; i<N; i++) {
    int k = (i>r) ? 0 : min(even[l+r-i+1], r-i+1);
    while (0 <= i-k-1 && i+k<N && S[i-k-1] == S[i+k])
      k++;
    even[i] = k--;
    if (i+k > r) {
        l = i-k-1;
        r = i+k;
    }
  }//even[i]=numpal centrati tra i-1 e i (even[0]=0)
  for (int i=0, l=0, r=-1; i<N; i++) {
    int k = (i>r) ? 1 : min(odd[l+r-i], r-i+1);
    while (0 <= i-k && i+k < N && S[i-k] == S[i+k])
      k++;
    odd[i] = k--;
    if (i+k > r) {
      l = i-k;
      r = i+k;
    }
  } //odd[i] = numpal centrati in i
  return {even, odd};
}
