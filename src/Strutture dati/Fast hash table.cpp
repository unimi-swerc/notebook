/// Source:
/// https://codeforces.com/blog/entry/60737
/// https://codeforces.com/blog/entry/61587
/// https://codeforces.com/blog/entry/62393
/// Verification:
/// https://codeforces.com/contest/1720/submission/187054707
/// https://itacpc22.kattis.com/submissions/10162289
/// https://codeforces.com/gym/101964/submission/187851301
/// https://judge.yosupo.jp/submission/140347
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = chrono
      ::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};
gp_hash_table<int, int, custom_hash> best; //2x faster
