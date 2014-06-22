#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <string.h>

#define MAXLINES 5000 /* max #lines to be sorted */
#define ALLOCSIZE 100000 /*  size of available space */
#define MAXLEN 1000 /* max length of any input line */

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int reversed);

void qsorta(void *lineptr[], int left, int right,
      int (*comp)(void*,void*,int (*shouldskipchar)(char), int (*charconversion)(int)),
      int (*shouldskipchar)(char),
      int (*charconversion)(int)
      );
//int numcmp(char *, char *);
void swap(void *v[], int i, int j);
int numcmp(char *s1, char *s2);
double aatof(char *s);

int getaline(char *, int);
char *alloc(int);

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf;  /* next free position */


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

/* zerofunc: return 0 */
int zerofunc(char c)
{
  return 0;
}

/* charreturn: return value of inputted char (nop) */
int charreturn(int c)
{
  return c;
}

/* strcmpall: compare strings by given paramenters, returning
 * >0 if s > t, 0 if s == t, < 0 if s < t */
int strcmpall(char *s, char *t, int (*shouldskipchar)(int),
    int (*charconversion)(char))
{
  assert(s != NULL && t != NULL);
  while (*s != '\0' && *t != '\0') {
    while (shouldskipchar(charconversion(*s)) && *s != '\0')
      s++;
    while (shouldskipchar(charconversion(*t)) && *t != '\0')
      t++;
    if (charconversion(*s) != charconversion(*t))
      break;
    s++; t++;
  }
  return charconversion(*s) - charconversion(*t);
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

/* sort input lines */

int main(int argc, char *argv[])
{
  int nlines, i;     /* number of input lines to read */
  int numeric = 0;  /* 1 if numeric sort */
  int reversed = 0; /* 1 if reversed output */
  int casesensitive = 1; /* 0 if not case sensitive */
  int directoryorder = 0; /* 1 if only checking letters/numbers/blanks */
  // functions to use
  /* comparison function to use */
  int (*funcpointer)(void*,void*,int (*shouldskipchar)(char),int (*charconversion)(int));
  /* function used to determine if character should be skipped (possibly if not alphanum/blank, possibly a nop*/
  int (*shouldskipchar)(char);
  /* function used to convert character (possibly to lower case, possibly no conversion */
  int (*charconversion)(int);

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

  // skip non directory characters?
  shouldskipchar = directoryorder ? isntdirchar : zerofunc;

  // convert to lowercase, or just stay the same
  charconversion = casesensitive ? charreturn : tolower;

  // numeric or string comparison
  funcpointer =  numeric ?
      (int (*)(void*,void*,int (*shouldskipchar)(char),int (*charconversion)(int))) numcmp
      :
      (int (*)(void*,void*,int (*shouldskipchar)(char),int (*charconversion)(int))) strcmpall;

  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    qsorta((void**) lineptr, 0, nlines-1,
        funcpointer, shouldskipchar, charconversion);
    writelines(lineptr, nlines, reversed);
    return 0;
  } else {
    printf("input too big to sort\n");
    return 1;
  }

  return 0;
}

/* qsorta: sort v[left]...v[right] into increasing order */
void qsorta(
    void *v[], int left, int right,
    int (*comp)(void*,void*,int (*shouldskipchar)(char), int (*charconversion)(int)),
    int (*shouldskipchar)(char),
    int (*charconversion)(int)
    )
{
  int i, last;

  void swap(void *v[], int, int);

  if (left >= right)    /* do nothing if array contains */
    return;             /* fewer than two elements */
  swap(v, left, (left + right)/2);
  last = left;
  for (i = left+1; i <= right; i++) {
    //printf("i: %d, %ld, left: %d, %ld, %p right: %d, %ld\n s[i]:\"%s\", s[left]:\"%s\"\n", i, (char *) v[i] - allocbuf, left, (char *) v[left] - allocbuf, v[left], right, (char *) v[right] - allocbuf, v[i], v[left]);
    if ( ((*comp)(v[i], v[left], shouldskipchar, charconversion)) < 0 )
      swap(v, ++last, i);
  }
  swap(v, left, last);
  qsorta(v, left, last-1, comp, shouldskipchar, charconversion);
  qsorta(v, last+1, right, comp, shouldskipchar, charconversion);
}

/*  aatof: convert string s to double */
// TODO: function seems to be inconsistend for
// lines that have non number characters
// e.g. "this is real-text line, line 12"
// should return either -12, or (12?),  but
// I haven't determined actual return value
double aatof(char *s)
{
  double val, power, epower;
  int j, numsign, esign;

  // skip non-numeric characters
  while (!isdigit(*s)) {
    if (*s == EOF || *s == '\0')
      return 0;
    if (*s == '+' || *s == '-')
      numsign = (*s == '-') ? -1 : 1;
    s++;
  }

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
int numcmp(char *s1, char *s2)
{
  double v1, v2;

  v1 = atof((const char*)s1);
  v2 = atof((const char*)s2);
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
