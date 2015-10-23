/*
 * use another array to record the every root's objects it has;
 * every time union , just merge the less one to the more one 
 * that will keep log N most  tree deep
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ISUNION(p,q)  (root(p) == root(q))


static int array[10];

static void init(int array[]);
static int test(int p , int q);
static void unify(int p , int q);
static int root(int p);

int 
main(void)
{
	char buf[50];
	char cmd[10];
	int p , q;

	init(array);

	while( fgets(buf , 49 , stdin) != NULL )
	{
		if(sscanf(buf , "%s %d %d" , cmd , &p , &q) == 3)
		{
			if(strcmp(cmd , "test") == 0)
				test(p , q);
			else if(strcmp(cmd , "unify") == 0)
				unify(p , q);
			else
				printf("unknow operations\n");
		}
		else
			printf("input error\n");	
	}
	return 0;
}

static void init( int *array)
{
	int i;
	
	for( i = 0 ; i < 10 ; i++)
		array[i] = i;
}

/*
 * test if p q belong to the same union
 */
static int test(int p , int q)
{
	if(ISUNION(p,q) != 0)
		printf("yes\n");
	else
		printf("no\n");
	return 1;
}
	
/*
 * append the root of p to a child of the root
 * fo q
 */
static void unify(int p , int q)
{
	static int sz[10] = {1,1,1,1,1,1,1,1,1,1};
	int rp = root(p);
	int rq = root(q);

	if( rp == rq)
		return;
	if(sz[rp] > sz[rq])
	{
		array[rq] = rp;
		sz[rp] += sz[rq];
	}
	else
	{
		array[rp] = rq;
		sz[rq] += sz[rp];
	}
}
		
/*
 * get root
 */
static int root(int p)
{
	while( array[p] != p)
		p = array[p];
	return p;
}
		
	
