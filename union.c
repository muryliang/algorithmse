#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10
#define BUF 255

static int array[MAX];

static void test(int , int );
void initarray(void);
int isunified(int , int);
void unify(int , int);

int
main(void)
{
	char linebuf[BUF];/*store the geted line*/
	char cmd[BUF]; /*store the cmd*/
	int a , b; /*store two numbers to test or unify*/
	
	initarray();

	printf("start , every thing is alone\n");
	printf("now get input....\n");
	
	while(1)
	{
		if(fgets(linebuf , BUF , stdin) == NULL )
			exit(1); /*wrong something*/

		if(3 != sscanf(linebuf , "%s %d %d" , cmd , &a , &b))
			exit(2); /*wrong args input*/
	
		if(strcmp(cmd , "test"))
			test(a , b);
		else if(strcmp(cmd , "unify"))
			unify(a , b);
	/*	else if(strcmp(cmd , "init"))
			initarray();
	*/	
		else{
			printf("unknown cmd\n");
		}
	}
	
		
/*	
	test(3 , 5);
	test(1 , 6);
	
	unify(1 , 4);
	unify(1 , 6);
	unify(2 , 3);
	unify(5 , 0);
	unify(6 , 2);
	
	
	test(3 , 2);
	test(1 , 6);
	test(1 , 3);
	test(7 , 8);
	test(2 , 5);
*/

	return 0;
}

static void test(int i , int j)
{
	printf("testing %d %d... " , i , j);
	if(isunified(i , j) == 1)
		printf("yes\n");
	else
		printf("no\n");
}

void initarray(void)
{
	int i;
	
	for(i = 0 ; i < MAX ; i++)
	{
		array[i] = i;
	}
}

void unify(int i , int j)
{
	int srcval = array[i];
	int destval = array[j];
	/*convert every one whose value equal to srcval to the val destval*/

	int index;

	printf("unifying %d %d... \n" , i , j);

	for(index = 0 ; index < MAX ; index++)
	{
		if(array[index] == srcval)
			array[index] = destval;
	}
}

int isunified(int i , int j)
{
	return (array[i] == array[j]) ? 1 : 0;
}
	
