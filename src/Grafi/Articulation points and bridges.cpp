using wedge_t = pair<size_t, size_t>;
// Returns (articulation points, bridges)
pair<vector<size_t>, vector<wedge_t>>
artpoints_bridges(vector<vector<size_t>>& adj) {
  pair<vector<size_t>, vector<wedge_t>> ans;
  vector<size_t> parent(adj.size());

  vector<size_t> order(adj.size()), low(adj.size());
  size_t dfs_count, dfs_source, source_children;

  function<void(vector<vector<size_t>>&, size_t)> dfs =
      [&](vector<vector<size_t>>& adj, size_t u) {
        bool is_art_point = false;
        order[u] = low[u] = dfs_count++;

        for(auto v : adj[u]) {
          if(!order[v]) {
            parent[v] = u;
            if(u == dfs_source)
              ++source_children;

            dfs(adj, v);

            if(low[v] >= order[u] && u != dfs_source) {
              is_art_point = true;
            }
            if(low[v] > order[u]) {
              ans.second.push_back(make_pair(u, v));
            }

            low[u] = min(low[u], low[v]);
          } else if(v != parent[u]) {
            low[u] = min(low[u], order[v]);
          }
        }

        if(is_art_point)
          ans.first.push_back(u);
      };

  for(dfs_source=0; dfs_source<adj.size(); ++dfs_source){
    if(!order[dfs_source]) {
      dfs_count = 1;
      source_children = 0;
      parent[dfs_source] = dfs_source;

      dfs(adj, dfs_source);
      if(source_children > 1) {
        ans.first.push_back(dfs_source);
      }
    }
  }

  return ans;
}
