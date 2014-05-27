#include <stdio.h>
#include <assert.h>

#define   IN   1  /* in a word */
#define   OUT  2  /* not in a word */
#define   NUMCHARS 128 /* largest possible number of characters looked for in word */

/* print a historgram of the lengths of words in input */
main()
{
  int c, i, j; 
  int ndigit[NUMCHARS];

  for (i = 0; i <= NUMCHARS; i++)
    ndigit[i] = 0;

  while ((c = getchar()) != EOF)
  {
    if (c > NUMCHARS-1)
      ndigit[NUMCHARS]++;
    else
      ndigit[c]++;
  }

  for (i = 0; i <= NUMCHARS; ++i)
  {
    if (i == '\n')
      printf("%3d \\n:", i);
    else if (i == '\t')
      printf("%3d \\t:", i);
    else if (i == '\0')
      printf("%3d \\0:", i);
    else
      printf("%3d %c: ", i, i);
    // printf("%d ", ndigit[i]);
    for (j = 0; j < ndigit[i]; ++j)
      printf("#");
    printf("\n");
  }

}
