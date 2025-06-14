/// Source: MrBrionix
/// Verification:
/// https://www.hackerearth.com/submission/72603015/ (è un po modificato perchè andava aggiunto un trick)
/// https://judge.yosupo.jp/submission/135968
/// https://judge.yosupo.jp/submission/85907
/// https://judge.yosupo.jp/submission/85911
/// https://codeforces.com/gym/101669/submission/179461930 (solo LCA)
/// https://evaluator.hsin.hr/tasks/HONI222337skrivaca/ (submission 2, solo LCA)
/// https://dmoj.ca/submission/5874311
/// https://training.olinfo.it/#/task/cioccolatini/submissions (id: 1197919,path_query è modificato, non ci sono update)
/* HLD 1-based (si supponga rt un segment
 * e ^ l'operazione di merge di due segmenti)
 * gli estremi di query e update del segment sono inclusi */
const long long MAXN=200005, LOGN=18;
long long n,q; fun v[MAXN]; vector<int> grafo[MAXN];
int par[MAXN][LOGN],prof[MAXN],siz[MAXN],in[MAXN];
int out[MAXN],rin[MAXN],nex[MAXN],cont;
void dfs(int nodo=0, int last=0, int p=0){
  siz[nodo]=1;
  par[nodo][0]=last;
  prof[nodo]=p;
  for(auto &x : grafo[nodo]){
    if(x!=last){
      dfs(x,nodo,p+1);
      siz[nodo]+=siz[x];
      if(grafo[nodo][0]==last || siz[x]>siz[grafo[nodo][0]])
      {
        swap(x,grafo[nodo][0]);
      }
    }
  }
}
void dfs_hld(int nodo=0, int last=0){
  in[nodo]=cont;
  rin[cont++]=nodo;
  for(auto x : grafo[nodo]){
    if(x!=last){
      if(x==grafo[nodo][0])nex[x]=nex[nodo];
      else nex[x]=x;
      dfs_hld(x,nodo);
    }
  }
  out[nodo]=cont;
}
int lca(int x,int y){ // Time: $\mathcal{O}(\log{N})$
  if(prof[x]>prof[y])swap(x,y);
  for(int i=LOGN-1;i>=0;i--){
    if(prof[par[y][i]]>=prof[x]){
      y=par[y][i];
    }
  }
  if(x==y)return x;
  for(int i=LOGN-1;i>=0;i--){
    if(par[x][i]!=par[y][i]){
      x=par[x][i];
      y=par[y][i];
    }
  }
  return par[x][0];
}
void update(int pos,fun x){
  rt.update(in[pos],x);
}
/* Query sul percorso u->v (u escluso). se flag = 1 il
 * percorso viene fatto al contrario: v->u (u escluso) */
fun path_query(int u,int v,bool flag){
  fun res=fun();
  //u deve essere antenato di v (u=v va bene)
  while(prof[nex[v]]>prof[u]){
    if(flag)res = res ^ rt.query(in[nex[v]],in[v],1);
    else res = rt.query(in[nex[v]],in[v],0) ^ res;
    v=par[nex[v]][0];
  }
  //il segment deve gestire il caso l>r (ovvero u=v)
  if(flag)res = res ^ rt.query(in[u]+1,in[v],1);
  else res = rt.query(in[u]+1,in[v],0) ^ res;
  return res;
}
// con $N,Q \le 200000$ impiega 800 ms
fun query(int u,int v){ //$\mathcal{O}(\log^2 N)$
  int z = lca(u,v);
  return path_query(par[z][0],u,1)^path_query(z,v,0);
}
/* subtree query, con $N,Q \le 500000$ impiega 961 ms
fun query(int u){ //$\mathcal{O}(\log{N})$
  return rt.query(in[u],out[u]-1);
}*/
/*add dummy vertex 0, necessary for LCA and HLD
  grafo[0].push_back(1); //Esempio d'uso
  dfs(); dfs_hld();
  for(int j=1;j<LOGN;j++){ //build LCA (1-based)
    for(int i=0;i<MAXN;i++)
      par[i][j]=par[par[i][j-1]][j-1];
  }
  rt.build(v,rin,1,n);
  update(a,fun(b,c)); query(a,b).eval(c);*/
