#include <stdio.h>
#include <ctype.h>
#include <curses.h>

#define MAXLINES 100
#define MAXLINELEN 200
// MAXSTORAGE = MAXLINELEN * MAXLINES + MAXLINELEN
// this avoids strings overflowing storage buffers
// wrapped strings overwriting previous strings
#define MAXSTORAGE 2200

char strarray[MAXSTORAGE]; // stores line strings
char c; // tracks most recent character gotten

int stoi(char *s);
int getparameter(int argc, char *argv[]);
char *getaline(void);

int main(int argc, char *argv[])
{
  int numlines;
  int i, j, line;
  char *lines[MAXLINES] = { NULL };

  numlines = getparameter(argc, argv);

  i = 0;
  for (; c != EOF; line = i++ % numlines)
    lines[i] = getaline();

  if (numlines < i)
    j = i - (numlines + 1); // should be numlines steps between j and i
  else
    j = 0; // if not numlines steps, just step as many time as there are lines

  line = j++ % MAXLINES;
  for (; j < i; line = j++ % MAXLINES)
  {
    printf("%s", lines[line]);
  }
  return 0;
}

int getparameter(int argc, char *argv[])
{
  char *argget;
  int numlines;

  numlines = 10;

  if (argc == 3)
  {
    argget = argv[1];
    if (*argget == '-') {
      argget++;
      if (*argget == 'n')
      {
        argget = argv[2];
        if (isdigit(*argget)) {
          numlines = stoi(argget);
        }
      }
      else if (isdigit(*argget)) {
        numlines = stoi(argget);
      }
    } else if (*argget == 'n') {
      argget = argv[2];
      if (isdigit(*argget)) {
        numlines = stoi(argget);
      }
    } else if (isdigit(*argget)) {
      numlines = stoi(argget);
    }
  }
  else if (argc == 2)
  {
    argget = argv[1];
    if (*argget == '-') {
      argget++;
      if (isdigit(*argget))
      {
        numlines = stoi(argget);
      }
    }
    else if (isdigit(*argget)) {
      numlines = stoi(argget);
    }
  } else if (argc == 1) {
    // do nothing
  } else {
    fprintf(stderr, "Incorrect number of arguments\n");
    return -1;
  }

  return numlines;
}

int stoi(char *s)
{
  int val;
  val = 0;

  if (!isdigit(*s)) {
    fprintf(stderr, "Error: non digit character passed to stoi: %c\n", *s);
    return -1;
  }

  while (*s != '\0' && isdigit(*s)) {
    val = val * 10 + (*s - '0');
    s++;
  }

  return val;

}

/* getaline: read line from stdout, place line in buffer */
char *getaline(void)
{
  static int strarraylocation = 0;
  int charsused;
  char *ret;

  // reset to avoid overflowing strarray
  if (strarraylocation >= MAXSTORAGE - MAXLINELEN)
  {
    strarraylocation = 0;
  }

  ret = &strarray[strarraylocation];

  charsused = 0;
  while ((c = getchar()) != EOF && charsused < MAXLINELEN - 1) {
    strarray[strarraylocation++] = c;
    charsused++;

    // end a line
    if (c == '\n') {
      strarray[strarraylocation++] = '\0';
      break;
    }
  }

  // terminate cut off strings
  if (charsused == MAXLINELEN - 1) {
    strarray[strarraylocation-2] = '\n';
    strarray[strarraylocation-1] = '\0';
  }
  // add newline to EOF string
  else if (c == EOF) {
    strarray[strarraylocation++] = '\n';
    strarray[strarraylocation++] = '\0';
  }

  return ret;
}
