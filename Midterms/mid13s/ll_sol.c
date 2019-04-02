#include <string.h>
#include <stdlib.h>

#include <stdio.h>


struct node {
  char s[30];
  struct node *next;
};


int findnode(const struct node *head, const struct node *find) 
{
  while (head != NULL && head != find)
  
  head = head->next;
 
 return head != NULL;
}


int main(void) {
  struct node *n1 = malloc(sizeof(struct node));
  struct node *n2 = malloc(sizeof(struct node));
  struct node *n3 = malloc(sizeof(struct node));

  strcpy(n1->s, "dan");
  strcpy(n2->s, "dan");
  strcpy(n3->s, "dan");

  n1->next = n2;
  n2->next = NULL;
  n3->next = NULL;
  printf("%d\n", findnode(n1, n2)); //outputs 1
  printf("%d\n", findnode(n1, n3)); //outputs 0
  return 0;
}
