/// Source:
/// https://usaco.guide/plat/centroid?lang=cpp
/// Verification:
/// https://codeforces.com/contest/342/submission/206408466
/// https://judge.yosupo.jp/submission/140347
/// https://judge.yosupo.jp/submission/140409
/// https://qoj.ac/submission/302411
const int MN = 1e5+10, INF = 0x3f3f3f3f;
int N, M, s[MN], m[MN][2], t, b, d;
bool r[MN], red[MN];vector<int> a[MN], v[MN];
//v[i][j]=nodo rosso + vicino a i nel sottoalbero j-esimo
struct info { int n,b,d; };
//g[i] = lista degli antenati di i nel centroid tree
//g[i][j]={antenato x (diverso da i),indice del sottoalbero
// che contiene i in v[x],distanza i->x}
vector<info> g[MN];
int dfs(int n, int p=0){
  s[n]=1;
  for(auto x:a[n])
    if(x!=p&&!r[x])
      s[n]+=dfs(x, n);
  return s[n];
}
int find(int n, int ms, int p=0){
  for(auto x:a[n])
    if(!r[x]&&x!=p&&s[x]*2>ms)
      return find(x, ms, n);
  return n;
}
void dfs2(int n, int p=0){
  for(auto x:a[n])
    if(!r[x]&&x!=p)
      ++d, dfs2(x, n), --d;
  g[n].push_back({t,b,d});
}
void centroid(int n=1){ //1-based
  n = find(n, dfs(n));
  v[n].reserve(a[n].size());
  for(auto x:a[n])
    if(!r[x]){
      t=n, b=v[n].size(), d=1;
      v[n].push_back(INF);
      dfs2(x, n); //aggiorno i g[], se...
    } //... vuoi anche v[n].back()
  r[n]=1;
  for(auto x:a[n])
    if(!r[x])
      centroid(x);
}
int main(){ //tested with $N,M \leq 10^5$ (529 ms)
  scanf("%d%d", &N, &M);
  for(int i=0,u,v;i+1<N;++i) {
    scanf("%d%d", &u, &v);
    a[u].push_back(v),a[v].push_back(u);
  }
  centroid(); memset(m, 0x3f, sizeof m);
  for(int i=0,t=1,n=1;i<=M;++i) {
    if(t==1) { //colora il nodo n di rosso
      for(auto x:g[n]) {
        int &q=v[x.n][x.b];
        if(x.d<q) {
          m[x.n][0]=min(m[x.n][0],x.d); q=x.d;
        }
      }
      red[n]=1; m[n][0]=0;
    } else { // trova il nodo rosso...
      int f=m[n][0]; // ...più vicino a n
      for(auto x:g[n])f=min(f, m[x.n][0]+x.d);
      printf("%d\n", f);
    }
    if(i<M) scanf("%d%d", &t, &n);
  }
}//also tested with contour sum ($N \leq 10^5, Q \leq 2\cdot 10^5$, 835 ms)
