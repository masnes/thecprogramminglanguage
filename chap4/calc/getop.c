#include <stdio.h>
#include <ctype.h>
#include "calc.h"

/* getop:  get next character or numeric operand */
int getop(char s[])
{
  int i, c;
  static char cOld = -2;
  printf("%d\n",cOld);
  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  if (!isdigit(c) && c != '.')
    return c;      /* not a number */
  if (cOld != -2 && (cOld == '.' || isdigit(cOld)))  {
    s[++i] = cOld;
    cOld = -2;
  }
  i = 0;
  if (isdigit(c))    /* collect integer part */
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.')      /* collect fraction part */
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
  if (c != EOF)
    cOld = c;
  return NUMBER;
}
