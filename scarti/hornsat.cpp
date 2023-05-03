/// Source: https://github.com/dariost/swerc/blob/master/src/Generic/hornsat.hpp
using u32 = uint32_t;

/// Viene assunto che in ogni clausola il primo termine sia quello positivo
/// Viene assunto che non ci siano clausole vuote
/// Viene assunto che ogni variabile appaia una volta in ogni clausola
vector<bool> hornsat(const vector<vector<u32>>& in) {
  u32 max_term = 0;
  size_t max_clause_size = 0;
  for(const auto& v: in) {
    max_term = max(max_term, *max_element(v.begin(), v.end()));
    max_clause_size = max(max_clause_size, v.size());
  }
  size_t n = (max_term >> 1) + 1;
  size_t variables_left = n;
  vector<bool> value(n);
  for(const auto& v: in) {
    if(v.size() == 1) {
      if(!value[v[0] >> 1])
        variables_left--;
      value[v[0] >> 1] = true;
    }
  }
  vector<unordered_set<size_t>> neg_instances(n);
  vector<u32> score(in.size());
  vector<unordered_set<size_t>> clauses_with_score(max_clause_size);
  for(size_t i = 0; i < in.size(); i++) {
    if(value[in[i][0] >> 1]) {
      continue;
    }
    if(find(in[i].begin(), in[i].end(), in[i][0] ^ 1) != in[i].end()) {
      continue;
    }
    u32 s = 0;
    for(size_t j = 1; j < in[i].size(); j++) {
      neg_instances[in[i][j] >> 1].insert(i);
      s += !value[in[i][j] >> 1];
    }
    score[i] = s;
    clauses_with_score[s].insert(i);
  }
  while(!clauses_with_score[0].empty()) {
    if(!variables_left) {
      return vector<bool>();
    }
    u32 cindex = *clauses_with_score[0].begin();
    clauses_with_score[0].erase(cindex);
    if(value[in[cindex][0] >> 1]) {
      score[cindex] = UINT_MAX;
      continue;
    }
    variables_left--;
    value[in[cindex][0] >> 1] = true;
    for(const auto& c: neg_instances[in[cindex][0] >> 1]) {
      if(score[c] >= clauses_with_score.size()) {
        continue;
      }
      clauses_with_score[score[c]--].erase(c);
      clauses_with_score[score[c]].insert(c);
    }
  }
  return value;
}
