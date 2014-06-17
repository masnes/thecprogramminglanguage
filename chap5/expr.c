#include <stdio.h>
#include <ctype.h>
#include <assert.h>

#define MAXSIZE 1000

int stoi(char *s);
void pushint(int push);
int popint(void);
int pushchar(char chartopush);
char popchar(void);
int isoperator(char c);
int mathfunc(int first, int second, char operator);

// globals
static int intbuf[MAXSIZE];
static int intlocation = 0;
static char charbuf[MAXSIZE];
static int charlocation = 0;

int main(int argc, char *argv[])
{

  char *inputptr;
  int pushval, poppedint1, poppedint2;
  char poppedchar;

  inputptr = argv[1];
  while (--argc > 0)
  {
    if (isdigit(*inputptr)) {
      pushval = stoi(inputptr);
      pushint(pushval);

      // flush other digits in number from args list
      while (isdigit(*inputptr)) {
        inputptr++;
      }

    } else if (isoperator(*inputptr)) {
      pushchar(*inputptr++);
    }

    // skip to next arg
    if(*inputptr == '\0')
      inputptr++;
  }

  poppedint1 = poppedint2 = 0;
  poppedchar = 0;
  // while the stacks return acceptable values
  while(poppedint1 != -1 && poppedint2 != -1 && poppedchar != EOF)
  {
    poppedint1 = popint();
    poppedint2 = popint();
    poppedchar = popchar();

    if (poppedint1 != -1 && poppedint2 == -1) {
      printf("%d\n", poppedint1);
      break;
    }

    pushint(mathfunc(poppedint1, poppedint2, poppedchar));
  }

  if(poppedint1 != -1 && poppedint2 != -1) {
    fprintf(stderr, "Error: value not processed\n");
    return 1;
  }

  return 0;
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

void pushint(int inttopush)
{

  if (intlocation < MAXSIZE-1)
  {
    intbuf[intlocation] = inttopush;
    intlocation++;
  } else {
    fprintf(stderr, "Error: out of storage space for numbers, please use fewer numbers\n");
  }

  return;
}

int popint(void)
{
  int ret;
  if (intlocation > 0 && intlocation < MAXSIZE)
  {
    ret = intbuf[--intlocation];
    intbuf[intlocation] = -1; // for reference
    return ret;
  }
  else if(intlocation == 0)
  {
    ret = intbuf[0];
    intbuf[0] = -1; // for reference
    return ret;
  } else {
    if (intlocation > MAXSIZE)
      fprintf(stderr, "Error: too many numbers entered, please use less: Int space used at this time %d\n", intlocation);
    else
      fprintf(stderr, "Error: disallowed int location: %d\n", intlocation);
  }

  return -1;
}

int pushchar(char chartopush)
{
  if (charlocation < MAXSIZE -1)
  {
    charbuf[charlocation++] = chartopush;
    return 0;
  } else {
    fprintf(stderr, "Error, too many arithmetic operations, please use less!\n");
  }
  return -1;
}

char popchar(void)
{
  char ret;

  if (charlocation > 0 && charlocation < MAXSIZE)
  {
    ret = charbuf[--charlocation];
    charbuf[charlocation] = EOF;
    return ret;
  } else if (charlocation == 0) {
    ret = charbuf[charlocation];
    charbuf[charlocation] = EOF; // marking this as popped
    return ret;
  } else {
    fprintf(stderr, "Error: trying to get number for arithmetic operation, but there is none. Did you enter too many arithmetic operators (+ - * / %%) ?\n");
  }
  return EOF; // marking error
}

int isoperator(char c)
{
  if (c == '+')
    return 1;
  if (c == '-')
    return 1;
  if (c == '*')
    return 1;
  if (c == '/')
    return 1;
  if (c == '%')
    return 1;
  return 0;
}

int mathfunc(int first, int second, char operator)
{
  switch(operator)
  {
    case '+':
      return first + second;
      break;
    case '-':
      return second - first;
      break;
    case '*':
      return first * second;
      break;
    case '/':
      return second / first;
      break;
    case '%': return second % first;
      break;
    default:
      fprintf(stderr, "Error: invalid operand got placed in calculator: %c | %d\n", operator, operator);
      return 0;
      break;
  }
  fprintf(stderr, "Error: operator not processed in calculator math routine: %c", operator);
  return 0;
}
