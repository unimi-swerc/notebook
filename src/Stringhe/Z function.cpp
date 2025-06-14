/// Source: Bortoz
/// Verification:
/// https://www.codechef.com/viewsolution/64779959
/// https://contest.ucup.ac/submission/283618
vector<int> z_function(string str) { // Time: $\mathcal{O}(N)$
  vector<int> ret(str.size()); int l=0, r=0;
  for (int i=1; i<str.size(); i++) {
    if (i<=r) ret[i] = min(r-i+1, ret[i-l]);
    while (i+ret[i]<str.size() &&
            str[ret[i]]==str[i+ret[i]])
      ret[i]++;
    if (i+ret[i]-1 > r) {
      r = i+ret[i]-1; l = i;
    }
  }
  return ret;
}
