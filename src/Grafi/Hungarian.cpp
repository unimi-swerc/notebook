/// Source:
/// https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Flows%20(12.3)/Dinic.h
/// Verification:
/// https://www.acmicpc.net/source/56913786 (google code jam 2022)
/// https://open.kattis.com/submissions/10161695
/// https://codeforces.com/gym/103640/submission/190868345
/// https://codeforces.com/contest/1510/submission/243053287
/* Description: Given array of (possibly negative) costs
 * to complete each of $N$ (1-indexed) jobs with each of $M$
 * workers ($N\leq M$), finds min cost to complete all jobs
 * such that each worker is assigned to at most one job.
 * Dijkstra with potentials works in almost the same way
 * as MCMF. Time: $\mathcal{O}(N^2M)$.
 * Matrix A is 1-based (sia sulle righe che sulle colonne)
 *row x= lista dei costi di ciascun worker per il lavoro x*/
using C = ll; // con $N\leq 1000,M\leq 2000$ impiega 1.6 sec
C hungarian(const V<V<C>>& a) { // 1-based
  int N = sz(a)-1, M = sz(a[1])-1; assert(N <= M);
  V<C> u(N+1), v(M+1); // to make edge weights >= 0
  vi job(M+1); // job[i] = lavoro assegnato al lavoratore i
  FOR(i,1,N+1) { // find alternating path with job i
    //attenzione: se C=__int128 bisogna settare inf a mano
    const C inf = numeric_limits<C>::max();
    int w = 0; job[w] = i; // add "dummy" worker 0
    V<C> dist(M+1,inf); vi pre(M+1,-1); V<bool> done(M+1);
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
