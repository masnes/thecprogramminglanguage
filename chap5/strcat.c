#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* concatenate string s to t, assumes that both are null terminated */
char *astrcat(char *s, char*t)
{
  char *ret = t;
  while(*t)
    ++t;
  while ((*t++ = *s++))
    ;
  return ret;
}

void astrcpy(char *s, char *t)
{
  while((*t++ = *s++));
}

int main(void)
{
  char string1[100] = "world";
  char string2[100] = "                    ";
  char string3[100] = "hello ";
  char string4[100] = "\n";
  char *s1 = string1;
  char *s2 = string2;
  char *s3 = string3;
  char *s4 = string4;
  astrcpy(s1, s2);
  printf("%s %s\n", s1, s2);
  astrcat(s2, s3);
  printf("%s\n", s3);
  astrcat(s2, s3);
  printf("%s\n", s3);
  astrcat(s2, s3);
  printf("%s\n", s3);
  
  return 0;
}
