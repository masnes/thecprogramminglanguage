#include <stdio.h>

/* print Fahrenheit-Celsius table
 *  for fahr = 0, 20, ..., 300; floating-poitn version */
main()
{
  float fahr, celsius;
  float lower, upper, step;

  lower = 0;    /* lower limit of temperature scale */
  upper = 300;  /* upper limit */
  step = 20;    /* step size */

  printf(" ∅C    ∅F\n");
  celsius = lower;
  while (celsius <= upper) {
    fahr = (9.0/5.0) * (celsius+32.0);
    printf("%3.0f %6.1f\n", celsius, fahr);

    celsius = celsius + step;
  }
}
