#include "cross_referencer.h"
#include "getword_handling.h"

/* word frequency count */
int main()
{
   struct tnode *root;
   char word[MAXWORD];
   int linenum = 1;
   int found = 0;

   root = NULL;
   while (getword(word, MAXWORD) != EOF) {
      if (isalpha(word[0]))
         if (binsearch(word, ignore, NUMWORDSINIGNORE) == -1)
            root = addtree(root, word, linenum);
      if (word[0] == '\n') {
         linenum++;
         found = 1;
      }
   }
   treeprint(root);
   printf("linenum: %d\n", linenum);
   return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int linenum)
{
   int cond;

   if (p == NULL) {     /* a new word has arrived */
      p = talloc();     /* make a new node */
      p->word = strdup(w);
      p->count = 1;
      p->lines[0] = linenum;
      p->i = 1;
      p->left = p->right = NULL;
   } else if ((cond = strcmp(w, p->word)) == 0) {
      p->count++;       /* repeat word */
      p->lines[p->i++] = linenum;
   } else if (cond < 0) {  /* less than into left subtree */
      p->left = addtree(p->left, w, linenum);
   } else {                /* greater than into right subtree */
      p->right = addtree(p->right, w, linenum);
   }
   return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
   int i;

   if (p != NULL) {
      treeprint(p->left);

      printf("%4d %s\n", p->count, p->word);
      printf("found on lines: ");
      for (i = 0; i < (p->i)-1; i++)
         printf("%d, ", p->lines[i]);
      printf("%d\n", p->lines[i]);

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

/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct ignore tab[], int n)
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
