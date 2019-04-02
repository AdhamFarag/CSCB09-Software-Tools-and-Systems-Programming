#include <stdlib.h>
#include <stdio.h>

int main(void) {
  char *p;
  // assume malloc succeeds and returns address 1234
  p = malloc(sizeof(char));
  *p = 0;
  p++;
  free(p);
  printf("hello\n");
  return 0;
}
