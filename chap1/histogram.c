#include <stdio.h>
#include <assert.h>

#define   IN   1  /* in a word */
#define   OUT  2  /* not in a word */
#define   MAXCHAR 20 /* largest possible number of characters looked for in word */

/* print a historgram of the lengths of words in input */
main()
{
  int c, ln, oldchar, i, j, state, charinword; 
  int ndigit[MAXCHAR];

  for (i = 0; i <= MAXCHAR; i++)
    ndigit[i] = 0;

  charinword = 0;
  ln = 0;
  state = OUT;
  while ((c = getchar()) != EOF) 
  {
    if (state == OUT) {
      if (c == ' ' || c == '\t' || c == '\n') {
        if (c == '\n')
          ++ln;
      } else {
        state = IN;
        ++charinword;
      }
    } else { /* state = IN */
      if (c == ' ' || c == '\t' || c == '\n') {
        if (c == '\n')
          ++ln;
        if (charinword-1 > MAXCHAR)
          charinword = MAXCHAR+1;

        assert(charinword > 0);

        ndigit[charinword-1]++;
        //printf("length: %d, ending char: %c on line: %d\n", charinword, oldchar, ln);
        charinword = 0;
        state = OUT;
      } else {
        ++charinword;
      }
    }
    oldchar = c;
  }

  for (i = 0; i < MAXCHAR; ++i)
  {
    printf("%2d: ", i+1);
    // printf("%d ", ndigit[i]);
       for (j = 0; j < ndigit[i]; ++j)
       printf("#");
    printf("\n");
  }

}
