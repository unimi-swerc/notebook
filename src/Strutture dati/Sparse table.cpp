/// Source: Bortoz
/// Verification:
/// https://oj.uz/submission/675959 (versione con i vector)
/// https://codeforces.com/gym/102428/submission/185955879
/// https://codeforces.com/contest/1748/submission/187560209
/// https://www.acmicpc.net/source/55976125
/// https://atcoder.jp/contests/abc303/submissions/41797597
/// https://training.olinfo.it/#/task/cioccolatini/submissions (id: 1197919)
constexpr int MAXN = 1 << 20, LOGN = 21;
int table[LOGN][MAXN]; //sparse table per il minimo
void build(int N, int* V) { //$\mathcal{O}(N\log{N})$
  copy(V, V + N, table[0]);
  for (int j = 1; j < LOGN; j++) {
    for (int i = 0; i + (1 << j) <= N; i++) {
      table[j][i]=min(table[j-1][i],
                      table[j-1][i+(1<<j)/2]);
    }
  } //0-based (indici di V da 0 a N-1)
}
int query(int l, int r) { //[l, r) ($\mathcal{O}(1)$)
  int k = 31 - __builtin_clz(r - l);
  return min(table[k][l], table[k][r-(1 << k)]);
}
