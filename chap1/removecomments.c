#include <stdio.h>
#include <assert.h>

#define IN 1 /* in a comment or quoted section */
#define OUT 0 /* not in a comment or quoted section */
#define YES 1
#define NO 0

int toggle(int state);

int main()
{
  int incomment, inmultilinecomment, inquote, delay;
  int quotetype;
  char c;
  char streambuffer[2];

  streambuffer[0] = '\0';
  streambuffer[1] = '\0';
  incomment = inmultilinecomment = inquote = OUT;
  delay = 0;

  while((c = getchar()) != EOF)
  {
    streambuffer[0] = streambuffer[1];
    streambuffer[1] = c;
    if (delay > 0)
      delay--;

    if(incomment == OUT)
    {
      if(streambuffer[0] == '/')
      {
        if(streambuffer[1] == '/' && inquote == OUT)
          incomment = IN;
        else if(streambuffer[1] == '*' && inquote == OUT)
        {
          incomment = IN;
          inmultilinecomment = IN;
        }
      }

      else if(streambuffer[0] == '\'' || streambuffer[0] == '"')
      {
        if (inquote == OUT)
        {
          inquote = IN;
          quotetype = streambuffer[0];
//          printf("\nIt's a me! Mario. We've started the quote. Here's our sign |%c%c|\n", streambuffer[0], streambuffer[1]);
        }
        else if (inquote == IN)
        {
          if(streambuffer[0] == quotetype)
          {
            inquote = OUT;
//            printf("\nIt's a me! Luigi. We've left the quote. Here's our sign |%c%c|\n", streambuffer[0], streambuffer[1]);
          }
//          else
//            printf("\nIt's a me! Bowser. Muahahahahaha!\n");
        }
      }
    }
    else if(incomment == IN)
    {
      // should never be in both a comment zone
      // and a quote zone
      assert(inquote == OUT);

      if(inmultilinecomment == OUT)
      {
        if(streambuffer[0] == '\n')
        {
          incomment = OUT;
          delay = 2;
        }
      }
      else if(inmultilinecomment == IN)
      {
        if(streambuffer[0] == '*')
          if(streambuffer[1] == '/')
          {
            inmultilinecomment = OUT;
            incomment = OUT;
            delay = 2;
          }

      }
    }

    assert(delay >= 0);
    assert(incomment == OUT || incomment == IN);
    assert(inmultilinecomment == OUT || inmultilinecomment == IN);
    assert(inquote == OUT || inquote == IN);

   if(incomment == OUT && delay == 0)
     putchar(streambuffer[0]);
  }

  putchar('\n');
} 

int toggle(int state)
{
  if(state == IN)
    return OUT;
  if(state == OUT)
    return IN;
  else
    return -1;
} 
