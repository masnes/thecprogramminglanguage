#include <stdio.h>

#define BUFMAX 100

void reverse(int start, int end, char s[])
{
  /* swap start and end */
  if (start < end) {
    char temp = s[start];
    s[start] = s[end];
    s[end] = temp;

    reverse(++start, --end, s);
  }

}

int main(void)
{
  char hello[] = "hello";

  printf("%s\n", hello);
  reverse(0, 4, hello);
  printf("%s\n", hello);
  return 0;
}
