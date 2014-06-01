/* strlen: return length of s */
int strlen_custom(char s[])
{
  int i;

  while (s[i] != '\0')
    ++i;
  return i;
}
