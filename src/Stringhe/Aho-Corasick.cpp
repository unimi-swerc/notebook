/// Source:
/// https://cp-algorithms.com/string/aho_corasick.html#construction-of-an-automaton (con aggiunte di MrBrionix)
/// Verification:
/// https://codeforces.com/contest/1437/submission/203227342
/// https://codeforces.com/contest/1252/submission/203227672
/// https://codeforces.com/gym/101741/submission/203227771
/// https://www.acmicpc.net/source/59829587
const int K = 26;
struct Vertex {
  int next[K], go[K], p=-1, link=-1, ind, exitlink=-2;
  bool leaf = false;
  char pch;
  Vertex(int p=-1, char ch='$') : p(p), pch(ch) {
    fill(begin(next), end(next), -1);
    fill(begin(go), end(go), -1);
  }
};
vector<Vertex> t(1);
//Total time:$\mathcal{O}(mk)$ (k=alphabet,m=total strings lengths)
void add_string(string const& s, int num) {
  int v = 0;
  for (char ch : s) {
    int c = ch - 'a';
    if (t[v].next[c] == -1) {
      t[v].next[c] = t.size();
      t.emplace_back(v, ch);
    }
    v = t[v].next[c];
  }
  t[v].leaf = true;
  t[v].ind=num;
}
int go(int v, char ch);
int get_link(int v) {
  if (t[v].link == -1) {
    if (v == 0 || t[v].p == 0)
      t[v].link = 0;
    else
      t[v].link = go(get_link(t[v].p), t[v].pch);
  }
  return t[v].link;
}
int get_exitlink(int v){
  if(t[v].exitlink==-2){
    if(v==0)
      t[v].exitlink=-1;
    else {
      int pos = get_link(v);
      if(t[pos].leaf)
        t[v].exitlink=t[v].link;
      else
        t[v].exitlink=get_exitlink(pos);
    }
  }
  return t[v].exitlink;
}
int go(int v, char ch) {
  int c = ch - 'a';
  if (t[v].go[c] == -1) {
    if (t[v].next[c] != -1)
      t[v].go[c] = t[v].next[c];
    else
      t[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
  }
  return t[v].go[c];
}
