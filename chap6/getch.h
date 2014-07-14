#ifndef _GETCH_H_
#define _GETCH_H_
#include <stdio.h>

#define BUFSIZE 100 /* buffer size for getch/ungetch */

char buf[BUFSIZE];  /* buffer for ungetch */
int bufp;       /* next free position in buf */

void ungetch(int c);  /* push character back on input */
int getch(void); /*  get a (possibly pushed-back) character */
#endif
