#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(struct key))
#define BUFSIZE 100 /* buffer size for getch/ungetch */

#define NOTCOMMENT 0
#define LINECOMMENT 1 /* a '//' comment */
#define TERMINATEDCOMMENT 2 /* a '/''*' comment */

struct key {
   char *word;
   int count;
} keytab[] = {
   { "auto", 0, },
   { "break", 0, },
   { "case", 0, },
   { "char", 0, },
   { "const", 0, },
   { "continue", 0, },
   { "default", 0, },
   { "do", 0, },
   { "double", 0, },
   { "else", 0, },
   { "enum", 0, },
   { "extern", 0, },
   { "float", 0, },
   { "for", 0, },
   { "goto", 0, },
   { "if", 0, },
   { "int", 0, },
   { "long", 0, },
   { "register", 0, },
   { "return", 0, },
   { "short", 0, },
   { "signed", 0, },
   { "sizeof", 0, },
   { "static", 0, },
   { "struct", 0, },
   { "switch", 0, },
   { "typedef", 0, },
   { "union", 0, },
   { "unsigned", 0, },
   { "void", 0, },
   { "volatile", 0, },
   { "while", 0 }
};

int getword(char *, int);
int binsearch(char *, struct key *, int);
int getch(void); /*  get a (possibly pushed-back) character */
void ungetch(int c);  /* push character back on input */
int iswordchar(char c);
int get_comment_state(int comment_type, int might_be_comment, int might_end_comment, char c);
char *handle_normal_word(char *w, int lim, char startingchar);
char *handle_string(char *w, int lim, char startingchar);
char *handle_possible_comment(char *w, int lim, char startingchar);
char *handle_terminated_comment(char *w, int lim, char startingchar);
char *handle_line_comment(char *w, int lim, char startingchar);

/* count C keywords */
int main()
{
   int n;
   char word[MAXWORD];

   while (getword(word, MAXWORD) != EOF)
      if (isalpha(word[0]))
         if ((n = binsearch(word, keytab, NKEYS)) >= 0)
            keytab[n].count++;
   for (n = 0; n < NKEYS; n++)
      if (keytab[n].count > 0)
         printf("%4d %s\n",
               keytab[n].count, keytab[n].word);
   return 0;
}

/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n)
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
   } else if (!iswordchar(c)) {
      *w = c;
      return word[0];
   } else {
      handle_normal_word(w, lim, c);
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
   *w = '\0';

   return w;
}

/* iswordchar: return 1 if character is considered part of a word, 0 otherwise */
int iswordchar(char c)
{
   if (isalnum(c))
      return 1;
   if (c == '_')
      return 1;
   if (c == '.')
      return 1;
   return 0;
}

/* handle_string: gets characters until the string ends */
char *handle_string(char *w, int lim, char startingchar)
{
   char c = startingchar;

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
      c = getch();
      *w++ = c;
      if (c == EOF) {
         *w++ = c;
         return w;
      }
      if (c == '"' || c == '\'')
         break;
   }

   // Terminate the string
   *w++ = '\0';
   return w;
}

/*
 * handle_line_comment: get characters until comment
 * terminates, or a character limit is reached. Then return position
 * to add next character to
 */
char *handle_line_comment(char *w, int lim, char startingchar)
{
   char c = startingchar;
   char cprev = *w;

   if (lim <= 0) {
      *w++ = '\0';
      return w;
   }
   if (c != '/' || cprev != '/') {
      fprintf(stderr, "Error: non '//' started comment passed to "
            "handle_line_comment\n"
            "cprev: %c, c: %c\n", cprev, c);
      *(++w) = '\0';
      return w;
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
 * handle_terminated_comment: get characters until comment
 * terminates, or a character limit is reached. Then return position
 * to add next character to
 */
char *handle_terminated_comment(char *w, int lim, char startingchar)
{
   char c = startingchar;
   char cprev = *w;

   if (lim <= 0) {
      *w = '\0';
      return w;
   }
   if (cprev != '/' && c != '*') {
      fprintf(stderr, "Error: non '/*' started comment passed to "
            "handle_terminated_comment \n");
      *(w++) = '\0';
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
      *w = '\0';
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
      return w;
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
