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

State fillState(int time, int timeA, int timeB){
	State newState;
	newState.time = time;
	newState.sg1 = timeA;
	newState.sg2 = timeB;
	return newState;

}
/* This function returns the smallest value of 2 integers */
int smallestValue(int a, int b){
	if (a < b){
		return a;
	} else if (b < a){
		return b;
	} 
	/* The values are the same. */
	return a;
}

void showState(State s){
	printf("The time now is: %d, we have timeleftA: %d, we have timeLeftB: %d\n", s.time, s.sg1, s.sg2);
}

State action(State s, int action, int cap1, int cap2 ) {
	/* What is actually happening here? To understand that we have to fully understand the sandGlass problem.*/	
	int smallestNumberOfSeconds;

	switch(action){
		case TURN_NOTHING:
			/* In this case we have to determine wich one of the values is the smallest */
			/* One of them has to be zero, so we are looking for the nonzero value*/
			/* This value needs to be added to the time. */
			if (s.sg1 == 0){
				/* Whenever s.sg1 == 0, this means that the remainder of s.sg2 has to be added to the time */
				s = fillState(s.time+s.sg2,0,0);
			} else {
				/* In this case s.sg2 == 0, means that the remainder of s.sg1 has to be added to the time */
				s = fillState(s.time+s.sg1,0,0);
			}
			return s;

		case TURN_A:
			/* Determine the remainders. */
			s.sg1 = cap1 - s.sg1;

			if (s.sg2 == 0){
				s = fillState(s.time+s.sg1,0,s.sg2);
				return s;
			}
			smallestNumberOfSeconds = smallestValue(s.sg1,s.sg2);

			s = fillState(s.time+smallestNumberOfSeconds, s.sg1- smallestNumberOfSeconds, s.sg2 - smallestNumberOfSeconds);
			return s;



			

			/* 

			newA = cap1 - s.sg1;

			smallestNumberOfSeconds = smallestValue(newA,s.sg2);

			s = fillState(s.time+smallestNumberOfSeconds,newA - smallestNumberOfSeconds, s.sg2 - smallestNumberOfSeconds);
			*/

		case TURN_B:
			/* Check what happends if we turn SandGlass B.*/
			/*
			newB = cap2 - s.sg2;

			smallestNumberOfSeconds = smallestValue(newB,s.sg1);

			s = fillState(s.time+smallestNumberOfSeconds,s.sg1 - smallestNumberOfSeconds, cap2 - smallestNumberOfSeconds);
			*/


			/* Determine the remainders. */
			s.sg2 = cap2 - s.sg2;
			
			if (s.sg1 == 0){
				s = fillState(s.time+s.sg2,s.sg1,0);
				return s;
			}
			smallestNumberOfSeconds = smallestValue(s.sg1,s.sg2);

			s = fillState(s.time+smallestNumberOfSeconds, s.sg1- smallestNumberOfSeconds, s.sg2 - smallestNumberOfSeconds);
			return s;			

		case TURN_BOTH:
			/* This will turn both of the SandGlasses. In this case the "fill" will stop whenever we the smallest remainder reaches zero. */

			/* Check what happends if we turn both the SandGlasses.*/
			s.sg1 = cap1 - s.sg1;
			s.sg2 = cap2 - s.sg2;

			smallestNumberOfSeconds = smallestValue(s.sg1,s.sg2);

			s = fillState(s.time+smallestNumberOfSeconds, s.sg1- smallestNumberOfSeconds, s.sg2 - smallestNumberOfSeconds);

			return s;

			
	}
	/* Nothing happend to the current state. */
	printf("Nothing happend to the current state error\n");
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
		/* This is the starting state */
		State start = fillState(0,0,0);
		State reachedGoal;

		/* check for simplest cases */
 		/*if(cap1 == goalTime || cap2 == goalTime || goalTime == 0 || goalTime%cap1 == 0 || goalTime%cap2 == 0)
 		{
 			return 1;
 		}*/
 		/* We create an empty queue. */
 		Queue q = newEmptyQueue();

 		/* Enque start state */
 		enqueue(start, &q);

 		/* Met dat de Queue niet leeg is. */
 		while( !isEmptyQueue(q) ){
 			/* We dequeue the time that we are going to check. */
 			reachedGoal = dequeue(&q);
 			/* showState(reachedGoal) */;

 			if (reachedGoal.time == goalTime){
 				return 1;
 			} else if (reachedGoal.time < goalTime) {
 				/* We start the program */
 				if (reachedGoal.sg1 != 0 || reachedGoal.sg2 != 0){
 					enqueue(action(reachedGoal,1,cap1,cap2), &q); 
 				}
 				enqueue(action(reachedGoal,2,cap1,cap2), &q);
 				enqueue(action(reachedGoal,3,cap1,cap2), &q); 
 				enqueue(action(reachedGoal,4,cap1,cap2), &q);				
 			}

 		} 		
 	/* We have exceeded the time and not found a match */
 	return 0;

}

/* main performs a dialogue with the user. The user is asked to provide three numbers: 
 * the (positive) capacities of the sandglasses and the goal time (>= 0).
 * The program indicates whether the goal time can be determined exactly. 
 * The dialogue is ended by the input '0'.
 */

int main(int argc, char *argv[]){
		  int cap1, cap2, goalTime; 
		  /*printf("give the sandglass capacities and the goal time: ");*/
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