constexpr int MAXN = 1 << 20, LOGN = 21;
int table[LOGN][MAXN];
void build(int N, int* V) {
  copy(V, V + N, table[0]);
  for (int j = 1; j < LOGN; j++) {
    for (int i = 0; i + (1 << j) <= N; i++) {
      table[j][i]=min(table[j-1][i],
                      table[j-1][i+(1<<j)/2]);
    }
  }
}
int query(int l, int r) { // [l, r)
  int k = 31 - __builtin_clz(r - l);
  return min(table[k][l], table[k][r-(1 << k)]);
}
