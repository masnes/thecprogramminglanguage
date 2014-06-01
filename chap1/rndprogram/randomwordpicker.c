#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAXWORDSIZE 20 /* words cannot be longer than 21 characters */
#define NUMWORDS 3 /* number of words to look at */
#define ON 1 /* currently on a word */
#define OFF 2 /* not currently on a word */

int isawordchar(char c);
int printwords(char words[NUMWORDS][MAXWORDSIZE+1]);
int printwordsfull(char words[NUMWORDS][MAXWORDSIZE+1]);
int printawordfull(char word[MAXWORDSIZE]);
int prettysecureseed();
void printascii();

int main()
{
  int ch, i, j, k, state, isword, wordcount, wordtorecord, seedcheck;
  long int r;
  char currword[MAXWORDSIZE+1];
  //char padding[MAXWORDSIZE+1];
  char words[NUMWORDS][MAXWORDSIZE+1];

  for (i = 0; i <= NUMWORDS; i++)
    for (j = 0; j <= MAXWORDSIZE; j++)
    {
      words[i][j] = 0;
//      padding[j] = 0;
    }

  seedcheck = prettysecureseed();
  if (seedcheck != 0)
  {
    fprintf(stderr, "ERROR: failed to properly seed random number generator\n");
    return -1;
  }

  state = OFF;
  wordcount = 0;
  wordtorecord = 0;
  while ((ch = getchar()) != EOF)
  {
    isword = isawordchar(ch);

    if (state == OFF) {
      if (isword) {
        state = ON;
        i = 0;
        wordcount++;
        currword[i] = ch;
        i++;
      } else {
        // do nothing
      }

    } else { // state == ON

      // should never reach an "ON" state
      // with wordcount < 1
      assert(wordcount > 0);

      if (isword) {
        if (i < MAXWORDSIZE)
        {
          currword[i] = ch;
          i++;
        }
        else {
          // do nothing
        }
      }
      else {
        // TODO possible bug, should be <=
        assert(i < MAXWORDSIZE);
        currword[i] = '\0';

        // less likely to pick a word
        // as we see more of them
        r = random() % (wordcount+1);
        while (r == 1)
        {
          printf("r: %ld, wordcount: %d\n", r, wordcount);
          printf("
          printawordfull(currword);
          assert(wordtorecord <= NUMWORDS);

//          if (wordtorecord == NUMWORDS)
//          {
//            printf("\n");
//            printf("last word: ");
//            for (j = 0; j <= MAXWORDSIZE; j++)
//            {
//              printf("%3d ", currword[j]);
//            }
//            printf("\n");
//            for (j = 0; j <= MAXWORDSIZE; j++)
//            {
//              printf("%c", currword[j]);
//            }
//            printf("\n");
//          }

          for (k = 0; k <= MAXWORDSIZE; k++)
          {
            words[wordtorecord][j] = currword[j];
          }
          // redundant safety check
          // force null byte placement in case of overflow
          words[wordtorecord][MAXWORDSIZE] = '\0';

          wordtorecord++;
          if (wordtorecord > NUMWORDS)
          {
//            printwordsfull(words);
            wordtorecord = 0;
          }

        // possibly go through loop again, possibly exit
        r = random() % (wordcount+1);
        }

        state = OFF;
      }
    }
  }

  printwordsfull(words);
  //printawordfull(padding);

  //printf("wordcount: %d\n", wordcount);

//  printascii();

  return 0;
}

int prettysecureseed()
{
  unsigned int seed;
  int randomData = open("/dev/urandom", O_RDONLY);
  size_t randomDataLen = 0;
  while (randomDataLen < sizeof seed)
  {
    ssize_t result = read(randomData, ((char*)&seed) + randomDataLen, (sizeof seed) - randomDataLen);
    if (result < 0)
    {
      // error, unable to read /dev/random
      return -1;
    }
    randomDataLen += result;
  }

  srandom(seed);

  return 0;

}

/* print the words for the user */
int printwords(char words[NUMWORDS][MAXWORDSIZE+1])
{
  int j, k;
  for (j = 0; j <= NUMWORDS; j++)
  {
    k = 0;
    while (words[j][k] != '\0' && k <= MAXWORDSIZE)
    {
      putchar(words[j][k]);
      k++;
    }
    putchar('\n');
  }

  return 0;
}

/* mostly for debuggin */
int printawordfull(char word[MAXWORDSIZE+1])
{
  int i;

  for (i = 0; i <= MAXWORDSIZE; i++)
    printf("%3d ", word[i]);
  printf("\n");

  for (i = 0; i <= MAXWORDSIZE; i++)
    printf("%c", word[i]);
  printf("\n");

  return 0;
}

/* mostly for debuggin */
int printwordsfull(char words[NUMWORDS][MAXWORDSIZE+1])
{
  int j, k;

  for (j = 0; j <= NUMWORDS; j++)
  {
    for (k = 0; k <= MAXWORDSIZE; k++)
    {
      printf("%3d ", words[j][k]);
    }
    printf("\n");
  }

  for (j = 0; j <= NUMWORDS; j++)
  {
    for (k = 0; k <= MAXWORDSIZE; k++)
    {
      if (words[j][k] == '\0')
        break;
      putchar(words[j][k]);
    }
    putchar('\n');
  }

  return 0;

}

/* check if a character is an 'in word' character
 *  ascii values that are part of a word:
 *  48-57, 65-90, 97-122
 **/
int isawordchar(char c)
{
  // if we're passing in a non-character value that's a problem
  assert(c > -2);
  // passing in EOF is probably a problem as well
  assert(c > -1);

  if (c >= 48 && c <= 57)
    return 1;
  if (c >= 65 && c <= 90)
    return 1;
  if (c >= 97 && c <= 122)
    return 1;
  if (c > 127)
    // possible expanded charset word character
    // program will include it
    return 1;

  return 0;
}

void printascii()
{
  int i;

  for (i = 48; i < 128; i++)
  {
    printf("%3d: %c \t", i, i);
    if (i % 10 == 0)
      printf("\n");
  }
}
