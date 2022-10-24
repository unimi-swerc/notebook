/// Source:
/// https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/DFS/EulerPath%20(12.2).h
/// Verification:
/// https://open.kattis.com/submissions/8825463 (archi diretti)
/// https://toph.co/s/889639 (archi non diretti, doppi archi)
/// https://dmoj.ca/submission/4966969 (archi non diretti, grafo quasi completo)
template<bool directed> struct Euler {
    int N; V<vpi> adj; V<vpi::iterator> its; vb used;
    void init(int _N) { N = _N; adj.rsz(N); } //0-based
    void ae(int a, int b) {//funziona anche con archi doppi
        int M = sz(used); used.pb(0); 
        adj[a].eb(b,M); if (!directed) adj[b].eb(a,M); }
    vpi solve(int src = 0) {  //Time: $\mathcal{O}(N+M)$
        its.rsz(N); F0R(i,N) its[i] = begin(adj[i]);
        vpi ans, s{{src,-1}};//{vertex,edge label to vertex}
        int lst = -1; // ans generated in reverse order
        while (sz(s)) { 
            int x = s.bk.f; auto& it=its[x], en=end(adj[x]);
            while (it != en && used[it->s]) ++it;
            if (it == en) { // no more edges out of vertex
                if (lst != -1 && lst != x) return {};
                // not a path, no tour exists
                ans.pb(s.bk); s.pop_back(); 
                if(sz(s))lst=s.bk.f;
            } else s.pb(*it), used[it->s] = 1;
        } // must use all edges
        if (sz(ans) != sz(used)+1) return {}; 
        reverse(all(ans)); return ans;
    }
};
