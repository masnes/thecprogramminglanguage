#include <stdio.h>
#define MAXLINE 1000 /*  maximum input line length */
#define LONGLENGTH 50 /* lines considered "long" */

int getaline(char line[], int maxline);
void copy(char to[], char from[]);
void reverse(char reversed[], char original[]);

/* print each line in reverse */
int main()
{
  int len;                /* current line length */
  int linelength;         /* length of currrent line */
  char line[MAXLINE];     /* current input line */
  char linecopy[MAXLINE];  /* copy line saved here */
  char linereversed[MAXLINE];  /* reversed line saved here */

//  max = 0;
//  while ((len = getaline(line, MAXLINE)) > 0)
//    if (len > max) {
//      max = len;
//      copy(linecopy, line);
//    }
//  if (max > 0) /* there was a line */
//    printf("linecopy: \n%s", linecopy);

  while ((len = getaline(line, MAXLINE)) > 0)
  {
    copy(linecopy, line);
    reverse(linereversed, linecopy);
    printf("%s", linecopy);
    printf("\nreversed:\n");
    printf("%s", linereversed);
    printf("\n");
  }

  return 0;
}

/*  getaline: read a line int os, return length */
int getaline(char s[], int lim)
{
  int c, i;

  for (i=0; (c=getchar()) != EOF && c!='\n'; ++i)
    if (i < lim-1)
    {
      s[i] = c;
      if (c == '\n') {
        s[i] = c;
        ++i;
      }
    }
  s[i] = '\0';
  return i;
}

/*  copy: copy 'from' into 'to'; assume to is big enough  */
void copy(char to[], char from[])
{
  int i;

  i = 0; 
  while ((to[i] = from[i]) !='\0')
    ++i;
}

void reverse(char reversed[], char original[])
{
  // get length of string to be reversed;
  int len, i, j;

  i = 0;
  while (original[i] != '\0')
    ++i;

  len = i+1;

  j = 0;
  while (j < len && i >= 0) {
    reversed[j] = original[i-1];
    i--;
    j++;
  }

//  printf("\n");
//  i = 0;
//  while (reversed[i] != '\0')
//  {
//    printf("%c",reversed[i]);
//    i++;
//  }
//  printf("\n");
}
