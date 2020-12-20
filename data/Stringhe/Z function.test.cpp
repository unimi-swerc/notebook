#include <iostream>
#include <random>
#include <vector>
#include <cassert>
#include <cstdlib>
using namespace std;

#include "Z function.cpp"

int main() {
  mt19937 rng(time(nullptr));

  int N = 1000;

  string S;
  for (int i = 0; i < N; i++) {
    S += 'a' + rng() % 6;
  }

  auto z = z_function(S);
  for (int i = 1; i < S.size(); i++) {
    for (int j = 0; j < z[i]; j++) {
      assert(S[j] == S[i + j]);
    }
    assert(S[z[i]] != S[i + z[i]]);
  }

  return 0;
}
