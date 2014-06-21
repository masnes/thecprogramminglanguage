#define ALPHABETSIZE 512

/* strcontains: return 1 if s contains all characters in t,
 * 0 otherwise, this implementation is fast for long strings,
 * but slower for very short (<20 characters each) ones*/
int strcontains(char *s, char *t)
{
  unsigned char *tstart = (unsigned char *)t;
  unsigned char *sh, *th;
  int bitmap[ALPHABETSIZE] = { 0 };
  int ret = 1;

  // count occurences of each character in t
  th = (unsigned char *) t;
  while (*(th++) != '\0') {
    bitmap[*th]++;
  }

  // then subtract each occurence of character in s
  sh = (unsigned char *) s;
  while (*(sh++) != '\0') {
    bitmap[*sh]--;
  }

  // then see if characters in t occured enough in s
  th = tstart;
  while (*(th++) != '\0') {
    if (bitmap[*th] > 0) // not enough of that character in s
      ret = 0;
  }

  return ret;
}
