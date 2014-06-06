#include <stdio.h>

unsigned rightrot(unsigned x, int n);

int main()
{
  int x = 0xF9;
  int n = 4;

  int rotated = rightrot(x,n);
  printf("x: %d, n: %d, rightrot(x,n): %d\n", x, n, rotated);

  return 0;
}

unsigned rightrot(unsigned x, int n)
{
  //int i;
  /// int size = sizeof(x);

  /// unsigned x2 = x >> n;
  /// unsigned xoverflow = x & ~(~0 << n);
  /// unsigned xmask = ~0 << n;

  return (x >> n & ~(~0 << n)) | ((x & ~(~0 << n)) << n);
}
