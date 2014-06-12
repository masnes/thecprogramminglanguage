#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

/*  atof: convert string s to double */
double atof(char *s)
{
  double val, power, epower;
  int j, numsign, esign;

  for ( ; isspace(*s); s++) /* skip white space */
    ;
  numsign = (*s == '-') ? -1 : 1;
  if (*s == '+' || *s == '-')
    s++;
  for (val = 0.0; isdigit(*s); s++)
    val = 10.0 * val + (*s - '0');
  if (*s == '.')
    s++;
  for (power = 1.0; isdigit(*s); s++) {
    val = 10.0 * val + (*s - '0');
    power *= 10;
  }

  /* address e values a-la 1.37e+6 */
  if (*s == 'e' || *s == 'E') {
    s++;

    /* get the sign */
    if (*s == '-' || *s == '+') {
      esign = (*s == '-') ? -1 : 1;
      s++;
    } else {
      esign = 1;
    }

    /* get the e-based power */
    for (epower = 0; isdigit(*s); s++)
        epower = epower * 10 + (*s - '0');
    /* now multiply val by 10^epower */
    assert (esign == 1 || esign == -1);
    if (esign > 0) {
      for (j = 0; j < epower; j++)
        val *= 10;
    } else {  /* esign is negative */
      for (j = 0; j < epower; j++)
        val /= 10;
    }

  }

  return numsign * val / power;
}


int main(void)
{
  char q[20] = "1.25";
  //char q[20] = "1.25e5";
  char r[20] = "1.25e-5";
  char s[20] = "1.25e+5";
  char y[20] = "879020.093e-3";
  printf("%s: %f\n", q, atof(q));
  printf("%s: %f\n", r, atof(r));
  printf("%s: %f\n", s, atof(s));
  printf("%s: %f\n", y, atof(y));
  return 0;
}
