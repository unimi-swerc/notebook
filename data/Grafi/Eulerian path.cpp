template<bool directed> struct Euler {
    int N; V<vpi> adj; V<vpi::iterator> its; vb used;
    void init(int _N) { N = _N; adj.rsz(N); }
    void ae(int a, int b) {
        int M = sz(used); used.pb(0); 
        adj[a].eb(b,M); if (!directed) adj[b].eb(a,M); }
    vpi solve(int src = 0) { 
        its.rsz(N); F0R(i,N) its[i] = begin(adj[i]);
        vpi ans, s{{src,-1}}; // {{vert,prev vert},edge label}
        int lst = -1; // ans generated in reverse order
        while (sz(s)) { 
            int x = s.bk.f; auto& it=its[x], en=end(adj[x]);
            while (it != en && used[it->s]) ++it;
            if (it == en) { // no more edges out of vertex
                if (lst != -1 && lst != x) return {};
                // not a path, no tour exists
                ans.pb(s.bk); s.pop_back(); if (sz(s)) lst=s.bk.f;
            } else s.pb(*it), used[it->s] = 1;
        } // must use all edges
        if (sz(ans) != sz(used)+1) return {}; 
        reverse(all(ans)); return ans;
    }
};
