using u32 = uint32_t;
using u64 = uint32_t;
/* 0-based, esempio d'uso:
 * $(a \lor c \lor d) \wedge (b \lor \neg c \lor d) \wedge (a \lor b \lor \neg d)$
 * $a = 0, \ \neg a = 1, \ b = 2, \ \neg b = 3, \ \ldots$
 * vector<vector<u32>> v={{0, 4, 6},{2, 5, 6},{0, 2, 7}};
 * auto r = sat(v);
 * for (auto b : r) cout << b << " "; cout << endl;
 * se non c'è soluzione r.size()=0
 */

vector<bool> sat(const vector<vector<u32>>& in) {
  u32 max_term = 0;
  for(const auto& v: in) {
    max_term=max(max_term,*max_element(v.begin(),v.end()));
  }
  size_t n = (max_term >> 1) + 1;
  size_t n_clauses = in.size();
  assert(n < 64);
  vector<u64> clause(n_clauses * 2);
  for(size_t i = 0; i < n_clauses; i++) {
    for(u32 t: in[i]) {
      clause[(i << 1) + (t & 1)] |= 1ULL << (t >> 1);
    }
  }
  for(u64 mask = 0; mask < (1ULL << n); mask++) {
    bool valid = true;
    for(size_t i = 0; i < n_clauses && valid; i++) {
      valid &= clause[i << 1] & mask 
        || clause[(i << 1) + 1] & ~mask;
    }
    if(valid) {
      vector<bool> solution(n);
      for(size_t j = 0; j < n; j++) {
        solution[j] = (mask >> j) & 1;
      }
      return solution;
    }
  }
  return vector<bool>();
}
