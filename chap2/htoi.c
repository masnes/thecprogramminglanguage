#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int hexstringtoint(char hexstring[]);
int hexchartoint(char c);

/* convert string of hexadecimal digits into an integer value */
int main()
{
  char supershort[] = "8";
  char empty[] = "";
  //char shortbuff[] = "0x8f"; // 143
  //char longbuff[] = "0x238fa"; //145658
  //char extralongbuff[] = "0xf2ac29fd148f38a8d8c"; // -209023604
  char nohex[] = "f28ab"; // 993451
  //char bigX[] = "0X128"; // 296
  char nozero[] = "axabf"; // NAN (would be 2751)
  //char weird[] = "0x2r3"; // NAN

  printf("supershort\t(8): %d\n", hexstringtoint(supershort));
  printf("empty\t(8): %d\n", hexstringtoint(empty));
  //printf("shortbuff\t(143): %d\n", hexstringtoint(shortbuff));
  //printf("longbuff\t(145658): %d\n", hexstringtoint(longbuff));
  //printf("extralongbuff\t(-209023604): %d\n", hexstringtoint(extralongbuff));
  printf("nohex\t(993451): %d\n", hexstringtoint(nohex));
  //printf("bigX\t(296): %d\n", hexstringtoint(bigX));
  printf("nozero\t(NAN - would be 2751): %d\n", hexstringtoint(nozero));
  //printf("weird\t(NAN): %d\n", hexstringtoint(weird));

  return 0;

}

/* convert string of hexadecimal digits into an integer value */
int hexstringtoint(char hexstring[]) {
  int i, count, offset, ret, charval;

  offset = 0; // offset to first hex character in string
  ret = 0; // value to return at end of func

  // check for 0x, 0X at start of string
  if (hexstring[1] == 'x' || hexstring[1] == 'X') {
    if (hexstring[0] == '0') {
      offset = 2;
    } else {
      fprintf(stderr, "Error: Input string must start with 0X, 0x, or first character in hex string\n" \
          "string started with: %c%c\n", hexstring[0], hexstring[1]);
      return -1;
    }
  }



  count = 0;
  for(i = strlen(hexstring) - 1; i >= offset; i--) {
    if(!isxdigit(hexstring[i]))
    {
      fprintf(stderr, "Error, non hexidecimal digit passed to hex string converter\n");
      return -1;
    }

    charval = hexchartoint(hexstring[i]);
    charval *= powl(16, count);
    ret += charval;
    count++;
  }

  return ret;

}

int hexchartoint(char c) {
  int ret;

  if(!isxdigit(c))
  {
    fprintf(stderr, "Error, non hexidecimal digit passed to hex char converter\n");
    return 0;
  }

  if(c >= '0' && c <= '9')
    ret = c - '0';
  else if(c >= 'a' && c <= 'f')
    ret = c - 'a' + 10;
  else if(c >= 'A' && c <= 'F')
    ret = c - 'A' + 10;
  else {
    fprintf(stderr, "Error, non hexidecimal digit passed to hex char converter\n");
    fprintf(stderr, "Note: passed digit not caught by isxdigit!\n");
    return 0;
  }

  return ret;
}
