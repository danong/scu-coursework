#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
// ---------- LINKED LIST ----------
// node decleration
struct node
{
	int value;
	struct node *next;
};

// head and tail node declarations
// head - first node in list
// current - last node in list
struct node *head = NULL;
struct node *current = NULL;

// global count variables
unsigned int requests= 0;
unsigned int faults = 0;

// create list a list
struct node* createList(int value)
{
	struct node *ptr = (struct node*)malloc(sizeof(struct node));
	if (ptr == NULL)
	{
		fprintf(stderr, "Node creation failed!");
		return NULL;
	}
	ptr->value = value;
	ptr->next = NULL;
	head = current = ptr;
	return ptr;
}

// insert node to front of list
struct node* insertFront(int value)
{
	if(head == NULL)
	{
		return (createList(value));
	}
	
	struct node *ptr = (struct node*)malloc(sizeof(struct node));
	if (ptr == NULL)
	{
		fprintf(stderr, "Node creation failed!");
		return NULL;
	}
	ptr->value = value;
	ptr->next = head;
	head = ptr;
	return ptr;
}

// search list for a node with a given value
struct node* searchList(int value, struct node **prev)
{
	struct node *ptr = head;
	struct node *temp = NULL;
	bool found = false;
	while (ptr != NULL)
	{
		if (ptr->value == value)
		{
			found = true;
			break;
		}
		else
		{
			temp = ptr;
			ptr = ptr->next;
		}
	}
	
	if  (true == found)
	{
		if(prev)
			*prev = temp;
		return ptr;
	}
	else
	{
		return NULL;
	} 
}   


// searches list for node with a given value and deletes it
int removeList(int value)
{
	struct node *prev = NULL;
	struct node *del = NULL;
	
	del = searchList(value, &prev);
	
	if(del == NULL)
		return -1;
	else
	{
		if(prev != NULL)
			prev->next = del->next;
		if(del == current)
		{
			current = prev;
		}
		if (del == head)
		{
			head = del->next;
		}
	}
	
	free(del);
	del = NULL;
	return 0;
}
/* print list - only used for debugging
void print_list(void)
{
	struct node *ptr = head;
	printf("YOUR LIST: \n");
	while (ptr != NULL)
	{
		printf("[%d] \n", ptr->value);
		ptr = ptr->next;
	}
	printf("END OF LIST \n");
	return;
}
*/

// ---------- LRU -----------
int lru(int cacheSize, int page)
{
	int i = 0, ret = 0;
	struct node *ptr = NULL;
	struct node *prev = NULL;
	struct node *temp = NULL;
	int count = 0;
	ptr = searchList(page, &prev);
	// page is not in list: page fault
	if (ptr == NULL)
	{
		faults++;
		// count length of linked list
		ptr = head;
		while (ptr != NULL)
		{
			ptr = ptr->next;
			count++;
		}
		// delete from tail until count is strictly less than cache size
		while (count >= cacheSize)
		{
			removeList(current->value);
			count--;
		}
		// insert page at front
		insertFront(page);
	}
	// page is in list: move to head
	else
	{
		// remove page from current location
		removeList(page);
		// insert page at head
		insertFront(page);	
	}
	return 0;
}

// ---------- MAIN ----------
int main(int argc, char *argv[])
{
	// variable declerations
	int i = 0;		// holds page values
	size_t buffersize = 0;	// for getline to allocate
	ssize_t read;		// status of getline
	char *line = NULL;	// holds a line from stdin
	int cacheSize = atoi(argv[1]);	// takes cache size given as command line parameter
	
	// get lines of input  from stdin
	while((read = getline(&line, &buffersize, stdin)) != -1)
	{
		// valid input starts with a digit
		if(isdigit(line[0]))
		{
			requests++;
			i = strtol(line, NULL, 10); // convert valid number from string to base 10 int
			lru(cacheSize, i); // call LRU function
		}
	}

	fprintf(stdout, "%d\n%d\n", requests, faults);

	return 0;
}
	
