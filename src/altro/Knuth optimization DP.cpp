/// Source:
/// https://cp-algorithms.com/dynamic_programming/knuth-optimization.html
/* Knuth's Optimization in dynamic programming 
specifically applies for optimal tree problems. 
It is only applicable for the following recurrence:
dp[i][j] = min_{i < k < j}(dp[i][k] + dp[k][j] + C[i][j])
min[i][j-1] <= min[i][j] <= min[i+1][j]
min[i][j] is the smallest k that gives the optimal answer
This optimization reduces the time complexity 
from $\mathcal{O}(N^3)$ to $\mathcal{O}(N^2)$*/
long long dp[SIZE][SIZE],mid[SIZE][SIZE],pos[SIZE],n,m;
cin>>p[1]>>p[2]>>...>>p[m];
pos[0] = 0;pos[m + 1] = n;
// length of section of cuts to compute
for (int i = 0; i <= m + 1; i++) {
  // section of cuts to compute: [j, j + i]
  for (int j = 0; j + i <= m + 1; j++) {
    if (i < 2) {
      dp[j][j + i] = 0ll;
      mid[j][j + i] = j;
      continue;
    }
    dp[j][j + i] = 1ll << 60;
    // optimal place to cut
    for (int k=mid[j][i+j-1]; k<=mid[j+1][i+j]; k++) {
      long long next = dp[j][k] + dp[k][j+i]
                         + pos[j+i] - pos[j];
      if (next < dp[j][j+i]) {
        dp[j][j+i] = next, mid[j][j+i] = k;
      }
    }
  }
}
printf("%lld\n", dp[0][m + 1]);
