#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "define_processor.h"
#include "getch.h"
#include "getword_handling.h"
#include "hashing.h"
/*
#ifndef GETCH_C
#define GETCH_C
#include "getch.c"
#endif
#ifndef GETWORD_HANDLING_C
#define GETWORD_HANDLING_C
#include "getword_handling.c"
#endif
#ifndef HASHING_C
#define HASHING_C
#include "hashing.c"
#endif
*/

// EOL / BOF
// '#'
// define
// CAPITAL WORD
// text to end of line
// ignore EOL char '\n'

// Task1: get all BOL #defines
int main(int argc, char *argv[])
{
   char word[MAXWORD] = "\n";
   char wprev[MAXWORD] = "\n";
   char *w = word;
   char *wp = wprev;
   char c;
   while (getnext(w, wp, MAXWORD) != EOF) {
      if ((strcmp(wprev, "\n") == 0) && (strcmp(word, "#") == 0)) {
         c = getnext(w, wp, MAXWORD) == EOF;
         printf("w: %s\n", w);
         if (c == EOF)
            break;
         if (strcmp(w, "define") == 0)
            handle_define_statement(w, wp, MAXWORD);
      }
   }

   return 0;
}

int getnext(char *w, char *wp, int lim)
{
   strcpy(wp, w);
   return getword(w, lim);
}

int handle_define_statement(char *w, char *wp, int lim)
{
   char word[lim];
   char *wnew = word;

   if (strcmp(w, "define") != 0) {
      fprintf(stderr, "Error, statement not preceeded by \"define\" passed to handle_define_statement\n");
      return -1;
   }
   getnext(w, wp, lim);
   printf("%s\n", w);
   getnext(w, wp, lim);
   while (*w != '\n') {
      getword(wnew, lim);
      strncat(w, wnew, lim);
   }
   printf("%s\n", w);
}
