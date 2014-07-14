#include "distinct_words.h"
#include "getword_handling.h"


/* word frequency count */
int main()
{
   struct tnode *wordroot;
   struct tnode *countroot;
   char word[MAXWORD];

   wordroot = countroot = NULL;
   while (getword(word, MAXWORD) != EOF)
      if (isalpha(word[0]))
         wordroot = addtree(wordroot, word);

   countroot = talloc();
   countroot->word = "";
   countroot->count = 0;
   countroot->left = countroot->right = NULL;

   countroot = treeprocess(wordroot, countroot);
   treeprint(countroot);
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

/* addtree: add a node with w, at or below p */
struct tnode *addtreebycount(struct tnode *p, char *w, int count)
{
   if (p == NULL) {     /* a new word has arrived */
      p = talloc();     /* make a new node */
      p->word = strdup(w);
      p->count = count;
      p->left = p->right = NULL;
   } else if (strcmp(w, p->word) == 0) {
      p->count++;       /* repeat word */
   } else if (count <= p->count) {  /* less than eq into left subtree */
      p->left = addtreebycount(p->left, w, count);
   } else {                /* greater than into right subtree */
      p->right = addtreebycount(p->right, w, count);
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

/*
 * treeprocess: process the old tree (sorted alphabetically)
 * into a new tree (sorted by count)
 */
struct tnode *treeprocess(struct tnode *p, struct tnode *d)
{
   struct tnode *ret = NULL;

   if (p != NULL) {
      treeprocess(p->left, d);
      ret = addtreebycount(d, p->word, p->count);
      treeprocess(p->right, d);
   }

   return ret;
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
