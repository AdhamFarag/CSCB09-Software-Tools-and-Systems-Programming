#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *first_letters(char *s) {
  int total = 0; // total spaces found
  char *new_s;
  char last = ' ';
  int i, j;
  i = 0;
  while (i < strlen(s)) {
    if (s[i] != ' ') {
      if (last == ' ') { // this is a non-space after a space
        last = 'x';
        total++;
      }
    }
    else
      last = ' ';
    i++;
  }
  new_s = malloc(total + 1);
  i = 0;
  j = 0;
  last = ' ';
  while (i < strlen(s)) {
    if (s[i] != ' ') {
      if (last == ' ') {
        last = 'x';
        new_s[j++] = s[i];
      }
    }
    else
      last = ' ';
    i++;
  }
  new_s[j] = '\0';
  return new_s;
}


int main(void) {
  char *s = "nothing ventured nothing gained";
  char *t = first_letters(s);
  printf("%s\n", t);
  return 0;
}
