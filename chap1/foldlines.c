#include <stdio.h>
#include <assert.h>
#include <ctype.h>

#define MAXLINELEN 80

int findblank(char inputchars[MAXLINELEN+1]);

int main()
{
  int i, j, blanklocation, offset;
  char line[MAXLINELEN+1];
  char c;

  i = 0;
  while((c = getchar()) != EOF)
  {
    line[i] = c;
    i++;

    if ( c == '\n')
    {
      for(j = 0; j <= i; j++)
        putchar(line[j]);
      i = 0;
    }
    // split line
    // print first bit
    else if (i == MAXLINELEN)
    {
      blanklocation = findblank(line);
      for(j = 0; j <= blanklocation; j++)
        putchar(line[j]);
      putchar('\\');
      putchar('\n');
      for(j = blanklocation+1; j <= MAXLINELEN; j++)
      {
        offset = j - blanklocation - 1;
        line[offset] = line[j];
      }
      // clear rest of line
      for(j = offset+1; j <= MAXLINELEN; j++)
        line[j] = '\0';
      i = offset;
    }
    // otherwise repeat loop

  }
  for(j = 0; j <= i; j++)
    putchar(line[j]);
  putchar('\n');
}

/* return location of farthest blank character
 * or 0 if none found */
int findblank(char inputchars[MAXLINELEN+1])
{
  int i;

  for(i = MAXLINELEN; i >= 0; i--)
  {
    if(isblank(inputchars[i]))
      break;
  }

  return i;
}
