#include <stdlib.h>
#include <ctype.h>

int _strlen(char *s) {
   int len = 0;
   while(*s) {
      ++len;
      s++;
   }

   return len;
}

void swap(char *a, char *b) {
    char c = *a;
    *a = *b;
    *b = c;
}

char *strrev(char s[]) {
   int len;
   char *rs;
   len = _strlen(s);
   rs = (char *)malloc(len+1);
   rs[len--] = '\0';
   while(*s) {
      rs[len--] = *s;
      s++;
   }
   return rs;
}

char *next_space(char *s) {
   while(*s) {
      if(isspace(*s))
         return s;
      ++s;
   }
   return s;
}

void istrrev(char *first, char *last) {
   while(first < last) {
      swap(first, last);
      ++first;
      --last;
   }
}

void inplace_word_reverse(char s[]) {
   char *space, *end, *temp = s;
   int len = _strlen(s);
   do {
      space = next_space(temp);
      if(*space == '\0') {
         istrrev(temp, s+len-1);
         break;
      }
      else {
         end = space+1;
         istrrev(temp, --space);
         temp = end;
      }
   } while(1);
}

void inplace_reverse(char s[]) {
   int len = _strlen(s);
   char *last = s+len-1;
   while(s < last) {
      swap(s, last);
      ++s;
      --last;
   }
}

