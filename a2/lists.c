#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lists.h"

void swap(User *curr,User *curr_next){
    int tempbalance = curr->balance;
    curr->balance = curr_next->balance;
    curr_next->balance = tempbalance;
    char *tempname = curr->name;
    curr->name = curr_next->name;
    curr_next->name = tempname;}

void bubbleSort(Group *group){
	User *start = group->users;
    int changed = 0; 
    if (start != NULL){
    while (changed == 0){
    	User *curr = start;
    	changed = 1;
    	while(curr->next != NULL){
    		if (curr->balance > curr->next->balance){
    			swap(curr,curr->next);
    			changed = 0;
    		}
    		curr = curr->next;
    	}

    }
}
} 
/* Add a group with name group_name to the group_list referred to by 
* group_list_ptr. The groups are ordered by the time that the group was 
* added to the list with new groups added to the end of the list.
*
* Returns 0 on success and -1 if a group with this name already exists.
*
* (I.e, allocate and initialize a Group struct, and insert it
* into the group_list. Note that the head of the group list might change
* which is why the first argument is a double pointer.)
*/
int add_group(Group **group_list_ptr, const char *group_name) {

	if (find_group(*group_list_ptr,group_name) != NULL){
		return -1;
	}
	else{
			Group *new_group = malloc(sizeof(Group));
			if (new_group == NULL){
				perror("MALLOC FAILED.\n");
				exit(1);
			}
			new_group->name = (char*) malloc (strlen(group_name) + 1);
			if (new_group->name == NULL){
				perror("MALLOC FAILED.\n");
				exit(1);
			}
			strncpy(new_group->name,group_name,strlen(group_name) + 1);
			new_group->name[strlen(group_name) + 1] = '\0';
			new_group->next = NULL;
			new_group->xcts = NULL;
			new_group->users = NULL;
	  if (*group_list_ptr == NULL ) {
            *group_list_ptr = new_group;
            return 0;
        } else {
            Group *curr = *group_list_ptr;
            while ( curr->next ) {
                curr = curr->next;
            }
            curr->next = new_group;
            return 0;
        }
    }
}
/* Print to standard output the names of all groups in group_list, one name
*  per line. Output is in the same order as group_list.
*/
void list_groups(Group *group_list) {
	if (group_list == NULL){
		printf("NO GROUPS EXIST \n");

	}
	else{
		Group *curr = group_list;
		while (curr != NULL){
			printf("%s\n",curr->name);
			curr = curr->next;
		}
		free (curr);
	}
}

/* Search the list of groups for a group with matching group_name
* If group_name is not found, return NULL, otherwise return a pointer to the 
* matching group list node.
*/
Group *find_group(Group *group_list, const char *group_name) {
		Group *curr = group_list;
		while (curr != NULL && (strcmp(curr->name,group_name) != 0)){
			curr = curr->next;
		}
		return curr;
}

//HELPER FUNCTION
User *find_user(User *user_list, const char *user_name) {
		User *curr = user_list;
		while (curr != NULL && (strcmp(curr->name,user_name) != 0)){
			curr = curr->next;
		}
		return curr;
}
/* Add a new user with the specified user name to the specified group. Return zero
* on success and -1 if the group already has a user with that name.
* (allocate and initialize a User data structure and insert it into the
* appropriate group list)
*/
int add_user(Group *group, const char *user_name) {
	if (find_user(group->users,user_name) != NULL){
		return -1;
	}
	else{
			User *new_user = malloc(sizeof(User));
			if (new_user == NULL){
				perror("MALLOC FAILED.\n");
				exit(1);
			}
			new_user->name = (char*) malloc (strlen(user_name) + 1);
			if (new_user->name == NULL){
				perror("MALLOC FAILED.\n");
				exit(1);
			}
			strncpy(new_user->name,user_name,strlen(user_name) + 1);
			new_user->name[strlen(user_name) + 1] = '\0';
			new_user->next = NULL;
			new_user->balance = 0;
	  if (group->users == NULL ) {
            group->users = new_user;
            return 0;
        } else {
            User *curr = group->users;
            while ( curr->next ) {
                curr = curr->next;
            }
            curr->next = new_user;
            bubbleSort(group);
            return 0;
        }
    }
}
/* Remove the user with matching user and group name and
* remove all her transactions from the transaction list. 
* Return 0 on success, and -1 if no matching user exists.
* Remember to free memory no longer needed.
* (Wait on implementing the removal of the user's transactions until you 
* get to Part III below, when you will implement transactions.)
*/
int remove_user(Group *group, const char *user_name) {
	if (find_user(group->users,user_name) == NULL){
		return -1;
	}
	else{
		User *prev = find_prev_user(group,user_name);
		User *currentUser = find_user(group->users,user_name);
		if (currentUser != NULL){
			if (strcmp(currentUser->name,group->users->name)==0){
				group->users = currentUser->next;
				currentUser->next = NULL;
				remove_xct(group,user_name);
				free(currentUser);
				return 0;
			}
			prev->next = currentUser->next;
			remove_xct(group,user_name);
            free(currentUser);
			return 0;
		}

	}
	return 0;
}

/* Print to standard output the names of all the users in group, one
* per line, and in the order that users are stored in the list, namely 
* lowest payer first.
*/
void list_users(Group *group) {
	User *curr = group->users;
	if (group->users == NULL){
		printf("NO USERS EXIST \n");
	}else{
		while (curr != NULL){
			printf("%s\n",curr->name);
			curr = curr->next;
		}
	}
	free(curr);
}

/* Print to standard output the balance of the specified user. Return 0
* on success, or -1 if the user with the given name is not in the group.
*/
int user_balance(Group *group, const char *user_name) {
	User *the_user = find_user(group->users,user_name);
	if (the_user == NULL){
		return -1;
	} 
	else{
		printf("%.2f\n",the_user->balance);
	}
    return 0;
}

/* Print to standard output the name of the user who has paid the least 
* If there are several users with equal least amounts, all names are output. 
* Returns 0 on success, and -1 if the list of users is empty.
* (This should be easy, since your list is sorted by balance). 
*/
int under_paid(Group *group) {
	User *users = group->users;
	double val = group->users->balance;
	if (users == NULL){
		return -1;
	}
	while(users!= NULL){
		if (users->balance == val){
			printf("%s\n",users->name);
		}
		users = users->next;
	}
	free(users);
    return 0;
}

/* Return a pointer to th user prior to the one in group with user_name. If 
* the matching user is the first in the list (i.e. there is no prior user in 
* the list), return a pointer to the matching user itself. If no matching user 
* exists, return NULL. 
*
* The reason for returning the prior user is that returning the matching user 
* itself does not allow us to change the user that occurs before the
* matching user, and some of the functions you will implement require that
* we be able to do this.
*/
User *find_prev_user(Group *group, const char *user_name) {
		User *curr = group->users;
		if (strcmp(curr->name,user_name) == 0)
		{
			return curr;
		}
		else{
		while (curr != NULL){
			if((strcmp(curr->next->name,user_name) == 0)){
				return curr;
			}
			curr = curr->next;
		}
	}
		return NULL;
}

/* Add the transaction represented by user_name and amount to the appropriate 
* transaction list, and update the balances of the corresponding user and group. 
* Note that updating a user's balance might require the user to be moved to a
* different position in the list to keep the list in sorted order. Returns 0 on
* success, and -1 if the specified user does not exist.
*/
int add_xct(Group *group, const char *user_name, double amount) {
	User *currentUser = find_user(group->users,user_name);
	if ( currentUser == NULL){
		return -1;
	}
	 else{
	 		Xct *new_xct = malloc(sizeof(struct xct));
	 		if (new_xct == NULL){
				perror("MALLOC FAILED.\n");
				exit(1);
			}
	 		new_xct->name = (char*) malloc (strlen(user_name) + 1);
	 		if (new_xct->name == NULL){
				perror("MALLOC FAILED.\n");
				exit(1);
			}
	 		strncpy(new_xct->name,user_name,strlen(user_name) + 1);
	 		new_xct->name[strlen(user_name) + 1] = '\0';
	 		new_xct->next = NULL;
	 		new_xct->amount += amount;
	 		currentUser->balance += amount;
	 	if (group->xcts == NULL ) {
            group->xcts = new_xct;
            bubbleSort(group);
            return 0;
        } else {
            Xct *curr = group->xcts;
            while ( curr->next ) {
                curr = curr->next;
            }
            curr->next = new_xct;
            bubbleSort(group);
            return 0;
        }

    }
}
/* Print to standard output the num_xct most recent transactions for the 
* specified group (or fewer transactions if there are less than num_xct 
* transactions posted for this group). The output should have one line per 
* transaction that prints the name and the amount of the transaction. If 
* there are no transactions, this function will print nothing.
*/
void recent_xct(Group *group, long nu_xct) {
		if (group->xcts == NULL){
		printf("\n");
	}else{
		Xct *curr = group->xcts;
		while (curr != NULL){
			if(nu_xct > 0){
				printf("NAME IS %s AND AMOUNT IS %.2f\n",curr->name,curr->amount);
			}
			curr = curr->next;
			nu_xct -= 1;
		}
	}
}
/* Remove all transactions that belong to the user_name from the group's 
* transaction list. This helper function should be called by remove_user. 
* If there are no transactions for this user, the function should do nothing.
* Remember to free memory no longer needed.
*/
void remove_xct(Group *group, const char *user_name) {
	Xct *prev = NULL;
	Xct *prevPrev =NULL;
	Xct *curr = group->xcts;
	if (curr->next == NULL &&(strcmp(curr->name, user_name) == 0)){
		group->xcts = NULL;
	}
	else{ 
		if (curr != NULL){
		while (curr->next != NULL){
			if ( strcmp(curr->name, user_name) == 0 ){
				if (prev == NULL){
					group->xcts = curr->next;
					free(curr->name);
					free (curr);
				}
				else{
					prev->next = curr->next;
					free(curr->name);
					free(curr);
				}
			}
			prevPrev = prev;
			prev = curr;
			curr = curr->next;
		}

	}
}
if (strcmp(prevPrev->next->name,user_name)==0){
	prevPrev->next = NULL;
	prevPrev = NULL;
	free(prevPrev->name);
	free(prevPrev);
	free(prev->name);
	free(prev);
	free(curr->name);
	free(curr);
}
}



int main(int argc, char const *argv[])
{
    struct group *list = NULL;
    add_group(&list,"a");
    add_group(&list,"b");
    add_group(&list,"c");
    add_group(&list,"d");
    add_group(&list,"e");
    add_group(&list,"f");

    list_groups(list);

    add_user(list,"ADHAM");
    add_user(list,"BRO-MIGO");
    add_user(list,"JOEYYYYY");
    add_user(list,"MOOOOOOOO");
    add_user(list,"MOOOOOOOO");
    add_user(list,"LOLLSSSS");

    list_users(list);

    add_xct(list,"ADHAM",5.0);
    add_xct(list,"BRO-MIGO",150.0);
    add_xct(list,"JOEYYYYY",110.0);
    add_xct(list,"LOLLSSSS",100.0);
    add_xct(list,"MOOOOOOOO",4.0);
    add_xct(list,"MOOOOOOOO",4.0);

    printf("-----------------\n");

    recent_xct(list,100);
    printf("-----------------\n");
    user_balance(list,"MOOOOOOOO");
    printf("-----------------\n");
    list_users(list);
    printf("-----------------\n");
    remove_user(list,"BRO-MIGO");
    under_paid(list);
    recent_xct(list,1000);
    add_user(list,"MAMAMAA");
    list_users(list);
    return 0;
}