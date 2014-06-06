#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

int main()
{
  unsigned int x = 5;
  unsigned int p = 3;
  unsigned int n = 5;

  printf("x: %d, p: %d, n: %d, invert(x,p,n): %d\n", x, p, n, invert(x,p,n));

  return 0;
}

unsigned invert(unsigned x, int p, int n) 
{
  unsigned xmask_end = ~0 << n;
  unsigned xmask_begin = ~(~0 << n);

  return (x & xmask_end) & ~(x & xmask_begin);
}
