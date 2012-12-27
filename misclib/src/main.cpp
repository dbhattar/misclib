#include <stdio.h>
#include "misclib.h"

static void print_array(int *a, int n) {
	for(int i = n-1; i >= 0; --i)
		printf("%d ", a[i]);
	printf("\n");
}

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
   int size = 4;
   printf("Subsets using counting method\n");
   initialize_set(size);
   while(has_next_direct()) {
	   int *set = next_subset_direct();
	   print_array(set, size);
   }
   printf("Gray Code\n");
   initialize_set(size);
   while(has_next_gray()) {
	   int *set = next_subset_gray();
	   print_array(set, size);
   }
}
