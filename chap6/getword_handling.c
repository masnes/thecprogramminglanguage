#include "getword_handling.h"
#include "getch.h"

/* getword: get next word or character from input */
char getword(char *word, int lim)
{
   int c, getch(void);
   void ungetch(int);

   char *w = word;

   while ((c = getch()) != '\n' && isspace(c))
      ;

   if (c == EOF) {
      *w = c;
      *(w+1) = '\0';
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
   } else if (is_word_char(c)) {
      handle_normal_word(w, lim, c);
      //printf("%s\n", word);
      return word[0];
   } else {
      *w = c;
      *(w+1) = '\0';
      //printf("%s\n", word);
      return word[0];
   }
}

/* is_word_char: return 1 if character is considered part of a word, 0 otherwise */
int is_word_char(char c)
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
      if (!is_word_char(*w = getch())) {
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
      w = skip_line_comment(w-1, lim, c);
   }
   else if (c == '*' && lim > 0) { // '*/' terminated comment
      w = skip_terminated_comment(w-1, lim, c);
   }
   else {
      ungetch(c);
      *(++w) = '\0';
      return ++w;
   }

   return w;
}
