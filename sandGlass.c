/* file: sandGlass.c                                 		*/
/* author: 	A.M van Maurik (email: mathew9753@gmail.com) 	*/
/*			Roel Rotteveel									*/
/* date: 1-03-2017                                     		*/
/* version:                                        			*/
/* Description: 											*/


/* sandglassSetup.c, 29 January 2014
 * 
 * This is the setup for the practical assignment Sandglasses.
 * As such, it is an incomplete program: it does compile, but it does not work properly.
 */

/* 4. Add include-statements in queues.c and sandglasses.c, 
 * so that you will be able to compile your program with 
 * gcc -ansi -Wall *.c
*/ 


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queues.c"



#define TURN_NOTHING 1
#define TURN_A 2
#define TURN_B 3
#define TURN_BOTH 4




/* The function action generates a new state from an existing state.
	General idea:
		-check outcome for all states (1,2,3,4)
		-if goal state: print solvable
		-if under goal state: add to queue
		-if over goal state: do nothing


	States:
 	1. turn no sandglass 
	2. turn only sandglass A 
	3. turn only sandglass B
	4. turn both sandglasses A and B

 */

State action(State s, int action ) {
	switch(action){
		case TURN_NOTHING: 
			return s;
		case TURN_A:
			return s;
		case TURN_B:
			return s;
		case TURN_BOTH:
			return s;
	}
	return s;
}

/* The function timeable checks whether a given time can be determined
 * exactly by two sandglasses with given capacities.
 * General idea:
 	-generate all states possible from a state (where at least 1 sandglass == 0)
 	-if turning one/both sandglass does not exceed the goal state, create new states and add to queue
 	-if goal state is reached: print solvable
 	-if all states pass the goal state print NOT solvable
 */

int timeable(int cap1, int cap2, int goalTime) { 
		//int time = 0; 
		// check for simplest cases
 		if(cap1 == goalTime || cap2 == goalTime || goalTime == 0 || goalTime%cap1 == 0 || goalTime%cap2 == 0)
 		{
 			return 1;
 		}

 	
return 0;

}

/* main performs a dialogue with the user. The user is asked to provide three numbers: 
 * the (positive) capacities of the sandglasses and the goal time (>= 0).
 * The program indicates whether the goal time can be determined exactly. 
 * The dialogue is ended by the input '0'.
 */

int main(int argc, char *argv[]){
		  int cap1, cap2, goalTime; 
		  printf("give the sandglass capacities and the goal time: ");
		  scanf("%d",&cap1);
		  while ( cap1 > 0 ) 
		  {
		    scanf("%d",&cap2);
		    assert( cap2 > 0 );
		    scanf("%d",&goalTime);
		    assert( goalTime >= 0 );
		    if ( timeable(cap1,cap2,goalTime) ) 
		    {
		      printf("%d and %d can time %d\n", cap1, cap2, goalTime);
		    } else 
		    {
		      printf("%d and %d cannot time %d\n", cap1, cap2, goalTime);
		    }
		    printf("\ngive the sandglass capacities and the goal time: ");
		    scanf("%d",&cap1);
		  }  
		  printf("good bye\n");
		  return 0;
}