#include <iostream>
#include <random>
#include <vector>
#include <cassert>
#include <cstdlib>
using namespace std;

#include "Manacher.cpp"

int main() {
  mt19937 rng(time(nullptr));

  int N = 10;

  string S;
  for (int i = 0; i < N; i++) {
    S += 'a' + rng() % 2;
  }

  auto [even, odd] = manacher(S);
  for (int i = 1; i < S.size(); i++) {
    int l = i - 1, r = i;
    for (int j = 0; j < even[i]; j++) {
      assert(0 <= l && l < N);
      assert(0 <= r && r < N);
      assert(S[l] == S[r]);
      l--, r++;
    }
    assert(l == -1 || r == N || S[l] != S[r]);
  }
  for (int i = 0; i < S.size(); i++) {
    int l = i, r = i;
    for (int j = 0; j < odd[i]; j++) {
      assert(0 <= l && l < N);
      assert(0 <= r && r < N);
      assert(S[l] == S[r]);
      l--, r++;
    }
    assert(l == -1 || r == N || S[l] != S[r]);
  }

  return 0;
}
