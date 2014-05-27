#include <stdio.h>

/* count lines in input */
main()
{
  int c, nl, tab, blank;

  nl, tab, blank = 0;
  while ((c = getchar()) != EOF)
  {
    if (c == '\n')
      ++nl;
    if (c == '\t')
      ++tab;
    if (c == '\0')
      ++blank;
  }

  printf("%d lines\n", nl);
  printf("%d tabs\n", tab);
  printf("%d blanks\n", blank);
}
