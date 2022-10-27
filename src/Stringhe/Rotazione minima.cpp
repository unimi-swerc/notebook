/// Source: Bortoz
/// Verification:
/// https://cses.fi/problemset/view/1110/
int least_rotation(string S) { //$\mathcal{O}(n)$
  S+=S;//tested with $n\leq 10^6$ (0.10 sec)
  vector<int> F(S.size(), -1);
  int k=0;
  for (int j=1; j<S.size(); j++) {
    int i = F[j-k-1];
    while (i != -1 && S[j] != S[k+i+1]) {
      if (S[j] < S[k+i+1]) k = j-i-1;
      i = F[i];
    }
    if (S[j] != S[k+i+1]) {
      if (S[j] < S[k]) k=j;
      F[j-k] = -1;
    } else {
      F[j-k] = i+1;
    }
  }
  return k;
}
