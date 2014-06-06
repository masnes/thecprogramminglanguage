#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

int main()
{
  int x = 8;
  int y = 5;
  int p = 5;
  int n = 2;

  printf("x: %d, y: %d, n: %d, p: %d, setbits: %d \n", x, y, p, n, setbits(x,p,n,y));

  return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
  unsigned xmask = x & ~0 << n;
  unsigned ymask = y & ~(~0 << n);
  printf("x & xmask: %d\n", x & xmask);
  printf("y & ymask: %d\n", y & ymask);

  return (x & xmask) | (y & ymask);


}
