#include <iostream>
#include <random>
#include <vector>
#include <cassert>
#include <cstdlib>
using namespace std;

#include "Sparse table.cpp"

int main() {
  mt19937 rng(time(nullptr));

  int N = 1000, Q = 1000;
  vector<int> V(N);
  for (int& i : V) {
    i = rng() % (int)(1e6);
  }

  build(N, V.data());

  for (int i = 0; i < Q; i++) {
    int l = rng() % N;
    int r = rng() % N;
    if (l == r) continue;
    if (l > r) swap(l, r);
    int x = V[l];
    for (int j = l; j < r; j++) {
      x = min(x, V[j]);
    }
    assert(x == query(l, r));
  }

  return 0;
}
