/// Source: 
/// https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Flows%20(12.3)/Dinic.h
/// Verification:
/// https://dmoj.ca/submission/5076805
/// https://www.spoj.com/problems/FASTFLOW/ (id: 30497196)
/// https://www.spoj.com/problems/MATCHING/ (id: 30497217)
/// https://codeforces.com/gym/103185/submission/183201540
/// https://codeforces.com/gym/102428/submission/186120441
/// https://dmoj.ca/submission/5178029
/// https://codeforces.com/contest/1070/submission/188615851
/// https://codeforces.com/contest/1783/submission/188798255
// 0-based, with $N\leq 5000, M\leq 30000$ run in 0.19 sec (F=ll)
//$\mathcal{O}(N^2M)$, con grafi bipartiti $N\leq 10^5,M\leq 10^5$ (0.77 sec)
using pi = pair<int,int>;
#define sz(x) int((x).size())
template<class F> struct Dinic {
    struct Edge { int to, rev; F cap; };
    int N; vector<vector<Edge>> adj;
    void init(int _N) { N = _N; adj.resize(N); } //0-based
    pi ae(int a, int b, F cap, F rcap = 0) { 
        assert(min(cap,rcap) >= 0); // saved me > once
        adj[a].push_back({b,sz(adj[b]),cap});
        adj[b].push_back({a,sz(adj[a])-1,rcap});
        return {a,sz(adj[a])-1};
    }
    F edgeFlow(pi loc) { // get flow along original edge
        const Edge& e = adj.at(loc.first).at(loc.second);
        return adj.at(e.to).at(e.rev).cap;
    }
    vector<int> lev, ptr;
    bool bfs(int s,int t){//level=shortest dist from source
        lev = ptr = vector<int>(N);
        lev[s] = 1; queue<int> q({s});
        while (sz(q)) { int u = q.front(); q.pop();
            for(auto& e: adj[u]) if (e.cap && !lev[e.to]) {
                q.push(e.to), lev[e.to] = lev[u]+1;
                if (e.to == t) return 1;
            }
        }
        return 0;
    }
    F dfs(int v, int t, F flo) {
        if (v == t) return flo;
        for (int& i = ptr[v]; i < sz(adj[v]); i++) {
            Edge& e = adj[v][i];
            if (lev[e.to]!=lev[v]+1||!e.cap) continue;
            if (F df = dfs(e.to,t,min(flo,e.cap))) { 
                e.cap -= df; adj[e.to][e.rev].cap += df;
                return df; } // saturated >=1 one edge
        }
        return 0;
    }
    F maxFlow(int s, int t) {
        F tot = 0; while (bfs(s,t)) while (F df = 
            dfs(s,t,numeric_limits<F>::max())) tot += df;
        return tot;
    }
};
