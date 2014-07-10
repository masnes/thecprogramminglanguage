// examples:
int is_var_type(char *w) // w
int binsearch(char *word, struct vartypes tab[], int n) // word, tab, n
{
   int cond; // cond
   int low, high, mid; // low high mid
   int c, getch(void); // c
}
struct tnode *addtree(struct tnode *p, char *w) // p w

int (*shouldskipchar)(char) // NOTHING

notes:
   starts with vartype
   if in parentheses, names are separated by commas and vartypes, names stop when exiting parentheses
   if not in parentheses, names are separated by commas, stop when a ';' appears
   names that terminate in '(' are actually function names

   easy way: ignore everything in parentheses
   hard way: new mode for everything in parentheses
             or handle both in one mode
