#ifndef _DISTINCT_WORDS_H__
#define _DISTINCT_WORDS_H__

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct tnode *addtree(struct tnode *, char *);
struct tnode *talloc(void);
char *strdupa(char *);
void treeprint(struct tnode *);
struct tnode *treeprocess(struct tnode *wordcountroot, struct tnode *countroot);
struct tnode *addtreebycount(struct tnode *p, char *w, int count);

struct tnode {  /* the tree node */
   char *word;             /* Points to text */
   int count;              /* number of occurrences of text */
   struct tnode *left;     /* left child */
   struct tnode *right;    /* right child */
};

#ifndef MAXWORD
#define MAXWORD 100
#endif
#ifndef BUFSIZE
#define BUFSIZE 100 /* buffer size for getch/ungetch */
#endif

#endif
