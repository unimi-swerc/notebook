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
// versione $\mathcal{O}(n\log^2n)$ potenziata con ds ($\mathcal{O}(\log n)$ per upd)
void divide_conquer(int l, int r, int l_opt, int r_opt){
  int mid = (l + r) / 2, opt = -1;

  ll best_delta = 1; //qua la ricorrenza è verso sx
  FOR(i, max(l_opt, d[mid]), r_opt + 1) {
    upd(a[i], 1);
    int inv=1-que(a[i]+1,a[d[mid]]-1)-que(a[i],a[d[mid]]);
    if (inv <= best_delta) best_delta = inv, opt = i;
  }
  ans = min(ans, best_delta);

  if (mid != r) {
    FOR(i, d[mid], d[(mid + r + 1) / 2]) upd(a[i], -1);
    FOR(i, max(opt, d[(mid+r+1)/2]), r_opt+1) upd(a[i], -1);
    divide_conquer(mid + 1, r, opt, r_opt);
    FOR(i, d[mid], d[(mid + r + 1) / 2]) upd(a[i], 1);
    FOR(i, max(opt, d[(mid+r+1)/2]), r_opt+1) upd(a[i], 1);
  }

  if (mid != l) {
    FOR(i, d[(mid+l-1)/2], min(l_opt,d[mid]))upd(a[i],1);
    FOR(i, max(l_opt, d[mid]), r_opt + 1) upd(a[i], -1);
    divide_conquer(l, mid - 1, l_opt, opt);
    FOR(i, d[(mid+l-1)/2], min(l_opt,d[mid]))upd(a[i],-1);
    FOR(i, max(l_opt, d[mid]), r_opt + 1) upd(a[i], 1);
  }

  FOR(i, max(l_opt, d[mid]), r_opt + 1) upd(a[i], -1);
}
