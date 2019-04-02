#include <stdio.h>
#include <stdlib.h>

struct block {
  void *addr; /*start address of memory for this block */
  int size;
  struct block *next;
};

// testing function
void print_list(struct block *list) {
  struct block *cur = list;
  while(cur != NULL) {
    printf("    [addr: %p, size: %d]\n", cur->addr, cur->size);
    cur = cur->next;
  }
  printf("\n");
}

void coalesce (struct block *freelist) {
  char *target;
  struct block *cur = freelist, *next, *temp;
  while (cur) {
    target = (char *)cur->addr + cur->size;
    next = cur->next;
    while (next && next->addr == target) {
      cur->size = cur->size + next->size;
      target = target + next->size;
      temp = next->next;
      free(next);
      next = temp;
      cur->next = next;    
    }
    cur = next;    
  }
}

int main(void) {
  struct block *block1, *block2, *block3;
  block1 = malloc(sizeof(struct block));
  block1->addr = (void *)500;
  block1->size = 100;
  block2 = malloc(sizeof(struct block));
  block2->addr = (void *)600;
  block2->size = 50;
  block3 = malloc(sizeof(struct block));
  block3->addr = (void *)650; // try 651 too
  block3->size = 10;
  block3->next = NULL;
  block1->next = block2;
  block2->next = block3;
  print_list(block1);
  coalesce(block1);
  print_list(block1);
  return 0;
}
