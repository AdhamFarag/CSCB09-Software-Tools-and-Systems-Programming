#include <stdio.h>
#include <string.h>

int str_insert(char *dest, char *newstr, char c, int size_dest) {
	if(strlen(dest) + strlen(newstr) + 1 > size_dest) { return -1; }
int i = 0; 
while((i < strlen(dest)) && (dest[i] != c)) { i++; }
if(i == strlen(dest)) { return -2; } 

else {
/* move the last part of dest out of the way */ 
	int k = strlen(dest) + strlen(newstr) -1; int j = strlen(dest) -1;
for(j = strlen(dest) - 1; j > i; j--, k--) { dest[k] = dest[j]; }
i++;

 for(k = 0; k < strlen(newstr); k++) {
  dest[i + k] = newstr[k]; 
}
} return 0;
}


/*Sample call*/

int main(void) {
  char s[50] = "hellol";
  str_insert (s, 'l', 'q');
  printf ("%s\n", s);
  return 0;
}
