#include <stdio.h>
#include <assert.h>

int strend(char *s, char *t)
{
  int lent, lens;
  char *sstart = s;
  char *tstart = t;

  /* get length of string s */
  for( ; *s != '\0' ; s++)
    ;
  /* get length of string t */
  for( ; *t != '\0' ; t++)
    ;
  
  /* if t is shorter/equal to s, compare the t last elements 
   * in s to all elements in t, return 1 if equivalent */
  lent = t - tstart;
  lens = s - sstart;
  if (lent <= lens) {
    s -= (lent);
    t = tstart;
    // count equivalent characters
    int i = 0;
    while ( *s == *t && *s != '\0' ) {
      ++s; ++t; ++i;
    }
    // if i > lent, we have a problem
    assert (i <= lent);
    if( i == lent )
      return 1;
  }
  return 0;
}


int main(void)
{
  int test;
  char *s = "hello world\n";
  char *t = " world\n";

  test = strend(s, t);
  printf("equivalent? %d\n", test);

  return 0;
}
