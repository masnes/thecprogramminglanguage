#include <stdio.h>
#include <string.h>

int containschar(char s[], char c);
void squeeze(char s[], char t[]);

int main() {
  char string1[] = "afjl";
  char string2[] = "aasdfghjkkl;";
  char string3[] = "afjl";
  char string4[] = "aasdfghjkkl;";
  printf("string1: %s\n", string1);
  printf("string2: %s\n", string2);
  printf("string3: %s\n", string3);
  printf("string4: %s\n", string4);

  squeeze(string1, string2);
  squeeze(string4, string3);
}

/* delete all characters in t from s */
void squeeze(char s[], char t[]) {
  int i, j;

  printf("squeezing...");

  for (i = j = 0; s[i] != '\0'; i++ )
    if (!containschar(t, s[i]))
      s[j++] = s[i];
  s[j] = '\0';

  printf(" squeezed: %s\n", s);
}

/* check if string contains a character c */
int containschar(char s[], char c) {
  int i;

  for (i = 0; s[i] != '\0'; i++)
    if (s[i] == c)
      return 1;

  return 0;
}
