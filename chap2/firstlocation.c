#include <stdio.h>
#include <string.h>

#define LENGTH 30
int containschar(char s[], char c);

int main(int argc, const char *argv[])
{
  int i;
  char s[LENGTH+1], t[LENGTH+1];

  if (argc < 3) {
    printf("Please enter two strings\n");
    return -2;
  }

  if (strlen(argv[1]) > LENGTH) {
    fprintf(stderr, "Error: first input string too long\n");
    return -2;
  }

  if (strlen(argv[2]) > LENGTH) {
    fprintf(stderr, "Error: second input string too long\n");
    return -2;
  }

  strcpy(s, argv[1]);
  strcpy(t, argv[2]);

  for(i = 0; t[i] != '\0'; i++) {
    if (containschar(t, s[i])) {
      printf("%d, %c\n", i+1, s[i]);
      return i+1;
    }
  }

  return -1;
}

/* check if string contains a character c */
int containschar(char s[], char c) {
  int i;

  for (i = 0; s[i] != '\0'; i++)
    if (s[i] == c)
      return 1;

  return 0;
}
