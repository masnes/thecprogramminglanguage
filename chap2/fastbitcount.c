#include <stdio.h>

unsigned fastbitcount(unsigned x);

int main() {
  int i;

  for (i = 0; i < 32; i++) {
    printf("%d: %d\n", i, fastbitcount(i));
  }
}

/* fastbitcount: get n bits from position p */
unsigned fastbitcount(unsigned x)
{
  int count = 0;
  while(x) {
    x &= (x-1);
    count++;
  }
  return count;
}
