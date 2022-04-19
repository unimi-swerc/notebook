using C = ll;
C hungarian(const V<V<C>>& a) { 
  int N = sz(a)-1, M = sz(a[1])-1; assert(N <= M);
  V<C> u(N+1), v(M+1); // potentials to make edge weights >= 0
  vi job(M+1);
  FOR(i,1,N+1) { // find alternating path with job i
    const C inf = numeric_limits<C>::max();
    int w = 0; job[w] = i; // add "dummy" worker 0
    V<C> dist(M+1,inf); vi pre(M+1,-1); vb done(M+1);
    while (job[w]) { // dijkstra
      done[w] = 1; int j = job[w], nexW; C delta = inf; 
      // fix dist[j], update dists from j
      F0R(W,M+1) if (!done[W]) { // try all workers
        if (ckmin(dist[W],a[j][W]-u[j]-v[W])) pre[W] = w;
        if (ckmin(delta,dist[W])) nexW = W;
      }
      F0R(W,M+1) { // subtract constant from all edges going
        // from done -> not done vertices, lowers all 
        // remaining dists by constant
        if (done[W]) u[job[W]] += delta, v[W] -= delta; 
        else dist[W] -= delta; 
      }
      w = nexW;
    } // potentials adjusted so all edge weights >= 0
    for (int W; w; w = W) job[w] = job[W = pre[w]];
  } // job[w] = 0, found alternating path 
  return -v[0]; // min cost
}
