#include <stdio.h>

/* Copy input from output, replacing multiple blanks 
 * with one single blank */
main()
{
  int c, d;

  while ((c = getchar()) != EOF)
  {
    if (c != '\0')
      putchar(c);
    else {
      while ((d = getchar()) == '\0')
        ;
      putchar(c);
      if (d == EOF)
        break;
    }
  }
}
