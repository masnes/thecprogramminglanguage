#ifndef _HASHING_H_
#define _HASHING_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

struct nlist {       /* table entry: */
   struct nlist *next;     /* next entry in chain */
   char *name;             /* defined name */
   char *defn;             /* replacment text */
};

unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
void undef(char *name, char *defn);

#endif
