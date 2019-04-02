#include <stdio.h>
#include <string.h>

int main(void) {
  char s[5];
  strncpy(s, "abcdefghij", 5);
  s[strlen(s) - 1] = '\0';
  printf("%s\n", s);
  return 0;
}
