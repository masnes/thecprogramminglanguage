#include <stdio.h>
#include <math.h>

int ipow(int base, int exp)
{
  int result = 1;
  while(exp)
  {
    if (exp & 1)
      result *= base;
    exp >>= 1;
    base *= base;
  }
  return result;
}
int main(void)
{
  char c = -128;
  printf("%d\n", c);
  printf("%d\n", ipow(2,sizeof(c)*8-1));
  c = -c;
  printf("%d\n", c);

  return 0;
}
