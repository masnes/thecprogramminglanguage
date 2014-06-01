
/*
 */
for (i=0; i < lim-1 && (c=getchar()) != '\n' && c != EOF; i++)
  s[i] = c;

while (i < lim-1)
{
  c=getachar();
  if (c == '\n')
    return;
  if (c == EOF)
    return;
  s[i++] = c;
}
