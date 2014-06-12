/* strcmp (pointer version): return <0 if s<t, o if s==t, >0 if s>t */
int strcmp(char *s, char *t)
{
  for ( ; *s == *t; s++, t++)
    if (*s == '\0')
      return 0;
  return *s - *t;
}
