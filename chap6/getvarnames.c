#include "getvarnames.h"
#include "getword_handling.c"

/* variable name frequency count */
int main()
{
   struct tnode *root = NULL;

   root = get_var_names(root);
   treeprint(root);
   return 0;
}

//int get_var_names(struct tnode *root)
//{
//   int count;
//
//}

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
struct tnode *get_var_names(struct tnode *root)
{
   char word[MAXWORD];

   while (getword(word, MAXWORD) != EOF) {
      if (is_var_type(word))
         root = handle_variable_outof_paren(root, word);
      if (word[0] == '(')
         root = get_var_names_in_paren(root);
   }

   return root;

}

/*
 * handle_variable_outof_paren: parse for variable names
 * when outside of any parentheses, to be used after a
 * vartype (char, int, etc.)
 */
struct tnode *handle_variable_outof_paren(struct tnode *root, char *starting_var)
{
   char word[MAXWORD];
   char nextword[MAXWORD];

   assert(starting_var != NULL);

   if (!is_var_type(starting_var)) {
      fprintf(stderr, "Error: handle_variable_outof_paren called, but previous word string was not a variable type\n");
      return 0;
   }

   if (is_struct(starting_var)) {
      // skip the structure type
      getword(word, MAXWORD);
   }

   getword(word, MAXWORD);
   while (getword(nextword, MAXWORD) != ';' && nextword[0] != EOF) {
      if(nextword[0] == '(')
         root = get_var_names_in_paren(root);
      else // don't add a word followed by a parentheses
         if(is_word_char(word[0])) {
            addtree(root, word);
         }
      strcpy(word, nextword);
   }

   return root;
}

/*
 * get_var_names_in_paren: adds variable names to tree, set up
 * for handling inside of parentheses
 * returns count of variables added to tree
 * returns -1 on error
 */
struct tnode *get_var_names_in_paren(struct tnode *root)
{
   char word[MAXWORD];

   while (word[0] != ')' && word[0] != EOF) {
      getword(word, MAXWORD);
      if (word[0] == '(')
         root = get_var_names_in_paren(root);
      while (is_var_type(word))
         // stops setting word to next vartype (if any)
         // while statement will re-loop if there is another
         // vartype within the loop
         root = handle_variable_in_paren(root, word);
   }

   return root;
}

/*
 * handle_variable_in_paren: given an input vartype
 * (char, int, etc.), will copy all names of that vartype
 * to the btree, then set it's parent pointer (starting_var),
 * to the next vartype if any
 */
struct tnode *handle_variable_in_paren(struct tnode *root, char *starting_var)
{
   char word[MAXWORD];
   char nextword[MAXWORD];

   assert(starting_var != NULL);

   if (!is_var_type(starting_var)) {
      fprintf(stderr, "Error: handle_variable_outof_paren called, but previous word string was not a variable type\n");
      return 0;
   }

   if (is_struct(starting_var)) {
      // skip the structure type
      getword(word, MAXWORD);
   }

   getword(word, MAXWORD);
   while (!(is_var_type(nextword)) && nextword[0] != ')') {
      getword(nextword, MAXWORD);
      if (nextword[0] == '(')
         // stop on '(', ignoring word followed by it (if any)
         // later, will return the parentheses to calling function
         root = get_var_names_in_paren(root);
      else
         if (is_word_char(word[0]))
            root = addtree(root, word);
   }


   strcpy(starting_var, nextword);

   return root;
}

/* is_var_type: checks if a word is the name of a variable type */
int is_var_type(char *w)
{
   if (binsearch(w, vartypes, NUMVARTYPES) != -1)
      return 1;
   return 0;
}

/* is_struct: determines if a word is "struct" */
int is_struct(char *w)
{
   if (strcmp(w, "struct") == 0)
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
