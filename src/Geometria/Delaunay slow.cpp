/// Source: https://github.com/dariost/swerc/blob/master/src/Extra/delaunay.cpp (+ refactor di Bortoz)
/// Verification: https://acm.timus.ru/problem.aspx?space=1&num=1520 (ID: 10250738)
/* Slow but simple Delaunay triangulation. Does not handle
 * degenerate cases (from O'Rourke, Computational Geometry
 * in C), running time: $\mathcal{O}(n^4)$
 * INPUT: x[] = x-coordinates, y[] = y-coordinates
 * OUTPUT:   triples = a vector containing m triples of
 * indices corresponding to triangle vertices */
//tested with $N\leq 300,x_i^2+y_i^2\leq 10^3$ (0.7 s)
auto delaunay(int N, vector<T> x, vector<T> y) {
  vector<tuple<int, int, int>> ret;
  vector<p3> p(N); // Richiede Base 3D
  for (int i = 0; i < N; i++)
      p[i] = {x[i], y[i], x[i]*x[i] + y[i]*y[i]};
  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      for (int k = i + 1; k < N; k++) {
        if (j == k) continue;
        p3 t = (p[j] - p[i]) * (p[k] - p[i]);
        bool ok = t.z < 0;
        for (int m = 0; m < N; m++)
            ok = ok && (((p[m] - p[i]) | t) <= 0);
        if (ok) ret.emplace_back(i, j, k);
      }
    }
  } //in case of degenerate cases (i.e. cyclic...
  return ret; //... quadrilateral) it doesn't work... 
} //... but it returns all possible triangles
