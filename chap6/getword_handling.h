#ifndef _GETWORD_HANDLING_H_
#define _GETWORD_HANDLING_H_
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

char getword(char *word, int lim);
int iswordchar(char c);
char *handle_normal_word(char *w, int lim, char startingchar);
char *handle_number(char *w, int lim, char startingchar);
char *handle_string(char *w, int lim, char startingchar);
char *skip_line_comment(char *w, int lim, char startingchar);
char *get_line_comment(char *w, int lim, char startingchar);
char *skip_terminated_comment(char *w, int lim, char startingchar);
char *get_terminated_comment(char *w, int lim, char startingchar);
char *handle_possible_comment(char *w, int lim, char startingchar);

#endif
