#include <stdio.h>

unsigned getbits(unsigned x, int p, int n);

int main() {
  int i;

  for (i = 0; i < 20; i++) {
    printf("%d: %d\n", i, getbits(i, i, i-1));
  }
}

/* getbits: get n bits from position p */
unsigned getbits(unsigned x, int p, int n)
{
  return ((x >> (p+1-n)) & ~(~0 << n));
}
