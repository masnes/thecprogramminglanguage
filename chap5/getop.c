#include <stdio.h>
#include <ctype.h>

#define NUMBER -1

int getch(void);
void ungetch(int);

/* getop: get next character or numeric operand */
int getop(char *s)
{

  while ((*s = getch()) == ' ' || *s == '\t')
    ;
  if (!isdigit(*s) && *s != '.') { 
    *(s+1) = '\0';
    return (int)*s;     /* not a number */
  }
  if (isdigit(*s))   /*  collect integer part */
    while (isdigit(*++s = getch()))
      ;
  if (*s == '.')     /* collect fraction part */
    while (isdigit(*++s = getch()))
      ;
  *++s = '\0';
  if (*s != EOF)
    ungetch(*s);
  return NUMBER;
}
