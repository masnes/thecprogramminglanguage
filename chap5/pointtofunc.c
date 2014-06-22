#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <string.h>

#define MAXLINES 5000 /* max #lines to be sorted */
#define ALLOCSIZE 100000 /*  size of available space */
#define MAXLEN 1000 /* max length of any input line */

/* don't skip any characters when reading a line */
#define NOSKIP 0
/* skip non directory characters (not alphanumeric or blank) */
#define SKIPNONDIRCHARS 1

/* don't convert any characters when reading a line */
#define NOCONVERT 0
/* convert all characters to lowercase when reading a line */
#define TOLOWER 1

/* strcmpa (pointer version): return <0 if s<t, 0 if s==t, >0 if s>t */
int strcmpa(char *s, char *t)
{
  assert(s != NULL && t != NULL);
  for ( ; *s == *t; s++, t++)
    if (*s == '\0')
      return 0;
  return *s - *t;
}

/* strcmpnocase pointer version): return <0 if s<t, 0 if s==t, >0 if s>t */
int strcmpnocase(char *s, char *t)
{
  assert(s != NULL && t != NULL);
  for ( ; tolower(*s) == tolower(*t); s++, t++)
    if (*s == '\0')
      return 0;
  return tolower(*s) - tolower(*t);
}

/* isntdircha: returns 1 if character isn't a letter, number, or blank, otherwise 0 */
int isntdirchar(char c)
{
  if (isalpha(c))
    return 0;
  if (isdigit(c))
    return 0;
  if (isspace(c))
    return 0;
  return 1;
}

/*skipchar: scaffolding to determine if a character should be skipped */
int skipchar(char c, int skipmethod)
{
  if (skipmethod == NOSKIP)
    return 0;
  if (skipmethod == SKIPNONDIRCHARS) {
    if (isntdirchar(c))
      return 1;
    else
      return 0;
  }

  // only valid skip methods
  assert(skipmethod == NOSKIP || skipmethod == SKIPNONDIRCHARS);
  return 0;
}

/*charconvertscaffold: scaffolding to determine how a character should be converted, and to then return the converted character */
char charconversion(char c, int charconvertmethod)
{
  if (charconvertmethod == TOLOWER)
    return tolower(c);
  if (charconvertmethod == NOCONVERT)
    return c;

  assert(charconvertmethod == TOLOWER || charconvertmethod == NOCONVERT);
  return 0;
}

/* strcmpall: compare strings by given paramenters, returning
 * >0 if s > t, 0 if s == t, < 0 if s < t */
int strcmpall(char *s, char *t, int skipmethod, int charconvertmethod)
{
  assert(s != NULL && t != NULL);
  while (*s != '\0' && *t != '\0') {
    while (skipchar(charconversion(*s, charconvertmethod), skipmethod) && *s != '\0')
      s++;
    while (skipchar(charconversion(*t, charconvertmethod), skipmethod) && *t != '\0')
      t++;
    if (charconversion(*s, charconvertmethod) != charconversion(*t, charconvertmethod))
      break;
  }
  return charconversion(*s, charconvertmethod) - charconversion(*t, charconvertmethod);
}

/* strcontainschar: return 1 if s contains t, 0 otherwise */
int strcontainschar(char *s, char t)
{
  while (*s != '\0')
    if (*(s++) == t)
      return 1;

  return 0;
}

/* strcontains: return 1 if s contains all characters in t,
 * 0 otherwise */
int strcontains(char *s, char *t)
{
  while(*t != '\0') {
    if(!strcontainschar(s, *t))
      return 0;
    t++;
  }

  return 1;
}

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int reversed);

void qsort(void *lineptr[], int left, int right,
    int (*comp)(void *, void *, int, int), int skipmethod, int charconvertmethod);
int numcmp(char *, char *, int, int);
void swap(void *v[], int i, int j);
int numcmp(char *s1, char *s2, int, int);
double atof(char *s);

int getaline(char *, int);
char *alloc(int);

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf;  /* next free position */

/* sort input lines */

int main(int argc, char *argv[])
{
  int nlines, i;     /* number of input lines to read */
  int numeric = 0;  /* 1 if numeric sort */
  int reversed = 0; /* 1 if reversed output */
  int casesensitive = 1; /* 0 if not case sensitive */
  int directoryorder = 0; /* 1 if only checking letters/numbers/blanks */
  int charconvertmethod, skipmethod;
  int (*funcpointer)(void *, void *);

  // parse input
  for (i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (strcontains(argv[i], "n")) {
        numeric = 1;
        printf("numeric\n");
      }
      if (strcontains(argv[i], "r")) {
        reversed = 1;
        printf("reversed\n");
      }
      if (strcontains(argv[i], "f")) {
        casesensitive = 0;
        printf("notcasesensitive\n");
      }
      if (strcontains(argv[i], "d")) {
        directoryorder = 1;
        printf("directoryorder\n");
      }
    }
  }

  if (casesensitive)
    charconvertmethod = TOLOWER;
  else
    charconvertmethod = NOCONVERT;

  if (directoryorder)
    skipmethod = SKIPNONDIRCHARS;
  else
    skipmethod = NOSKIP;

  // choose sorting function to use
  if (numeric) {
    funcpointer = (int (*)(void*,void*,int,int)) numcmp;
  } else { // comparing string
    funcpointer = (int (*)(void*,void*,int,int)) strcmpall;
  }

  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    qsort((void**) lineptr, 0, nlines-1,
        funcpointer, skipmethod, charconvertmethod);
    writelines(lineptr, nlines, reversed);
    return 0;
  } else {
    printf("input too big to sort\n");
    return 1;
  }

  return 0;
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(void *v[], int left, int right,
    int (*comp)(void *, void *, int, int), int skipmethod, int charconvertmethod)
{
  int i, last;

  void swap(void *v[], int, int);

  if (left >= right)    /* do nothing if array contains */
    return;             /* fewer than two elements */
  swap(v, left, (left + right)/2);
  last = left;
  for (i = left+1; i <= right; i++) {
    //printf("i: %d, %ld, left: %d, %ld, %p right: %d, %ld\n s[i]:\"%s\", s[left]:\"%s\"\n", i, (char *) v[i] - allocbuf, left, (char *) v[left] - allocbuf, v[left], right, (char *) v[right] - allocbuf, v[i], v[left]);
    if ( ((*comp)(v[i], v[left], skipmethod, charconvertmethod)) < 0 )
      swap(v, ++last, i);
  }
  swap(v, left, last);
  qsort(v, left, last-1, comp, skipmethod, charconvertmethod);
  qsort(v, last+1, right, comp, skipmethod, charconvertmethod);
}

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

  // calculate regular values (ie 12.345)
  for (val = 0.0; isdigit(*s); s++)
    val = 10.0 * val + (*s - '0');
  if (*s == '.')
    s++;
  for (power = 1.0; isdigit(*s); s++) {
    val = 10.0 * val + (*s - '0');
    power *= 10;
  }

  /* consider e value if present (12.345e7) */
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

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2, int skipmethod, int charconvertmethod)
{
  double v1, v2;
  //char l1[MAXLEN], l2[MAXLEN];

  v1 = atof(s1);
  v2 = atof(s2);
  if (v1 < v2)
    return -1;
  else if (v1 > v2)
    return 1;
  else
    return 0;
}

void swap(void *v[], int i, int j)
{
  void *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

/* readlines:  read input lines */
int readlines(char *lineptr[], int maxlines)
{
  int len, nlines;
  char *p, line[MAXLEN];
  nlines = 0;
  while ((len = getaline(line, MAXLEN)) > 0)
    if (nlines >= maxlines || (p = alloc(len)) == NULL)
      return -1;
    else {
      line[len-1] = '\0';  /* delete newline */
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  return nlines;
}
/* writelines:  write output lines */
void writelines(char *lineptr[], int nlines, int reversed)
{
  int i;
  if (!reversed) {
    for (i = 0; i < nlines; i++)
      printf("%s\n", lineptr[i]);
  } else { // reversed
    for (i = nlines-1; i >= 0; i--)
      printf("%s\n", lineptr[i]);
  }
}


char *alloc(int n) /* returns pointer to n characters */
{
  if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
    allocp += n;
    return allocp - n; /* old p */
  } else /* note enough room */
    return 0;
}

void afree(char *p) /* free storage pointed to by p */
{
  if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
    allocp = p;
}


/*  getaline: read a line into s, return length */
int getaline(char s[], int lim)
{
  char ch;
  char *c;

  for (c = s; (ch=getchar()) != EOF && ch!='\n'; ++c)
    if (c - s < lim-1)
    {
      *c = ch;
    }
  if (ch == '\n') {
    *c = ch;
    ++c;
  }
  *c = '\0';
  return c - s;
}
