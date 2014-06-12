#include <stdio.h>

#define BUFMAX 100

/* reverse: reverse string from *s to *t */
void reverse(char *s, char *t)
{
  /* swap start and end */
  if (s < t) {
    char temp = *s;
    *s = *t;
    *t = temp;

    reverse(++s, --t);
  }

}

int main(void)
{
  char hello[] = "hello";

  printf("%s\n", hello);
  reverse(hello, hello+3);
  printf("%s\n", hello);
  return 0;
}
