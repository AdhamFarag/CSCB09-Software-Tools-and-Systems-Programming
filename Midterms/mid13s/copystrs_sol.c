#include <string.h>
#include <stdio.h>

void copystrs(char *s, char **strs, int max) {
  s[0] = '\0';
  while (*strs && max > 0) {
    strncat(s, *strs, max);
    max -= strlen(*strs);
    strs++;
  }
}

int main(void) {
  char s[6];
  char *strs[4] = {"ab", "cd", "ef", NULL};
  copystrs(s, strs, 5);
  printf("%s\n", s); // outputs abcde
  return 0;
}
