constexpr int MAXN = 1000, INF = 1e9;
struct Edge {
  int u, f, c, r;
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
int sendFlow(int v, int flow, int sink) {
  if (v == sink) return flow;
  for (; cur[v] < grafo[v].size(); cur[v]++) {
    Edge& e = grafo[v][cur[v]];
    if (level[e.u] != level[v] + 1 || e.f == e.c) continue;
    int nxtFlow = sendFlow(e.u, min(flow, e.c - e.f), sink);
    if (nxtFlow > 0) {
      e.f += nxtFlow;
      grafo[e.u][e.r].f -= nxtFlow;
      return nxtFlow;
    }
  }
  return 0;
}
void addEdge(int from, int to, int cap) {
  Edge a{to, 0, cap, (int)grafo[to].size()};
  Edge b{from, 0, 0, (int)grafo[from].size()};
  grafo[from].push_back(a);
  grafo[to].push_back(b);
}
int maxFlow(int source, int sink) {
  int flow = 0;
  while (levelGraph(source, sink)) {
    while (true) {
      int nxtFlow = sendFlow(source, INF, sink);
      if (nxtFlow == 0) break;
      flow += nxtFlow;
    }
  }
  return flow;
}
