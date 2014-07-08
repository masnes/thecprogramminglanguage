#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100 /* buffer size for getch/ungetch */

struct tnode *addtree(struct tnode *, char *);
struct tnode *talloc(void);
char *strdupa(char *);
void treeprint(struct tnode *);
int getword(char *, int);
int getch(void); /*  get a (possibly pushed-back) character */
void ungetch(int c);  /* push character back on input */
int iswordchar(char c);
char *handle_normal_word(char *w, int lim, char startingchar);
char *handle_number(char *w, int lim, char startingchar);
char *handle_string(char *w, int lim, char startingchar);
char *get_line_comment(char *w, int lim, char startingchar);
char *handle_possible_comment(char *w, int lim, char startingchar);

struct tnode {  /* the tree node */
   char *word;             /* Points to text */
   int count;              /* number of occurrences of text */
   struct tnode *left;     /* left child */
   struct tnode *right;    /* right child */
};

/* word frequency count */
int main()
{
   struct tnode *root;
   char word[MAXWORD];

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

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
   int c, getch(void);
   void ungetch(int);

   char *w = word;

   while (isspace(c = getch()))
      ;

   if (c == EOF) {
      *w = c;
      //printf("%s\n", word);
      return word[0];
   }

   if (c == '"' || c == '\'') {
      handle_string(w, lim, c);
      //printf("%s\n", word);
      return word[0];
   } else if (c == '/') {
      handle_possible_comment(w, lim, c);
      //printf("%s\n", word);
      return word[0];
   } else if (isdigit(c)) {
      handle_number(w, lim, c);
      //printf("%s\n", word);
      return word[0];
   } else if (iswordchar(c)) {
      handle_normal_word(w, lim, c);
      //printf("%s\n", word);
      return word[0];
   } else {
      *w = c;
      //printf("%s\n", word);
      return word[0];
   }
}

/* handle_normal_word: write a normal word to the word buffer */
char *handle_normal_word(char *w, int lim, char startingchar)
{
   char c = startingchar;

   if (lim <= 0) {
      *w++ = '\0';
      return w;
   }

   *w++ = c;
   lim--;
   for ( ; --lim > 1; w++)
      if (!iswordchar(*w = getch())) {
         ungetch(*w);
         break;
      }
   if (lim == 0)
      ungetch(*w);
   *w++ = '\0';

   return w;
}

/* iswordchar: return 1 if character is considered part of a word, 0 otherwise */
int iswordchar(char c)
{
   if (isalpha(c))
      return 1;
   if (c == '_')
      return 1;
   if (c == '.')
      return 1;
   return 0;
}

/* handle_number: handles number words */
char *handle_number(char *w, int lim, char startingchar)
{
   char c = startingchar;
   char cprev = 'c'; // initialize cprev to non-digit character

   while (lim > 1) {
      if (isdigit(c) || ((c == ',' || c == '.') && isdigit(cprev))) {
         *w++ = cprev = c;
         c = getch();
         lim--;
      } else
         break;
   }
   ungetch(c);
   *w++ = '\0';
   return w;
}

/* handle_string: gets characters until the string ends */
char *handle_string(char *w, int lim, char startingchar)
{
   char stringtype = startingchar;
   char c = startingchar;
   char cprev;

   if (lim <= 0) {
      *w++ = '\0';
      return w;
   }
   if (startingchar != '"' && startingchar != '\'') {
      fprintf(stderr, "Error: non quote passed to "
            "handle_string, expected a quote!");
      *w++ = '\0';
      return w;
   }

   *w++ = c;
   while (--lim > 1) {
      cprev = c;
      c = getch();
      *w++ = c;
      if (c == EOF) {
         *w++ = c;
         return w;
      }
      if (c == stringtype && cprev != '\\')
         break;
   }

   // Terminate the string
   *w++ = '\0';
   return w;
}

/*
 * skip_line_comment: get characters until comment
 * terminates, discarding them. Return null string
 */
char *skip_line_comment(char *w, int lim, char startingchar)
{
   char c = startingchar;
   char cprev = *w;

   if (c != '/' || cprev != '/') {
      fprintf(stderr, "Error: non '//' started comment passed to "
            "get_line_comment\n"
            "cprev: %c, c: %c\n", cprev, c);
      *(++w) = '\0';
      return ++w;
   }

   while((c = getch()) != EOF && c !='\n')
      ;

   // return the newline to the char buffer
   // this way it's exactly as if the comment didn't exist
   ungetch(c);
   // make a null string
   *w++ = '\0';
   return w;
}
/*
 * get_line_comment: get characters until comment
 * terminates, or a character limit is reached. Then return position
 * to add next character to
 */
char *get_line_comment(char *w, int lim, char startingchar)
{
   char c = startingchar;
   char cprev = *w;

   if (lim <= 0) {
      *w++ = '\0';
      return w;
   }
   if (c != '/' || cprev != '/') {
      fprintf(stderr, "Error: non '//' started comment passed to "
            "get_line_comment\n"
            "cprev: %c, c: %c\n", cprev, c);
      *(++w) = '\0';
      return ++w;
   }

   while (lim > 1) {
      if (c == EOF) {
         *w = EOF;
         return w;
      }
      if (c == '\n') {
         *w++ = c;
         *w++ = '\0';
         return w;
      }
      lim--;
      // Assign to word
      *w++ = c;
      // Get next character
      c = getch();
   }

   ungetch(c);
   *w++ = '\0';
   return w;
}

/*
 * skip_terminated_comment: get characters until comment
 * terminates, discarding them.
 * return null string
 */
char *skip_terminated_comment(char *w, int lim, char startingchar)
{
   char c = startingchar;
   char cprev = *w;

   if (cprev != '/' && c != '*') {
      fprintf(stderr, "Error: non '/*' started comment passed to "
            "get_terminated_comment \n");
      *w++ = '\0';
      return w;
   }

   while (cprev != '*' || c != '/') {
      cprev = c;
      c = getch();
      if (c == EOF)
         break;
   }

   *w++ = '\0';
   return w;
}

/*
 * get_terminated_comment: get characters until comment
 * terminates, or a character limit is reached. Then return position
 * to add next character to
 */
char *get_terminated_comment(char *w, int lim, char startingchar)
{
   char c = startingchar;
   char cprev = *w;

   if (lim <= 0) {
      *w++ = '\0';
      return w;
   }
   if (cprev != '/' && c != '*') {
      fprintf(stderr, "Error: non '/*' started comment passed to "
            "get_terminated_comment \n");
      *w++ = '\0';
      return w;
   }

   while (lim > 1) {
      if (c == EOF) {
         *w = EOF;
         return w;
      }
      if (cprev == '*' && c == '/') {
         *w++ = c;
         break;
      }
      // Assign to word
      *w++ = c;
      // Get next character
      cprev = c;
      lim--;
      if (lim > 0)
         c = getch();
   }

   *w++ = '\0';
   return w;
}

/*
 * handle_possible_comment: tests for comment, if comment returns full
 * text of comment (up to some limit), else returns first character of
 * suspected comment
 */
char *handle_possible_comment(char *w, int lim, char startingchar)
{
   char c = startingchar;

   if (lim <= 0) {
      *w++ = '\0';
      return w;
   }
   if (c != '/') {
      fprintf(stderr, "Error: non '/' beginning passed to "
            "handle_possible_comment\n");
      *(++w) = '\0';
      return w;
   }

   *w++ = c;
   c = getch();
   lim--;

   if (c == '/' && lim > 0) { // line comment
      w = get_line_comment(w-1, lim, c);
   }
   else if (c == '*' && lim > 0) { // '*/' terminated comment
      w = get_terminated_comment(w-1, lim, c);
   }
   else {
      ungetch(c);
      *(++w) = '\0';
      return ++w;
   }

   return w;

}

/* getch / unget copied code */
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
