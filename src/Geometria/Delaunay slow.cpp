// Slow but simple Delaunay triangulation. Does not handle
// degenerate cases (from O'Rourke, Computational Geometry
// in C), running time: O(n^4)
// INPUT: x[] = x-coordinates, y[] = y-coordinates
// OUTPUT:   triples = a vector containing m triples of
// indices corresponding to triangle vertices

typedef double T;
typedef tuple<int, int, int> triple;

vector<triple> delaunay(vector<T> &x, vector<T> &y) {
  int n = x.size();
  vector<T> z(n);
  vector<triple> ret;

  for (int i = 0; i < n; i++)
    z[i] = x[i] * x[i] + y[i] * y[i];

  for (int i = 0; i < n - 2; i++) {
    for (int j = i + 1; j < n; j++) {
      for (int k = i + 1; k < n; k++) {
        if (j == k) continue;
        double xn = (y[j] - y[i]) * (z[k] - z[i]) -
                    (y[k] - y[i]) * (z[j] - z[i]);
        double yn = (x[k] - x[i]) * (z[j] - z[i]) -
                    (x[j] - x[i]) * (z[k] - z[i]);
        double zn = (x[j] - x[i]) * (y[k] - y[i]) -
                    (x[k] - x[i]) * (y[j] - y[i]);
        bool flag = zn < 0;
        for (int m = 0; flag && m < n; m++) {
          flag = flag && ((x[m] - x[i]) * xn + (y[m] -
                 y[i]) * yn + (z[m] - z[i]) * zn <= 0);
        }
        if (flag) ret.emplace_back(i, j, k);
      }
    }
  }
  return ret;
}
