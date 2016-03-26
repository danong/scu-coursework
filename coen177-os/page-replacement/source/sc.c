#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
// ---------- LINKED LIST ----------
// node decleration
struct node
{
	bool bit;
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
struct node* createList(int value, bool bit)
{
	struct node *ptr = (struct node*)malloc(sizeof(struct node));
	if (ptr == NULL)
	{
		fprintf(stderr, "Node creation failed!");
		return NULL;
	}
	ptr->value = value;
	ptr->next = NULL;
	ptr->bit = bit;
	head = current = ptr;
	return ptr;
}

// insert node to front of list
struct node* insertFront(int value, bool bit)
{
	if(head == NULL)
	{
		return (createList(value, 0));
	}
	
	struct node *ptr = (struct node*)malloc(sizeof(struct node));
	if (ptr == NULL)
	{
		fprintf(stderr, "Node creation failed!");
		return NULL;
	}
	ptr->bit = bit;
	ptr->value = value;
	ptr->next = head;
	head = ptr;
	return ptr;
} 

// insert node to end of list
struct node* insertTail(int value, bool bit)
{
	if(head == NULL)
	{
		return (createList(value, 0));
	}
	
	struct node *ptr = (struct node*)malloc(sizeof(struct node));
	if (ptr == NULL)
	{
		fprintf(stderr, "Node creation failed!");
		return NULL;
	}
	ptr->bit = bit;
	ptr->value = value;
	ptr->next = NULL;
	current->next = ptr;
	current = ptr;
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
// print list - only used for debugging
void print_list(void)
{
	struct node *ptr = head;
	printf("YOUR LIST: \n");
	while (ptr != NULL)
	{
		fprintf(stderr, "[%d] \n", ptr->value);
		ptr = ptr->next;
	}
	printf("END OF LIST \n");
	return;
}


// ---------- SC -----------
int sc(int cacheSize, int page)
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
		// count == cacheSize: iterate through list.
		// if head->bit == 1, change it to 0 and move to end of list and repeat
		// if head->bit == 0, swap out page
		if (count == cacheSize)
		{
			ptr = head;
			// repeat until head has ref bit == 0
			while (ptr->bit == 1)
			{
				// move node to tail and set reference bit to 0
				insertTail(ptr->value, 0);
				removeList(ptr->value);
				// ptr points to new head
				ptr = head;
			}
			// ref bit of head is now 0 so we swap it out
			removeList(ptr->value);
			// insert new page at tail with ref bit == 0
			insertTail(page, 0);
		}
		// count < cacheSize: insert page at tail of list
		else
		{
			insertTail(page, 0);
		}
	}
	// page is in list: set bit to 1
	else
	{
		ptr->bit = 1;
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
			sc(cacheSize, i); // call LRU function
		}
	}

	fprintf(stdout, "%d\n%d\n", requests, faults);

	return 0;
}
	
