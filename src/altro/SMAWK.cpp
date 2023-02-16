/// Source: https://codeforces.com/blog/entry/98663
// smawck for (max,+) convolution, complexity: $\mathcal{O}(N)$
template<class F>
vector<int> smawck(F f, const vector<int> &rows,
      const vector<int> &cols) {
  vector<int> ans(rows.size(), -1);
  if((int) max(rows.size(), cols.size()) <= 2) {
    for(int i = 0; i < (int) rows.size(); i++) {
      for(auto j : cols) {
        if(ans[i] == -1 || f(rows[i], ans[i], j)) {
          ans[i] = j;
        }
      }
    }
  } else if(rows.size() < cols.size()) { // reduce
    vector<int> st;
    for(int j : cols) {
      while(1) {
        if(st.empty()) {
          st.push_back(j);
          break;
        }else if(f(rows[(int)st.size()-1], st.back(), j)){
          st.pop_back();
        } else if(st.size() < rows.size()) {
          st.push_back(j);
          break;
        } else {
          break;
        }
      }
    }
    ans = smawck(f, rows, st);
  } else {
    vector<int> newRows;
    for(int i = 1; i < (int) rows.size(); i += 2) {
      newRows.push_back(rows[i]);
    }
    auto otherAns = smawck(f, newRows, cols);
    for(int i = 0; i < (int) newRows.size(); i++) {
      ans[2*i+1] = otherAns[i];
    }
    for(int i = 0, l = 0, r = 0; i < (int)rows.size();i+=2){
      while(l && cols[l-1] >= ans[i-1]) l--;
      if(i+1 == (int) rows.size()) r = (int) cols.size();
      while(r < (int) cols.size() && r <= ans[i+1]) r++;
      ans[i] = cols[l++];
      for(; l < r; l++) {
        if(f(rows[i], ans[i], cols[l])) {
          ans[i] = cols[l];
        }
      }
      l--;
    }
  }
  return ans;
}
/* F(i, j, k) checks if M[i][j] $\leq$ M[i][k]
 * another interpretations is: F(i, j, k) checks if
 * M[i][k] is at least as good as M[i][j] (higher == better)
 * when comparing 2 columns as vectors for j < k, 
 *column j can start better than column k. as soon as column
 * k is at least as good, it's always at least as good */
template<class F>
vector<int> smawck(F f, int n, int m) {
  vector<int> rows(n), cols(m);
  for(int i = 0; i < n; i++) rows[i] = i;
  for(int i = 0; i < m; i++) cols[i] = i;
  return smawck(f, rows, cols);
}
template<class T>
vector<T> MaxConvolutionWithConvexShape(vector<T> anyShape, 
      const vector<T> &convexShape) {
  if((int) convexShape.size() <= 1) return anyShape;
  if(anyShape.empty()) anyShape.push_back(0);
  int n = (int)anyShape.size(), m = (int)convexShape.size();
  auto function = [&](int i, int j) {
    return anyShape[j] + convexShape[i-j];
  };
  auto comparator = [&](int i, int j, int k) {
    if(i < k) return false;
    if(i - j >= m) return true;
    return function(i, j) <= function(i, k);
  };
  const vector<int> best = smawck(comparator, n + m - 1, n);
  vector<T> ans(n + m - 1);
  for(int i = 0; i < n + m - 1; i++) {
    ans[i] = function(i, best[i]);
  }
  return ans;
} //$\mathit{ans}_i=\max_{j+k=i}(A_j+B_k)$
