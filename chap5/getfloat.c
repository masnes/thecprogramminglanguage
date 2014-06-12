#include <stdio.h>
#include <math.h>
#include <ctype.h>

int getch(void); /*  get a (possibly pushed-back) character */
void ungetch(int c);  /* push character back on input */

float getfloat(float *pn)
{
  int i;
  float c, sign;
  float fraction = 0.0f;

  while (isspace(c = getch())) /* skip whitespace */
    ;
  if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
    ungetch(c); /* it is not a number */
    return 0;
  }
  sign = (c == '-') ? -1.0f : 1.0f;
  if (c == '+' || c == '-') {
    c = getch();
    if(!isdigit(c) && c != '.') {
      ungetch(c);
      return 0.0f;
    }
  }
  for(*pn = 0.0f; isdigit(c); c = getch())
    *pn = 10.0f * *pn + (c - '0');
  if (c == '.')
    for (i = 1; isdigit(c = getch()); i++)
      fraction += (float)(c - '0') / powf(10, 1);
  *pn += fraction;
  *pn *= sign;
  if (c != EOF)
    ungetch(c);
  return c;
}

int main(void)
{
  float floatval;

  getfloat(&floatval);
  printf("floatval: %f\n", floatval);

  return 0;
}
#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch */
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
