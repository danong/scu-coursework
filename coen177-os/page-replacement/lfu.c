#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
#include<limits.h>
// global count variables
unsigned int requests= 0;
unsigned int faults = 0;

// ---------- LRU -----------
int lfu(int page, int requestCount[], int cache[], int cacheSize)
{
	int used = 0;			// holds the number of pages in cache
	int i, temp;
	int found = -1;			// holds location of page if in cache. -1 otherwise
	int minCount = INT_MAX;		// holds count of the least frequenty used page
	int minLoc = -1;		// holds location of least frequently used page
	for (i = 0; i < cacheSize; ++i) // iterate through cache and get values for used and found
	{
		if (requestCount[i] > 0)
		{
			used++;
			if (cache[i] == page)
				found = i;
			if (requestCount[i] <= minCount)
			{
				minCount = requestCount[i];
				minLoc = i;
			}
		}
	}
	// page is not already in cache: insert page
	if (found == -1)		
	{
		faults++;
		// there is space in the cache: insert page at front
		if (used < cacheSize)
		{
			for (i = used; i >= 0; --i)
			{
				cache[i+1] = cache[i];
				requestCount[i+1] = requestCount[i];
			}
			cache[0] = page;
			requestCount[0] = 1;
		}
		// cache is full: swap out least frequently used
		else
		{
			for (i = minLoc - 1; i >= 0; --i)
			{
				cache[i+1] = cache[i];
				requestCount[i+1] = requestCount[i];
			}
			cache[0] = page;
			requestCount[0] = 1;
		}
	}
	// page is in cache
	else
	{
		temp = requestCount[found];
		for (i = found - 1; i >= 0; --i)
		{
			cache[i+1] = cache[i];
			requestCount[i+1] = requestCount[i];
		}
		cache[0] = page;
		requestCount[0] = temp+1;
	}
	return 0;
}

// ---------- MAIN ----------
int main(int argc, char *argv[])
{
	// variable declerations
	int i = 0;			// holds page values
	size_t buffersize = 0;		// for getline to allocate
	ssize_t read;			// status of getline
	char *line = NULL;		// holds a line from stdin
	int cacheSize = atoi(argv[1]);	// takes cache size given as command line parameter
	int requestCount[cacheSize];	// holds the number of times a page is requested
	int cache[cacheSize];		// holds the pages in memory
	for (i = 0; i < cacheSize; ++i)	// initialize cache and requestCount to 0
		cache[i] = requestCount[i] = 0;
	// get lines of input  from stdin
	while((read = getline(&line, &buffersize, stdin)) != -1)
	{
		// valid input starts with a digit
		if(isdigit(line[0]))
		{
			requests++;
			i = strtol(line, NULL, 10); 	// convert valid number from string to base 10 int
			lfu(i, requestCount, cache, cacheSize);// call LRU function
		}
	}

	fprintf(stdout, "%d\n%d\n", requests, faults);

	return 0;
}

	
