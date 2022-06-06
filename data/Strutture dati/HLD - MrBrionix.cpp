const long long mod=998244353ll, MAXN=200005, LOGN=18;
//HLD 1-based
struct fun{
  long long a,b;  
  fun(){
    a=1;
    b=0;
  }
  fun(long long x,long long y){
    a=x;
    b=y;
  }
  fun operator^(const fun& other) const {
    fun res(a*other.a%mod,(b*other.a+other.b)%mod);
    return res;
  }
  long long eval(long long x){
    return (a*x+b)%mod;
  }
};

struct SegmentTree{
  int _l,_r;
  fun f,revf;
  SegmentTree *left,*right;
  
  SegmentTree(int l,int r){
    _l=l;
    _r=r;
    
    if(l==r)return;  
    left = new SegmentTree(l,(l+r)/2);
    right = new SegmentTree((l+r)/2+1,r);
  }
  
  void build(fun *v,int *ind,int l,int r){
    if(_r<l || _l>r)return;
    if(_l==_r){
      f=revf=v[ind[_l]];
      return;
    }
    
    left->build(v,ind,l,r);
    right->build(v,ind,l,r);
    
    f=left->f^right->f;
    revf=right->revf^left->revf;
  }
  
  void update(int pos,fun x){
    if(pos<_l|| pos>_r)return;
    if(_l==_r){
      f=revf=x;
      return;
    }
    
    left->update(pos,x);
    right->update(pos,x);
    
    f=left->f^right->f;
    revf=right->revf^left->revf;
  }
  
  fun query(int l,int r,bool flag){
    if(l>r || r<_l || l>_r)return fun();
    if(_l>=l && _r<=r){
      if(flag)return revf;
      return f;
    }
    
    if(flag)return right->query(l,r,flag)^left->query(l,r,flag);
    return left->query(l,r,flag)^right->query(l,r,flag);
  }
} rt(0,MAXN);

long long n,q;
fun v[MAXN];
vector<int> grafo[MAXN];
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

int lca(int x,int y){
  
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

//query sul percorso u->v (u escluso)
//flag = 1 il percorso viene fatto al
//contrario: v->u (u escluso)
fun path_query(int u,int v,bool flag){
  fun res=fun();
  
  while(prof[nex[v]]>prof[u]){
    if(flag)res = res ^ rt.query(in[nex[v]],in[v],1);
    else res = rt.query(in[nex[v]],in[v],0) ^ res;
    
    v=par[nex[v]][0];
  }
  
  if(flag)res = res ^ rt.query(in[u]+1,in[v],1);
  else res = rt.query(in[u]+1,in[v],0) ^ res;
  
  return res;
}

// con N,Q <= 200000 impiega 800 ms
fun query(int u,int v){
  int z = lca(u,v);
  return path_query(par[z][0],u,1)^path_query(z,v,0);
}

/* subtree query
// con N,Q <= 500000 impiega 961 ms
fun query(int u){
  return rt.query(in[u],out[u]-1);
}
*/

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin>>n>>q;
  for(int i=1;i<=n;i++){
    cin>>v[i].a>>v[i].b;
  }
  for(int i=0;i<n-1;i++){
    int u,v;
    cin>>u>>v;
    u++; //li rendo 1-based
    v++;
    grafo[u].push_back(v);
    grafo[v].push_back(u);
  }
  
  grafo[0].push_back(1);
  dfs();
  dfs_hld();
  for(int j=1;j<LOGN;j++){
    for(int i=0;i<MAXN;i++){
      par[i][j]=par[par[i][j-1]][j-1];
    }
  }
  rt.build(v,rin,1,n);
  
  for(int i=0;i<q;i++){
    int t,a,b,c;
    cin>>t>>a>>b>>c; 
    if(t==0){
      a++;
      update(a,fun(b,c));
    }else{
      a++;
      b++;
      cout<<query(a,b).eval(c)<<"\n";
    }
  }
  return 0;
}
