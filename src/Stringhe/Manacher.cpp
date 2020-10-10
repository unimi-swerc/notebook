vector<int> manacher(string str, bool ev = true) {
  vector<int> ret(str.size(), !ev);
  int l = -ev, r = -ev;
  for (int i = !ev; i < str.size() - ev; i++) {
    if (i < r) ret[i] = min(r - i + !ev, ret[l + r - i - ev]);
    while (i - ret[i] >= 0 && i + ret[i] + ev < str.size() &&
        str[i - ret[i]] == str[i + ret[i] + ev]) ret[i]++;
    if (i + ret[i] - !ev > r) l = i - ret[i] + 1, r = i + ret[i] - !ev;
  }
  return ret;
}

