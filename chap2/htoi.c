#include <stdio.h>
#include <string.h>

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
static int getLine (char *prmpt, char *buff, size_t sz)
{
  int ch, extra;

  // Get line with buffer overrun protection
  if (prmpt != NULL) {
    printf ("%s", prmpt);
    fflush(stdout);
  }

}

/* convert string of hexadecimal digits into an integer value */
/*
int main()
{
  if (
      }
  */
