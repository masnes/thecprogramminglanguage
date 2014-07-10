#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define MAXARG  50
#define BUFSIZE 100 /* buffer size for getch/ungetch */

struct tnode *addtree(struct tnode *, char *);
struct tnode *talloc(void);
char *strdupa(char *);
void treeprint(struct tnode *);
int getword(char *, int);
int getch(void); /*  get a (possibly pushed-back) character */
void ungetch(int c);  /* push character back on input */
int is_word_char(char c);
char *handle_normal_word(char *w, int lim, char startingchar);
char *handle_number(char *w, int lim, char startingchar);
char *handle_string(char *w, int lim, char startingchar);
char *handle_line_comment(char *w, int lim, char startingchar);
char *handle_possible_comment(char *w, int lim, char startingchar);

struct tnode {  /* the tree node */
   char *word;             /* Points to text */
   int count;              /* number of occurrences of text */
   struct tnode *left;     /* left child */
   struct tnode *right;    /* right child */
};

/* word frequency count */
int main(int argc, char *argv[])
{
   struct tnode *root;
   char word[MAXWORD];
   char arg1[MAXARG];
   char arg2[MAXARG];
   int chars_to_test = 6;

   if (argc > 2)
      if (strcmp(argv[1], "-n") == 0)
         chars_to_test = atoi(argv[2]);


   root = NULL;
   while (getword(word, MAXWORD) != EOF)
      if (isalpha(word[0]))
         root = addtree(root, word);
   treeprint(root);
   return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
   int cond;

   if (p == NULL) {     /* a new word has arrived */
      p = talloc();     /* make a new node */
      p->word = strdup(w);
      p->count = 1;
      p->left = p->right = NULL;
   } else if ((cond = strcmp(w, p->word)) == 0) {
      p->count++;       /* repeat word */
   } else if (cond < 0) {  /* less than into left subtree */
      p->left = addtree(p->left, w);
   } else {                /* greater than into right subtree */
      p->right = addtree(p->right, w);
   }
   return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
   if (p != NULL) {
      treeprint(p->left);
      printf("%4d %s\n", p->count, p->word);
      treeprint(p->right);
   }
}

char *strdupa(char *s) /* make a duplicate of s */
{
   char *p;

   p = (char *) malloc(strlen(s)+1); /* +1 for '\0' */
   if (p != NULL)
      strcpy(p, s);
   return p;
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
   return (struct tnode *) malloc(sizeof(struct tnode));
}
