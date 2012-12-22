#ifndef MISCLIB_H
#define MISCLIB_H

int _strlen(char *s);
char *strrev(char s[]);
void inplace_word_reverse(char s[]);
void inplace_reverse(char s[]);

void initialize_set(int size);
int *next_subset(int bits[], int size);

#endif
