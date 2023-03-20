/// Source:
/// https://github.com/kth-competitive-programming/kactl/blob/main/content/various/FastInput.h
/// Verification:
/// https://codeforces.com/gym/101620/submission/178418728
/* Read an integer from stdin. Usage requires your
 * program to pipe in input from file.
 * Usage: ./a.out < input.txt
 * Time: About 5x as fast as cin/scanf. */
inline char gc() { // like getchar()
  static char buf[1 << 16];
  static size_t bc, be;
  if (bc >= be) {
    buf[0] = 0, bc = 0;
    be = fread(buf, 1, sizeof(buf), stdin);
  }
  return buf[bc++]; // returns 0 on EOF
}
int readInt(){//con $2\cdot 10^6$ interi è più veloce di 200 ms
  int a, c;
  while ((a = gc()) < 40);
  if (a == '-') return -readInt();
  while ((c = gc()) >= 48) a = a * 10 + c - 480;
  return a - 48;
}
