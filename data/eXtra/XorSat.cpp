using u32 = uint32_t;

#ifndef NSAT
#define NSAT (512-1)
#endif

/* 0-based, esempio d'us:
    (a XOR c XOR d) ^ (b XOR ¬c XOR d) ^ (a XOR b XOR ¬d)
  vector<vector<u32>> v = {{0, 4, 6}, {2, 5, 6}, 
                           {0, 2, 7}, {0, 3, 5}};
  auto r = xorsat(v);
  cout << r.size() << endl;
  for (auto b : r)
    cout << b << " ";
  cout << endl;
  
  se non c'è soluzione r.size()=0
*/
int gauss(vector<bitset<NSAT+1>> &a, int m,
          vector<bool> &ans){
  int n = a.size();
  vector<int> where (m, -1);
  for (int col = 0, row = 0; col<m && row<n; ++col){
    for (int i = row; i < n; ++i)
      if (a[i][col]) {
        swap (a[i], a[row]);
        break;
      }
    if (!a[row][col]) continue;
    where[col] = row;

    for (int i = 0; i < n; ++i)
      if (i != row && a[i][col])
        a[i] ^= a[row];
    ++row;
  }
  ans.assign(m, 0);
  for (int i = 0; i < m; ++i)
    if (where[i] != -1)
      ans[i] = a[where[i]][m] / a[where[i]][i];
  for (int i = 0; i < n; ++i) {
    int sum = 0;
    for (int j = 0; j < m; ++j)
      sum += ans[j] * a[i][j];
    if (sum != a[i][m])
      return 0;
  }

  for (int i = 0; i < m; ++i)
    if (where[i] == -1)
      return -1;
  return 1;
}

vector<bool> xorsat(const vector<vector<u32>> &f) {
  vector<bitset<NSAT+1>> lines;
  for (auto &p : f) {
    bitset<NSAT+1> line;
    bool disparity = 1;
    for (u32 i : p) {
      disparity ^= i & 1;
      line[i >> 1] = 1;
    }
    line[NSAT] = disparity;
    lines.push_back(line);
  }
  vector<bool> ans(NSAT+1);
  int g = gauss(lines, NSAT, ans);
  if (g != 0)
    return ans;
  return vector<bool>(0);
}
