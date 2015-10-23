#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define ISUNION(p,q)  (root(p) == root(q))
#define N 20


static int array[N * N];

static void init(int array[]);
static int test(int p , int q);
static void unify(int p , int q);
static int root(int p);
static int root2(int p);
static int myrandom(int n); /* generate a number between 0 to n-1 */
static void printtable(int (*)[N]);


int 
main(void)
{
	int state[N][N];
	int i , j;

	srand(time((time_t *)NULL ));
	init( array); /*initialize the array */

	for( i = 0 ; i < N ; i++)
		for(j = 0 ; j < N ; j++){
			state[i][j] = myrandom(2); /*initialize to 0(block) or 1(open)*/
		}

	printtable(state);

/* do the unify*/
	for( i = 0 ; i < N ; i++){
		for(j = 0; j < N ; j++){
			if( state[i][j] != 0)
			{
	
				if( i -1 >= 0 && state[i-1][j] != 0)
					unify((i-1)*N + j , i*N + j);
				if( i +1 < N  && state[i+1][j] != 0)
					unify((i+1)*N + j , i*N + j);
				if( j -1 >= 0 && state[i][j-1] != 0)
					unify(i*N + j-1 , i*N + j);
				if( j +1 < N && state[i][j+1] != 0)
					unify(i*N + j+1 , i*N + j);
			}
		}
	}
	
/*unify is over  , now test the percolate */
	

	for( i = 0 ; i < N ; i++){
		unify(array[0] , array[i]);
		unify(array[(N-1)*N ] , array[(N-1)*N+i]);
	}

	test( array[0] , array[N*N-1]);
	
	return 0;
}


static void init( int *array)
{
	int i;
	
	for( i = 0 ; i < N*N ; i++)
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
	static int sz[N*N];
	static int flag = 0;
	int rp = root(p);
	int rq = root(q);
	int i;

	if( flag == 0){
		flag = 1;
		for( i = 0 ; i < N*N ; i++ )
			sz[i] = 1;
	}
	

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
/*
 * just fix a bug here , ori = tmp;  
 * becareful !!
 */
	while( array[ori] != p )
	{
		tmp = array[ori];
		array[ori] = p;
		ori = tmp;
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
		
	
static void  printtable(int (*a)[N])
{
	int i , j;

	for( i = 0; i < N ; i++){
		for( j = 0 ; j < N ; j++)
		{
			printf("%3d" , a[i][j]);
		}
		putchar('\n');
	}

}

/*
 * if you want to  set the random of the p percent
 * then just use  RAND_MAX * p , and then rand() ,
 * test if result < the above  result  ,then  1  
 * else 0( use this to simulate the percent)
 */
static int myrandom( int n)
{
return (rand() / (RAND_MAX / n + 1));
}
