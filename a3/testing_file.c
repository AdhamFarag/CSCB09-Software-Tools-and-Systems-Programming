#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "worker.c"
#include "freq_list.h"

int main(int argc, char **argv)
{
  Node *head = NULL;
  char **filenames = init_filenames();
  char *listfile = "index";
  char *namefile = "filenames";
  read_list(listfile, namefile, &head, filenames);
  FreqRecord *f = get_word(head, filenames,"wood");
  print_freq_records(f);
  run_worker(index, STDIN_FILENO, STDOUT_FILENO);
  return 0;
}
