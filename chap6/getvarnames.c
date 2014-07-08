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

struct tnode *addtree(struct tnode *, char *);
struct tnode *talloc(void);
char *strdupa(char *);
void treeprint(struct tnode *);
int binsearch(char *, struct vartypes *, int);
int get_var_name(char *, int);
char getword(char *, int);
int getch(void); /*  get a (possibly pushed-back) character */
void ungetch(int c);  /* push character back on input */
int iswordchar(char c);
int is_var_type(char *w);
char *handle_normal_word(char *w, int lim, char startingchar);
char *handle_number(char *w, int lim, char startingchar);
char *handle_string(char *w, int lim, char startingchar);
char *get_line_comment(char *w, int lim, char startingchar);
char *get_terminated_comment(char *w, int lim, char startingchar);
char *skip_line_comment(char *w, int lim, char startingchar);
char *skip_terminated_comment(char *w, int lim, char startingchar);
char *handle_possible_comment(char *w, int lim, char startingchar);

// I'll use this for storing variable names
struct tnode {  /* the tree node */
   char *word;             /* Points to text */
   int count;              /* number of occurrences of text */
   struct tnode *left;     /* left child */
   struct tnode *right;    /* right child */
};

/* variable name frequency count */
int main()
{
   struct tnode *root;
   char word[MAXWORD];
   char c;

   root = NULL;
   while ((c = getword(word, MAXWORD)) != EOF)
      if (isalpha(c))  //
         if (is_var_type(word))
               root = addtree(root, word);
   treeprint(root);
   return 0;
}

/* get_var_names: get the names of variables
 * a variable comes after a vartype ("char", "int", etc.), but is not
 * followed by an opening paren '('
 * vartype checking is left to other functions
 *
 * notes:
 *    all variables start with a vartype
 *    if we're in parentheses, names are separated by commas and
 *    vartypes, names stop when exiting parentheses
 *
 *    if we're not in parentheses, names are separated by commas,
 *    stop when a ';' appears
 *
 *    names that terminate in '(' are actually function names
 *
 *    structs have an extra word proceeding the variable name
 *
 *    need new mode for handling inside parentheses
 */
int get_var_names_outof_paren()
{
   char word[MAXWORD];
   char prevword[MAXWORD];
   struct tnode *root;

   // if word is a vartype
   if (is_var_type(prevword)) {
      while (getword(word, MAXWORD) != EOF)
   }

}

/*
 * get_var_names_in_paren: addes variable names to tree, set up
 * for handling inside of parentheses
 * returns count of variables added to tree
 * returns -1 on error
 */
int get_var_names_in_paren(

/* is_var_type: checks if a word is the name of a variable type */
int is_var_type(char *w)
{
   if (binsearch(w, vartypes, NUMVARTYPES) != -1)
      return 1;
   return 0;
}

/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct vartypes tab[], int n)
{
   int cond;
   int low, high, mid;

   low = 0;
   high = n - 1;
   while (low <= high) {
      mid = (low+high) / 2;
      if ((cond = strcmp(word, tab[mid].word)) < 0)
         high = mid - 1;
      else if (cond > 0)
         low = mid + 1;
      else
         return mid;
   }
   return -1;
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
char getword(char *word, int lim)
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
   for ( ; --lim > 0; w++)
      if (!iswordchar(*w = getch())) {
         ungetch(*w);
         break;
      }
   if (lim == 0)
      ungetch(*w);
   *w++ = '\0';

   return w;
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
      w = handle_line_comment(w-1, lim, c);
   }
   else if (c == '*' && lim > 0) { // '*/' terminated comment
      w = handle_terminated_comment(w-1, lim, c);
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
