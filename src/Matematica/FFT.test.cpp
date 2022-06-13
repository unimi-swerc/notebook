#include <complex>
#include <iostream>
#include <random>
#include <vector>
#include <cassert>
#include <cstdlib>
using namespace std;

#include "FFT.cpp"

int main() {
  mt19937 rng(time(nullptr));

  int N = 1000;

  vector<int> A(N), B(N);
  for (int i = 0; i < N; i++) {
    A[i] = rng() % N;
    B[i] = rng() % N;
  }
  vector<int> C(2 * N - 1);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      C[i + j] += A[i] * B[j];
    }
  }

  assert(C == multiply(A, B));

  return 0;
}
