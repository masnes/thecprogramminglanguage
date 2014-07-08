#ifndef _GETVARNAME_H_
#define _GETVARNAME_H_

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100 /* buffer size for getch/ungetch */
#define STOP   -1
#define NUMVARTYPES 6 // number of variable types searched for (struct, int, char, etc)
#define STRUCT 0 // location of "struct" in vartypes

struct qualifiers {
   char * word;
} qualifiers[] = {
   { "long" },
   { "unsigned" }
};
struct vartypes {
   char *word;
} vartypes[] = {
   { "struct" }, // If this location is changed STRUCT must be \
   redefined
   { "int" },
   { "void" },
   { "char" },
   { "float" },
   { "double" }
};

// I'll use this for storing variable names
struct tnode {  /* the tree node */
   char *word;             /* Points to text */
   int count;              /* number of occurrences of text */
   struct tnode *left;     /* left child */
   struct tnode *right;    /* right child */
};

struct qualifiers; 
struct tnode *addtree(struct tnode *, char *);
struct tnode *talloc(void);
char *strdupa(char *);
void treeprint(struct tnode *);
int binsearch(char *, struct vartypes *, int);
int get_var_name(char *, int);
int is_var_type(char *w);


#endif
