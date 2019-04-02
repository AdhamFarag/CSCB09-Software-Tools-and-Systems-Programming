#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include "worker.h"
#include "freq_list.h"
/* The function get_word should be added to this file */
FreqRecord *get_word(Node *head, char **filenames,char *word){
	int i = 0;
	int k = 0;
    FreqRecord *f_list = malloc(MAXRECORDS*sizeof(FreqRecord));
    if (f_list == NULL){
    	perror("MALLOC FAILIURE");
    	exit(1);
    }
    Node *curr = head;
    while (curr != NULL){
    	if(strcmp(curr->word,word) == 0){
    		while(i < MAXFILES){
    			if (curr->freq[i] == 0){
    				i++;
    			}
    			else{
    				FreqRecord *fr = malloc(sizeof(FreqRecord));
    				if (fr == NULL){
    					perror("MALLOC FAILIURE");
    					exit(1);
    				}
    				fr->freq = curr->freq[i];
    				strcpy(fr->filename,filenames[i]);
    				f_list[k] = *fr;
    				i++;
    				k++;
    		}
    	}
        break;
    }
    	else{
    		curr = curr->next;
    	}
    }

    if (curr == NULL){
        FreqRecord *fr = malloc(sizeof(FreqRecord));
        if (fr == NULL){
            perror("MALLOC FAILIURE");
            exit(1);
            }
            fr->freq = 0;
            return fr;
    }
    return f_list;
}

/* Print to standard output the frequency records for a word.
* Used for testing.
*/
void print_freq_records(FreqRecord *frp) {
	int i = 0;
	while(frp != NULL && frp[i].freq != 0) {
		printf("%d    %s\n", frp[i].freq, frp[i].filename);
		i++;
	}
}

/* run_worker
* - load the index found in dirname
* - read a word from the file descriptor "in"
* - find the word in the index list
* - write the frequency records to the file descriptor "out"
*/
void run_worker(char *dirname, int in, int out){
	char index_dir[PATHLENGTH];
    char namefile[PATHLENGTH];
    Node *head = NULL;
    char **filenames = init_filenames();
    strcpy(index_dir,dirname);
    strcpy(namefile,dirname);
    strcat(index_dir,"/index");
    strcat(namefile,"/filenames");
    read_list(index_dir, namefile, &head, filenames);
    printf("found dir\n");
    char word[MAXWORD];
    read(in,word,MAXWORD);
    FreqRecord *f = malloc(sizeof(FreqRecord));
    f = get_word(head,filenames,word);
    int i = 0;
    while (f!= NULL && f[i].freq!=0){
        close(in);
        write(out,&f[i],sizeof(FreqRecord));
        i++;
    }
}