#include <stdio.h>
#include <assert.h>

static char daytab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

/*  day_of_year: set day of year frommonth & day */
int day_of_year(int year, int month, int day)
{
  int i, leap;

  if (month > 12 || month < 1) {
    fprintf(stderr, "Error: passing incorrect month to func day_of_year: %d", month);
    return -1;
  }
  if (day > 365 || day < 1) { 
    fprintf(stderr, "Error: passing incorrect day to func day_of_year: %d", day);
    return -1;
  }
  if (year < 0) {
    fprintf(stderr, "Error: passing incorrect year to func day_of_year: %d", year);
    return -1;
  }

  leap = ( (year % 4 == 0) && (year % 100 != 0) ) || (year % 400 == 0);
  for (i = 1; i < month; i++)
    day += daytab[leap][i];
  return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
  int i, leap;

  if (yearday > 366 || yearday < 1) {
    fprintf(stderr, "Error: passing incorrect yearday to func month_day: %d", yearday);
    return;
  }
  if (year < 0) {
    fprintf(stderr, "Error: passing incorrect year to func month_day: %d", year);
    return;
  }
  if (pmonth == NULL) {
    fprintf(stderr, "Error: passing NULL *pmonth to func month_day");
    return;
  }
  if (pday == NULL) {
    fprintf(stderr, "Error: passing NULL *pday to func month_day");
    return;
  }

  leap = ( (year % 4 == 0) && (year % 100 != 0) ) || (year % 400 == 0);
  if (yearday == 366 && !leap) {
    fprintf(stderr, "Error: Only 365 days in are allowed in a non leap year! (yearday of 366 passed to month_day on non leap year.) ");
    return;
  }
  for ( i = 1; yearday > daytab[leap][i]; i++) {
    assert(i <= 12);
    yearday -= daytab[leap][i];
  }
  *pmonth = i;
  *pday = yearday;
}

/*  month_name: return name of n-th month */
char *month_name(int n)
{
  static char *name[] = {
    "Illegal month",
    "January", "February", "March",
    "April", "May", "June",
    "July", "August", "September",
    "October", "November", "December"
  };

  return (n < 1 || n > 12) ? name[0] : name[n];
}
