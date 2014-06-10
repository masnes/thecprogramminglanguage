#include <stdio.h>

#define BUFMAX 100

/* append character to string */
void append(int n, char ch_array[])
{
  static int pos = 0;

  char c = (n % 10 + '0');

  if (pos < BUFMAX) {
    ch_array[pos++] = c;
    /* stupid (but safe) way of doing things: 
     * append EOS character constantly */
    ch_array[pos] = '\0'; 
  }
}

/* printd: convert int n to decimal string */
void itoa(int n, char ch_array[])
{
  if (n < 0) {
    putchar('-');
    n = -n;
  }
  if (n / 10)
    itoa(n / 10, ch_array);
  append(n, ch_array);
}

int main(void) 
{
  char ch_array[BUFMAX+1];
  int n = 134785;
  printf("n: %d\n", n);
  itoa(n, ch_array);
  printf("ch_array: %s\n", ch_array);

  return 0;
}
