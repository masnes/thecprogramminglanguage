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

/* hash: form hash value for string s */
unsigned hash(char *s)
{
   unsigned hashval;

   for (hashval = 0; *s != '\0'; s++)
      hashval = *s + 31 * hashval;
   return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
   struct nlist *np;

   for (np = hashtab[hash(s)]; np != NULL; np = np->next)
      if (strcmp(s, np->name) == 0)
         return np;     /* found */
   return NULL;         /* not found */
}

struct nlist *lookup(char *);
char *strdup(const char *);

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
   struct nlist *np;
   unsigned hashval;

   if ((np = lookup(name)) == NULL) { /* not found */
      np = (struct nlist *) malloc(sizeof(*np));
      if (np == NULL || (np->name = strdup(name)) == NULL)
         return NULL;
      hashval = hash(name);
      np->next = hashtab[hashval];
      hashtab[hashval] = np;
   } else         /* already there */
      free((void *) np->defn);   /* free previous defn */
   if ((np->defn = strdup(defn)) == NULL)
      return NULL;
   return np;
}

/* undef: remove name and definition from table */
void undef(char *name, char *defn)
{
   /* What's happening here */
   /*
    * if there's a node subsequent to the definition
    * we want to remove:
    *    copy its contents to the old definition and remove it.
    * else:
    *    just remove the node
    */
   struct nlist *np; /* node with our name/definition */
   struct nlist *todel; /* next node, if any */
   unsigned hashval;

   if ((np = lookup(name)) == NULL)   /* not found */
      return;

   if (np->next != NULL) {       /* there's another node in the last after np */
      todel = np->next;
      if (todel->name != NULL) {
         if (np->name == NULL)
            np->name = malloc(sizeof(todel->name));
         np->name = strcpy(np->name, todel->name);
      } else {
         free(np->name);
         np->name = NULL;
      }
      if (todel->defn != NULL) {
         if (np->defn == NULL)
            np->defn = malloc(sizeof(todel->name));
         strcpy(np->defn, todel->defn);
      } else {
         free(np->defn);
         np->defn = NULL;
      }
      if (todel->next != NULL)
         np->next = todel->next;
      else {
         np->next = NULL;
      }
      free(todel->name);
      free(todel->defn);
      free(todel);
   } else {                /* np is the last node in its list */
      free(np->name);
      free(np->defn);
      free(np->next);
      free(np);
   }

   return;
}
