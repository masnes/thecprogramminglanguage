#include <stdio.h>

/* copy input to output; 2nd version */
main()
{
  int c;
  int iseof;

  while (1) 
  {

    iseof = ((c = getchar()) != EOF);

    if (iseof == 0)
      break;

    putchar(c);
    putchar(' ');
    printf("0 or 1: %d\n", iseof);
  }


  char eof = EOF;
  
  printf("EOF code: %d, displayed as: %c\n", eof, eof);
}
