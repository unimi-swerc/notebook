/// Source: https://github.com/dariost/swerc/blob/master/src/Generic/hornsat.hpp (+ modifiche di MrBrionix)
/// Verification:
/// https://codeforces.com/gym/103202/submission/208679969
using u32 = uint32_t; //0-based, $X = 2*i$, $\mathit{not}(X) = 2*i+1$
/* In ogni clausola solo primo termine può essere positivo e
 * non ci sono clausole vuote.Ritorna {} se insoddisfacibile
 * $n$ = numero di variabili, $m$ = lunghezza totale clausole
 * Complessità: $\mathcal{O}(m)$ ($m \leq 10^6 \implies$ 1.6s)
 * $u\lor \neg p \lor \neg q \lor \cdots \iff u \gets p \land q \land \cdots$
 * $\neg u\lor \neg p \lor \neg q \lor \cdots \iff \mathit{false} \gets u\land p \land q \land \cdots$*/
vector<bool> hornsat(const vector<vector<u32>>& in,int n){
  size_t max_c = 0,variables_left = n;vector<bool> value(n);
  for(const auto& v: in) {
    max_c = max(max_c, v.size());
  }
  for(const auto& v: in)
    if(v.size() == 1 && (v[0]&1)==0) {
    if(!value[v[0] >> 1]) variables_left--;
    value[v[0] >> 1] = true;
  }
  vector<vector<size_t>> neg_instances(n);
  vector<u32> score(in.size());
  vector<vector<size_t>> clauses_with_score(max_c+1);
  for(size_t i = 0; i < in.size(); i++) {
    if((in[i][0]&1)==0 && value[in[i][0] >> 1]) continue;
    if(find(in[i].begin(), in[i].end(), in[i][0] ^ 1)
      != in[i].end()) { continue; }
    u32 s = 0;
    for(size_t j=(in[i][0]&1)==0; j<in[i].size(); j++) {
      neg_instances[in[i][j] >> 1].push_back(i);
      s += !value[in[i][j] >> 1];
    }
    score[i] = s; clauses_with_score[s].push_back(i);
  }
  while(!clauses_with_score[0].empty()) {
    u32 index = clauses_with_score[0].back();
    clauses_with_score[0].pop_back();
    if((in[index][0]&1)==0 && value[in[index][0] >> 1]) {
      score[index] = UINT_MAX; continue;
    }
    if(!variables_left||(in[index][0]&1))return {};
    variables_left--; value[in[index][0] >> 1] = true;
    for(const auto& c: neg_instances[in[index][0] >> 1]) {
      if(score[c] >= clauses_with_score.size()) continue;
      clauses_with_score[--score[c]].push_back(c);
    }
  }
  return value;
}
