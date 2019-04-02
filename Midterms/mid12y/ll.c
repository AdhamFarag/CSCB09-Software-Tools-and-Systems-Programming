#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
  char s[30];
  struct node *next;
} Name;

char *tostring (const Name *nl) {
  const Name *cur = nl;
  int total = 0, numspaces = 0;
  char *s;
  while (cur) {
    total += strlen(cur->s);
    if (cur->next) {numspaces = numspaces + 1;
    cur = cur->next;}
  }
  s = malloc(total + numspaces + 1);
  s[0] = '\0';
  cur = nl;
  while (cur) {
    strcat (s, cur->s);
    if (cur->next) {strcat (s, " ");
    cur = cur->next;}
  }
  return s;
}

int main(void) { //Testing
  Name *n1 = malloc(sizeof(Name));
  Name *n2 = malloc(sizeof(Name));
  char *ret;  
  
  strcpy(n1->s, "dan");
  strcpy(n2->s, "z");
  n1->next = n2;
  n2->next = NULL;
  ret = tostring (n1);
  printf ("%s\n", ret);
  free (ret);
  ret = tostring (NULL); // should produce empty string
  printf ("%s\n", ret);
  printf ("%d\n", (int)strlen(ret));
  free (ret);
  free (n1);
  free (n2);
  return 0;
}
