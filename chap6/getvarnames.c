#include "getvarnames.h"
#include "getword_handling.c"

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
         ;
   }

}

/*
 * get_var_names_in_paren: addes variable names to tree, set up
 * for handling inside of parentheses
 * returns count of variables added to tree
 * returns -1 on error
 */
int get_var_names_in_paren()
{

}

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
