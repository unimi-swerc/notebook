using u64 = uint64_t;
using i64 = int64_t;

struct hash_pair {
  size_t operator()(const pair<u64, u64>& p) const { 
    return hash<u64>{}((p.first << 32) | p.second); 
  }
};

vector<vector<u64>> DBF(const string &s) {
  size_t n = s.size();
  
  size_t ld = size_t(ceil(log2(n))) + 2;
  vector<vector<u64>> dbf(ld, vector<u64>(n + 1));
  vector<array<u64, 2>> term(n + 1);
  vector<u64> order(n + 1);
  vector<size_t> bucket(n + 1);
  vector<size_t> bucket_size(n + 1);
  vector<size_t> prefix(n + 1);
  unordered_set<char> chars;
  for(size_t i = 0; i < n; i++) {
    chars.insert(s[i]);
  }
  chars.insert('\0');
  vector<char> ordered;
  for(char c : chars) {
    ordered.push_back(c);
  }
  sort(ordered.begin(), ordered.end());
  unordered_map<char, size_t> mapper;
  for(size_t i = 0; i < ordered.size(); i++) {
    mapper[ordered[i]] = i;
  }
  for(size_t i = 0; i < n; i++) {
    dbf[0][i] = mapper[s[i]];
  }
  
  auto radix_sort = [&](int k) {
    fill(bucket_size.begin(), bucket_size.end(), 0);
    for(size_t j = 0; j < n + 1; j++) {
      bucket_size[term[order[j]][k]]++;
    }
    size_t partial = 0;
    for(size_t j = 0; j < n + 1; j++) {
      size_t tmp = bucket_size[j];
      bucket_size[j] = partial;
      partial += tmp;
    }
    for(size_t j = 0; j < n + 1; j++) {
      bucket[bucket_size[term[order[j]][k]]++] = order[j];
    }
    order = bucket;              
  };
  
  for(size_t i = 1; i < dbf.size(); i++) {
    for(size_t j = 0; j < n + 1; j++) {
      term[j][0] = dbf[i - 1][j];
      term[j][1] = dbf[i - 1][(j + (1 << (i - 1))) % (n + 1)];
    }
    iota(order.begin(), order.end(), 0);
    
    radix_sort(1);
    radix_sort(0);
    dbf[i][order[0]] = 0;
    for(size_t j = 1; j < n + 1; j++) {
      auto o = order[j - 1];
      dbf[i][order[j]] = dbf[i][o] + (term[order[j]] != term[o]);
    }
  }
  
  return dbf;
}
