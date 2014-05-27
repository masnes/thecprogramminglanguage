#include <stdio.h>

/* Copy input from output, replacing multiple blanks 
 * with one single blank */
main()
{
  int c, d;

  while ((c = getchar()) != EOF)
  {
    if (c != ' ')
      putchar(c);
    else {
      while ((d = getchar()) == ' ')
        ;
      putchar(c);
      if (d == EOF)
        break;
      putchar(d);
    }
  }
}   
