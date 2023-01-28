/// Source: https://github.com/dariost/swerc/blob/master/src/Extra/delaunay.cpp
/// Verification: https://acm.timus.ru/problem.aspx?space=1&num=1520 (ID: 10156667)
// Slow but simple Delaunay triangulation. Does not handle
// degenerate cases (from O'Rourke, Computational Geometry
// in C), running time: $\mathcal{O}(n^4)$
// INPUT: x[] = x-coordinates, y[] = y-coordinates
// OUTPUT:   triples = a vector containing m triples of
// indices corresponding to triangle vertices
typedef double T; //tested with $N\leq 300,x_i^2+y_i^2\leq 1000$ (0.7 sec)
typedef tuple<int, int, int> triple;
vector<triple> delaunay(vector<T> &xx, vector<T> &yy) {
  int n = xx.size();
  vector<T> z(n);
  vector<triple> ret;
  for (int i = 0; i < n; i++)
    z[i] = xx[i] * xx[i] + yy[i] * yy[i];
  for (int i = 0; i < n - 2; i++) {
    for (int j = i + 1; j < n; j++) {
      for (int k = i + 1; k < n; k++) {
        if (j == k) continue;
        double xn = (yy[j] - yy[i]) * (z[k] - z[i]) -
                    (yy[k] - yy[i]) * (z[j] - z[i]);
        double yn = (xx[k] - xx[i]) * (z[j] - z[i]) -
                    (xx[j] - xx[i]) * (z[k] - z[i]);
        double zn = (xx[j] - xx[i]) * (yy[k] - yy[i]) -
                    (xx[k] - xx[i]) * (yy[j] - yy[i]);
        bool flag = zn < 0;
        for (int m = 0; flag && m < n; m++) {
          flag = flag && ((xx[m] - xx[i]) * xn + (yy[m] -
                yy[i]) * yn + (z[m] - z[i]) * zn <= 0);
        }
        if (flag) ret.emplace_back(i, j, k);
      }
    }
  } //in case of degenerate cases (i.e. cyclic...
  return ret; //... quadrilateral) it doesn't work... 
} //... but it returns all possible triangles
