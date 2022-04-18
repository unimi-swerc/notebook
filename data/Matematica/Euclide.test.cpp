#include <iostream>
#include <random>
#include <tuple>
#include <vector>
#include <cassert>
#include <cstdlib>
using namespace std;
typedef long long ll;
constexpr int MAXV = 1e6;

#include "Euclide.cpp"

int main() {
  mt19937 rng(time(nullptr));

  ll x = rng() % MAXV;
  ll y = rng() % MAXV;

  auto [a, b, g] = xgcd(x, y);

  assert(a * x + b * y == g);

  return 0;
}
