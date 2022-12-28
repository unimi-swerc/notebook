/// Source:
/// https://cp-algorithms.com/dynamic_programming/divide-and-conquer-dp.html
/* This optimization for dynamic programming solutions uses
 * the concept of divide and conquer. It is only applicable
 * for the following recurrence:
 * dp[i][j] = min_{k < j}(dp[i-1][k] + C[k][j])
 * min[i][j] <= min[i][j+1]
 * min[i][j] is the smallest k that gives the optimal answer
 * This optimization reduces the time complexity 
 * from $\mathcal{O}(KN^2)$ to $\mathcal{O}(KN\log N)$
 */
int m, n;
vector<long long> dp_before(n), dp_cur(n);

long long C(int i, int j);
// compute dp_cur[l], ... dp_cur[r] (inclusive)
void compute(int l, int r, int optl, int optr) {
  if (l > r) return;
    
  int mid = (l + r) >> 1;
  pair<long long, int> best = {LLONG_MAX, -1};
    
  for (int k = optl; k <= min(mid, optr); k++) {
    best=min(best, {(k ? dp_before[k - 1]:0)+C(k,mid), k});
  }
    
  dp_cur[mid] = best.first;
  int opt = best.second;
    
  compute(l, mid - 1, optl, opt);
  compute(mid + 1, r, opt, optr);
}
