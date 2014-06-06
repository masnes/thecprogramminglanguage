#include <stdio.h>
#include <stdlib.h>

#define BUF_MAX 50

void reverse(char s[BUF_MAX])
{
  int i,j;
  char temp;

  //printf("Starting string:\n");
  //printf("%s\n", s);
  i = j = 0;
  if (s[0] != '\0')
    while (s[j+1] != '\0' && j < BUF_MAX - 1)
      j++;

  while (i < j) { /* swap characters from i to j */
    temp = s[i];
    s[i] = s[j];
    s[j] = temp;
    i++; j--;
  }
  //printf("Ending string:\n");
  //printf("%s\n", s);

}

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

void itob(int n, char s[], int b)
{
  int sign, i;

  int max_neg = ipow(2, (sizeof(int)*4)-1);
  printf("max_neg: %d\n", max_neg);

  sign = n; /* record sign */

  i = 0;
  do {
    s[i++] = abs(n % b) + '0'; /*  get next digit */
  } while ((n /= b) != 0); /* delete it */
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
  //printf("Ending string:\n");
  //printf("%s\n", s);
  printf("s:\n");
  printf("%s\n", s);

}

int main(void)
{
  int n, b;
  char s[BUF_MAX];

  n = 100;
  b = 16;
  printf("n:%d, s:%s, b:%d\n", n, s, b);
  itob(n,s,b);
  return 0;
}
