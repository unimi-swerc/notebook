/// Source: 
/// https://codeforces.com/blog/entry/110844
/// https://noshi91.github.io/Library/algorithm/concave_max_plus_convolution.cpp
/// Verification:
/// https://oj.uz/submission/745241
/// https://atcoder.jp/contests/abc218/submissions/41520696
/* smawk for (max,+) convolution, complexity: $\mathcal{O}(N)$
 * tested in a $\mathcal{O}(4N\log N)$ solution ($N\leq 2\cdot 10^5$, 913 ms)*/
template <class Select>
vector<int> smawk(const int row_size, const int col_size,
  const Select &sel){
  using vi = vector<int>;
  const function<vi(const vi&,const vi&)> solve =
    [&](const vi &row, const vi &col) -> vi{
    const int n = row.size();
    if (n == 0) return {};
    vi c2, r2;
    for(const int i : col){
      while(!c2.empty()&&sel(row[c2.size()-1],c2.back(),i))
        c2.pop_back();
      if (c2.size() < n) c2.push_back(i);
    }
    for(int i = 1; i < n; i += 2) r2.push_back(row[i]);
    const vi a2 = solve(r2, c2); vi ans(n);
    for(int i = 0; i != a2.size(); i += 1) ans[i*2+1]=a2[i];
    int j = 0;
    for(int i = 0; i < n; i += 2){
      ans[i] = c2[j];
      const int end = i + 1 == n ? c2.back() : ans[i + 1];
      while (c2[j] != end){
        j += 1;
        if(sel(row[i], ans[i], c2[j])) ans[i] = c2[j];
      }
    }
    return ans;
  };
  vi row(row_size);iota(row.begin(), row.end(), 0);
  vi col(col_size);iota(col.begin(), col.end(), 0);
  return solve(row, col);
}
template <class T> // a qualsiasi, b convesso
vector<T> conv(const vector<T> &a, const vector<T> &b){
  const int n = a.size(); const int m = b.size();
  const auto get = [&](const int i, const int j){
    return a[j] + b[i - j];
  };
  const auto sel=[&](const int i,const int j,const int k){
    if (i < k) return false;
    if (i - j >= m) return true;
    return get(i, j) <= get(i, k);
  };
  const vector<int> amax = smawk(n + m - 1, n, sel);
  vector<T> c(n + m - 1);
  for (int i = 0; i != n + m - 1; i += 1)
    c[i] = get(i, amax[i]);
  return c;
} //$\mathit{ans}_i=\max_{j+k=i}(A_j+B_k)$
