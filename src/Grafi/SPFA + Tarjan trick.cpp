/// Source: Own (MrBrionix)
/// Verification:
/// https://atcoder.jp/contests/agc056/submissions/40918831
long long n,m,t,dist[MAXN],padre[MAXN];
vector<pair<int,int>> grafo[MAXN]; vector<int> nod,g[MAXN];
void dfs(int nodo){ //tested with $n,m\leq 10^6$ (900 ms)
    dist[nodo]=-1;
    for(auto i : g[nodo]){
        if(padre[i]==nodo) dfs(i);
    }
    g[nodo].clear();
    padre[nodo]=-1;
}
void dj(int nodo){ //funziona anche con archi negativi
    if(dist[nodo]==-1)return;
    for(auto [v,peso] : grafo[nodo]){
        if(dist[v]==-1 || (dist[nodo]+peso)<dist[v]){
            dfs(v);
            dist[v]=(dist[nodo]+peso);
            nod.push_back(v);
            g[nodo].push_back(v);
            padre[v]=nodo;
        }
    }
}
