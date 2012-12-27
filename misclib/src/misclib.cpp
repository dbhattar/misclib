#include <cstdlib>
#include <cctype>
#include <cmath>

#include "misclib.h"
int _strlen(char *s) {
	int len = 0;
	while (*s) {
		++len;
		s++;
	}

	return len;
}

static void swap(char *a, char *b) {
	char c = *a;
	*a = *b;
	*b = c;
}

char *strrev(char s[]) {
	int len;
	char *rs;
	len = _strlen(s);
	rs = (char *) malloc(len + 1);
	rs[len--] = '\0';
	while (*s) {
		rs[len--] = *s;
		s++;
	}
	return rs;
}

static char *next_space(char *s) {
	while (*s) {
		if (isspace(*s))
			return s;
		++s;
	}
	return s;
}

static void istrrev(char *first, char *last) {
	while (first < last) {
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
		if (*space == '\0') {
			istrrev(temp, s + len - 1);
			break;
		} else {
			end = space + 1;
			istrrev(temp, --space);
			temp = end;
		}
	} while (1);
}

void inplace_reverse(char s[]) {
	int len = _strlen(s);
	char *last = s + len - 1;
	while (s < last) {
		swap(s, last);
		++s;
		--last;
	}
}

static int *bits = NULL;
static int size = 0;
static int done = 0, cardinality = 0;
void initialize_set(int _size) {
	int i;
	if (bits != NULL)
		free(bits);
	size = _size;
	bits = (int *) malloc(sizeof(int) * size);
	for (i = 0; i < size; ++i)
		bits[i] = 0;
	done = 0;
	cardinality = 0;
}

int *next_subset_direct() {
	if (done == 1) {
		return bits;
	} else {
		int i;
		for (i = 0; i < size; ++i) {
			if (bits[i] == 0) {
				bits[i] = 1;
				cardinality += 1;
				if (cardinality == size)
					done = 1;
				return bits;
			} else {
				bits[i] = 0;
				cardinality -= 1;
			}
		}
	}
	//should never reach here;
	return bits;
}

int has_next_direct() {
	return 1-done;
}

int *next_subset_gray() {
	if (done == 1)
		return bits;
	int t = cardinality % 2;
	int j = 0;
	int flag = 0;
	do {
		if (t == 0 || (j > 0 && bits[j-1] == 1)) {
			bits[j] = 1 - bits[j];
			cardinality += 2 * bits[j] - 1;
			if (cardinality == bits[size - 1])
				done = 1;
			flag = 1;
		}
		j = j + 1;
	} while(flag == 0 && j < size);
	return bits;
}

int has_next_gray() {
	return 1-done;
}

