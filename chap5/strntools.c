#include <stdio.h>

/* strncpy: copy up to n characters from s to t */
void astrncpy(char *s, char *t, int n)
{
  int i;

  for(i = 0; *s != '\0' && i < n-1; i++, s++, t++)
    *t = *s;
  *t = *s; // copy the '\0'
}

/* strncat: concatenate up to n characters from s to t */
void astrncat(char *s, char *t, int n)
{
  int i;

  /* find end of t */
  while(*t != '\0')
    ++t;
  for(i = 0; i < n && *s != '\0'; ++t, ++s, ++i)
    *t = *s;
}

/* strncmp: compare first n characters of s and t,
 * return 1 if same, 0 otherwise */
int astrncmp(char *s, char *t, int n)
{
  int i;
  i = 0;
  while (*s == *t && i < n) {
    if (*s == '\0')
      return 1;
    s++; t++; i++;
  }
  if (i == n)
    return 1;
  return 0;
}


int main(void)
{
  char string1[100] = "hello";
  char string2[100] = "goodbye";

  printf("%s\n", string2);
  astrncpy(string1, string2, 4);
  printf("%s\n", string2);
  astrncat(string1, string2, 4);
  printf("%s\n", string2);
  printf("strng1 astrncmp string2, n = 100: %d\n", astrncmp(string1, string2, 100));
  printf("strng1 astrncmp string2, n = 4: %d\n", astrncmp(string1, string2, 4));
  printf("strng1 astrncmp string2, n = 5: %d\n", astrncmp(string1, string2, 5));

  return 0;
}
