#include <stdio.h>

void main() {
   char s[] = "Hello world!";
   char *rs;
   rs = strrev(s);
   printf("length: %d\n", _strlen(s));
   //printf("%s\t%s\n", s, rs);
   printf("%s\n", s);
   //inplace_word_reverse(s);
   inplace_reverse(s);
   printf("%s\n", s);
}
