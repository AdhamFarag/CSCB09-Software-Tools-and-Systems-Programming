#include <stdio.h>
#include <string.h>

struct person {
  char first[10], last[10];
};

struct marriage {
  struct person person1, person2;
};

int main(void) {
  struct marriage m;
  strcpy(m.person1->first, "a");
  strcpy(m.person1->last, "b");
  printf("hello\n");
  return 0;
}
