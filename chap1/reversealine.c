#include <stdio.h>
#define MAXLINE 1000 /*  maximum input line length */
#define LONGLENGTH 50 /* lines considered "long" */

int getaline(char line[], int maxline);
void copy(char to[], char from[]);
int printlonglines(char s[], int min, int lim);

/* print the longest input line */
int main()
{
  int len;                /* current line length */
  int linelength;         /* length of currrent line */
  int max;                /* maximum length seen so far */
  char line[MAXLINE];     /* current input line */
  char longest[MAXLINE];  /* longest line saved here */

//  max = 0;
//  while ((len = getaline(line, MAXLINE)) > 0)
//    if (len > max) {
//      max = len;
//      copy(longest, line);
//    }
//  if (max > 0) /* there was a line */
//    printf("longest: \n%s", longest);

  while ((len = getaline(line, MAXLINE)) > 0)
  {
    if (len > LONGLENGTH) {
      linelength = len;
      copy(longest, line);
      if (len > 0) /* there was a line */
        printf("line: \n%slength: %d\n", longest, len);
    }
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
  printf("linelength: %d", i);
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

  j = 0;
  reversed[i+i] = '\0';
  while (j <= i) {
    reversed[j] = original[i];
    i--;
    j++;
  }

}
