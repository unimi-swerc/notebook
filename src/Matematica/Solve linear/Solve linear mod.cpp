/// Source: MrBrionix (ricavato dalla versione senza modulo)
/// Verification:
/// https://dmoj.ca/submission/4727287
/// https://judge.yosupo.jp/submission/97080
/// https://dmoj.ca/submission/4716163
// come solve linear ma con il modulo
typedef vector<ll> vd;
vi col; //globale per ricavare il sottospazio
// con $n,m\leq 500$ impiega 302 ms
int solveLinear(vector<vd>& A, vd& b, vd& x) {
  int n = sz(A), m = sz(x), rank = 0, br, bc;
  if (n) assert(sz(A[0]) == m);
  col.resize(m);
  iota(all(col), 0);

  rep(i,0,n) {
    ll v, bv = 0;
    rep(r,i,n) rep(c,i,m)
      if ((v = abs(A[r][c])) > bv)
        br = r, bc = c, bv = v;
    if (bv <= 0) {
      rep(j,i,n) if (abs(b[j]) > 0) return -1;
      break;
    }
    swap(A[i], A[br]);
    swap(b[i], b[br]);
    swap(col[i], col[bc]);
    rep(j,0,n) swap(A[j][i], A[j][bc]);
    bv = inv(A[i][i]);//inverso moltiplicativo
    rep(j,i+1,n) {
      ll fac = A[j][i] * bv % mod;
      b[j] -= fac * b[i];
      b[j] %= mod;
      rep(k,i+1,m) {
        A[j][k] -= fac*A[i][k];
        A[j][k] %= mod;
      }
    }
    rank++;
  }

  x.assign(m, 0);
  for (int i = rank; i--;) {
    b[i] *= inv(A[i][i]);//inverso
    b[i] %= mod;
    rep(z,i+1,m){ //*per ricavare il sottospazio
      A[i][z] *= inv(A[i][i]);//inverso
      A[i][z] %= mod;
    }
    
    x[col[i]] = b[i];
    rep(j,0,i) {
      rep(z,i+1,m){ //*per ricavare il sottospazio
        A[j][z] -= A[j][i] * A[i][z];
        A[j][z] %= mod;
      }
      b[j] -= A[j][i] * b[i];
      b[j] %= mod;
    }
  }
  return rank; // (multiple solutions if rank < m)
}
/* se non serve il sottospazio eliminare
   i 2 for segnati sopra (*)
   per ottenere il sottospazio vettoriale:
  auto cop = p;
  auto co = tmp;
  int xx=solveLinear(p,tmp,ans);
  if(xx==-1){
    cout<<xx<<"\n";
    return 0;
  }
  //soluzioni
  cout<<m-xx<<"\n";
  for(int i=0;i<m;i++)cout<<(ans[i]+mod)%mod<<" ";
  cout<<"\n";
  
  for(auto &i : co)i=0; //azzero i termini noti
  xx = solveLinear(cop,co,ans); //calcolo
  assert(xx!=-1);
  //costruisco la base del sottospazio
  vector<vector<ll> > d(m-xx,vector<ll>(m,0));
  for(int j = xx; j<m;j++){
    d[j-xx][col[j]]=1;
    for(int i=xx-1;i>=0;i--){
      d[j-xx][col[i]]=-cop[i][j];
    }
  }*/
