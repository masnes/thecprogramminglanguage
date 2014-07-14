#ifndef _CROSS_REFERENCER_H_
#define _CROSS_REFERENCER_H_
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLINES 1024
#define MAXWORD 100
#define BUFSIZE 100 /* buffer size for getch/ungetch */
#define NUMWORDSINIGNORE 9

struct tnode {  /* the tree node */
   char *word;             /* Points to text */
   int count;              /* number of occurrences of text */
   struct tnode *left;     /* left child */
   struct tnode *right;    /* right child */
   int i; /* location to add next linenumber */
   int lines[MAXLINES];    /* lines where text occured */
};

struct ignore {
   char *word;
} ignore[] = {
   { "and" },
   { "i" },
   { "if" },
   { "in" },
   { "of" },
   { "shall" },
   { "that" },
   { "the" },
   { "to" }
};

struct tnode *addtree(struct tnode *, char *, int linenum);
struct tnode *talloc(void);
char *strdupa(char *);
void treeprint(struct tnode *);
int binsearch(char *word, struct ignore tab[], int n);

#endif
