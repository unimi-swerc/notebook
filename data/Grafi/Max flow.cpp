// with n<=5000, m<=30000 run in 0.20 sec
constexpr int MAXN = 6000;
constexpr ll INF = 1e18;
struct Edge {
  int u, r;
  ll f, c;
};
vector<Edge> grafo[MAXN];
int level[MAXN];
int cur[MAXN];
bool levelGraph(int source, int sink) {
  memset(level, 0, MAXN * sizeof(int));
  memset(cur, 0, MAXN * sizeof(int));
  level[source] = 1;
  queue<int> Q;
  Q.push(source);
  while (!Q.empty()) {
    int v = Q.front();
    Q.pop();
    for (Edge e : grafo[v]) {
      if (level[e.u] == 0 && e.f < e.c) {
        level[e.u] = level[v] + 1;
        Q.push(e.u);
      }
    }
  }
  return level[sink];
}
ll sendFlow(int v, ll flow, int sink) {
  if (v == sink) return flow;
  for (; cur[v] < grafo[v].size(); cur[v]++) {
    Edge& e = grafo[v][cur[v]];
    if (level[e.u] != level[v] + 1 || e.f == e.c) continue;
    ll nxtFlow = sendFlow(e.u, min(flow, e.c - e.f), sink);
    if (nxtFlow > 0) {
      e.f += nxtFlow;
      grafo[e.u][e.r].f -= nxtFlow;
      return nxtFlow;
    }
  }
  return 0;
}
void addEdge(int from, int to, ll cap) {
  Edge a{to, (int)grafo[to].size(), 0, cap};
  Edge b{from, (int)grafo[from].size(), 0, 0};
  grafo[from].push_back(a);
  grafo[to].push_back(b);
}
ll maxFlow(int source, int sink) {
  ll flow = 0;
  while (levelGraph(source, sink)) {
    while (true) {
      ll nxtFlow = sendFlow(source, INF, sink);
      if (nxtFlow == 0) break;
      flow += nxtFlow;
    }
  }
  return flow;
}
