#include <stdio.h>
#include <stdlib.h>

#define BUF_MAX 999

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

int itob(int n, char s[], int b)
{
  int sign, i, abs_val;

  if (b == 1 || b == -1 || b == 0) {
    printf("It is impossible to convert to base %d\n", b);
    return -1;
  }

  //int max_neg = ipow(2, (sizeof(int)*4)-1);
  //printf("max_neg: %d\n", max_neg);

  sign = n; /* record sign */

  i = 0;
  do {
    abs_val = abs(n % b);
    if (abs_val < 10) {
      s[i++] = abs_val + '0'; /*  get next digit for bases <= decimal */
    }
    else if (abs_val < 36) {
      s[i++] = abs_val - 10 + 'A'; /* get next digit for large bases */
    }
    else /* get next digit for huge bases */
    {
      s[i++] = ')';

      do {
      s[i++] = abs(abs_val % 10) + '0';

      // catch overflow
      if (i > BUF_MAX - 5) {
        fprintf(stderr, "Returned value too large for string buffer, quitting to avoid overflow\n");
        return -1;
      }

      } while ((abs_val /= 10) != 0);

      s[i++] = '(';
    }

    // catch overflow
    if (i > BUF_MAX - 5) {
      fprintf(stderr, "Returned value too large for string buffer, quitting to avoid overflow\n");
      return -1;
    }
  } while ((n /= b) != 0); /* delete it */

  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
  //printf("Ending string:\n");
  //printf("%s\n", s);
  //printf("s:\n");
  //printf("%s\n", s);

  return 0;
}

int main(int argc, char * argv[])
{
  int ret;
  int n, b;
  char s[BUF_MAX];
  n = 100;
  b = 16;


  if (argc > 2)
  {
    n = atoi(argv[1]);
    b = atoi(argv[2]);
  } else if (argc > 1)
  {
    n = atoi(argv[1]);
  }

  //printf("argv[1]: %s, argv[2]: %s,\n", argv[1], argv[2]);

  //printf("n: %d, b: %d\n", n, b);

  //printf("n:%d, s:%s, b:%d\n", n, s, b);

  if (itob(n,s,b) == 0) {
    printf("%d in base %d:\n", n, b);
    printf("%s\n", s);
  }
  return 0;
}
