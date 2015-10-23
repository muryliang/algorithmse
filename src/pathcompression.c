/*
 * in addition to the weightunion , every time search the root
 * of one node , put every node in path to a child of the root(root());
 * or put every other node's parent to its origin grandparent(root2())
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
static int root2(int p);

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
static int root(int ori)
{
	int p = ori;
	int tmp;
	
	while( array[p] != p)
		p = array[p];

/*
 * do the path compression; now p is the root;
 * let every node in the path from ori to root
 * be a direct child of the root
 */
	while( array[ori] != p )
	{
		tmp = array[ori];
		array[ori] = p;
		p = tmp;
	}
	return p;
}


		
static int root2(int ori)
{
	int p = ori;
/*
 * another method, on the path to the root
 * make every other node's parent(that is , keep step of 2) to its original grandparent
 * to halve the height of the tree
 */
	while( array[p] != p){
		array[p] = array[array[p]];
		p = array[p];
	}

	return p;
}
		
	
