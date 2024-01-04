/// Source:
/// https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/SolveLinear.h
/// Verification:
/// https://open.kattis.com/submissions/11054334 (double)
/// https://judge.yosupo.jp/submission/139293 (modular)
/// https://dmoj.ca/submission/5535996 (modular)
/// https://dmoj.ca/submission/5536025 (modular)
/// https://contest.ucup.ac/submission/297686 (double)
/* Solves $Ax = b$. If there are multiple solutions,
 * an arbitrary one is returned.
 * Returns rank, or -1 if no solutions.
 * Data in A and b is lost. Time: $\mathcal{O}(n^2 m)$
 * double: $n,m \leq 100$, t ignoto impiega 0.03 sec
 * con precisione di almeno $10^{-3}$ (ma eps=$10^{-12}$)
 * modular: con $n,m\leq 500$ impiega 447 ms*/
typedef double T; //oppure modular<mod>
typedef vector<T> vd;
const double eps = 1e-12;
vi col; //globale per ricavare il sottospazio
int solveLinear(vector<vd>& A, vd& b, vd& x) {
  int n = sz(A), m = sz(x), rank = 0, br, bc;
  if (n) assert(sz(A[0]) == m);
  col.resize(m); iota(all(col), 0);
  rep(i,0,n) {
    T v, bv = 0;
    rep(r,i,n) rep(c,i,m)
    if ((v = fabs(A[r][c])) > bv)
      br = r, bc = c, bv = v;
    if (bv <= eps) {
      rep(j,i,n) if (fabs(b[j]) > eps) return -1;
      break;
    }
    swap(A[i], A[br]); swap(b[i], b[br]);
    swap(col[i], col[bc]);
    rep(j,0,n) swap(A[j][i], A[j][bc]);
    bv = T(1)/A[i][i];
    rep(j,i+1,n) {
      T fac = A[j][i] * bv;
      b[j] -= fac * b[i];
      rep(k,i+1,m) A[j][k] -= fac*A[i][k];
    }
    rank++;
  }
  x.assign(m, T(0));
  for (int i = rank; i--;) {
    b[i] = b[i]/A[i][i];
    rep(z,i+1,m){ //(*)per ricavare il sottospazio
      A[i][z] = A[i][z]/A[i][i];
    }
    x[col[i]] = b[i];
    rep(j,0,i) {
      rep(z,i+1,m){ //(*)per ricavare il sottospazio
        A[j][z] -= A[j][i] * A[i][z];
      }
      b[j] -= A[j][i] * b[i];
    }
  }
  return rank; // (multiple solutions if rank < m)
}
/* se non serve il sottospazio eliminare
  i 2 for segnati sopra (*)
  per ottenere il sottospazio vettoriale:
  auto cop = p; auto co = tmp;
  int xx=solveLinear(p,tmp,ans);
  if(xx==-1) { cout<<xx<<"\n";return 0; }
  //soluzioni
  cout<<m-xx<<"\n";
  for(int i=0;i<m;i++)cout<<ans[i].r<<" ";
  cout<<"\n";
  for(auto &i : co)i=0; //azzero i termini noti
  xx = solveLinear(cop,co,ans); //calcolo
  assert(xx!=-1);
  //costruisco la base del sottospazio
  vector<vector<ll> > d(m-xx,vector<ll>(m,0));
  for(int j = xx; j<m;j++){
    d[j-xx][col[j]]=1;
    for(int i=xx-1;i>=0;i--)
      d[j-xx][col[i]]=-(cop[i][j].r);
  }*/
