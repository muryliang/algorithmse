/*
 * this is the quickunion function , 
 * use a forest to implement the union operations.
 * whenever you call union , the root of the first
 * (which has its value equal to its index) will be
 * a child of the root of the second value
 *  it looks more efficient than the quickfind ,
 *  but if tree is too tall , will be also inefficient
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
	int rp = root(p);
	int rq = root(q);

	if( rp == rq)
		return;
	array[rp] = rq;
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
		
	
