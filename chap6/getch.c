#include "getch.h"
/* getch / unget copied code */
int bufp = 0;       /* next free position in buf */

int getch(void) /*  get a (possibly pushed-back) character */
{
   return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)  /* push character back on input */
{
   if (bufp >= BUFSIZE)
      printf("Ungetch: too many characters\n");
   else
      buf[bufp++] = c;
}
