#include <iostream>
#include <random>
#include <vector>
#include <cassert>
#include <cstdlib>
using namespace std;
typedef long long ll;
constexpr int MOD = 998'244'353;

#include "NTT.cpp"

int main() {
  mt19937 rng(time(nullptr));

  int N = 1000;

  vector<int> A(N), B(N);
  for (int i = 0; i < N; i++) {
    A[i] = rng() % MOD;
    B[i] = rng() % MOD;
  }
  vector<int> C(2 * N - 1);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      C[i + j] = ((ll) A[i] * B[j] + C[i + j]) % MOD;
    }
  }

  assert(C == multiply(A, B));

  return 0;
}
