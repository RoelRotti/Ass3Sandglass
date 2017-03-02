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

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TURN_NOTHING 1
#define TURN_A 2
#define TURN_B 3
#define TURN_BOTH 4


/* First the type definitions.
 */

typedef struct State { /* a state contains a time and the states of the two sandglasses */
		  int time;
		  int sg1, sg2;
} State;

typedef struct ListNode *List;  /* List is the type of lists of states */

struct ListNode {
		  State item;
		  List next;
};

typedef struct Queue { /* a queue is a list and a pointer to the last node */
		  List list;
		  List lastNode;
} Queue;

/* We use the functions on lists as defined in 1.3 of the lecture notes.
 */

List newEmptyList() {
		  return NULL;
}

int isEmptyList (List li) {
		  return ( li==NULL );
}

void listEmptyError() {    
		  printf("list empty\n");
		  abort();
}

List addItem(State s, List li) {
		  List newList = malloc(sizeof(struct ListNode));
		  assert(newList!=NULL);
		  newList->item = s;
		  newList->next = li;
		  return newList;
}

State firstItem(List li) {
		  if ( li == NULL ) {
		    listEmptyError();
		  }
		  return li->item;
}

List removeFirstNode(List li) {
		  List returnList;
		  if ( li == NULL ) {
		    listEmptyError();
		  }
		  returnList = li->next;
		  free(li);
		  return returnList;
}

void freeList(List li) {
		  List li1;
		  while ( li != NULL ) {
		    li1 = li->next;
		    free(li);
		    li = li1;
		  }
		  return;
}

/* We define some functions on queues, based on the definitions in 1.3.1 of the
 * lecture notes. Integers are replaced by states, and enqueue has output type void here.
 */

Queue newEmptyQueue () {
		  Queue q;
		  q.list = newEmptyList();
		  q.lastNode = NULL;
		  return q;
}

int isEmptyQueue (Queue q) {
		  return isEmptyList(q.list);
}

void emptyQueueError () {
		  printf("queue empty\n");
		  exit(0);
}

void enqueue (State s, Queue *qp) {
		  if ( isEmptyList(qp->list) ) {
		    qp->list = addItem(s,NULL);
		    qp->lastNode = qp->list;
		  } else {
		    (qp->lastNode)->next = addItem(s,NULL);
		    qp->lastNode = (qp->lastNode->next);
		  }
}

State dequeue(Queue *qp) {
		  State s = firstItem(qp->list);
		  qp->list = removeFirstNode(qp->list);
		  if ( isEmptyList(qp->list) )  {
		    qp->lastNode = NULL;
		  }
		  return s;
}

void freeQueue (Queue q) {
			freeList(q.list);
}

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
		  /* ... */
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
		int time = 0; 
		// check for simplest cases
 		if(cap1 == goalTime || cap2 == goalTime || goalTime == 0 || goalTime%cap1 == 0 || goalTime%cap2 == 0)
 		{
 			return 1;
 		}

 		// create empty queue
 		newEmptyQueue();

 		State start = {0,0,0};

 		enqueue(start, NULL);

 		// start checking all states
 		while(time <= goalTime)
 		{
 			enqueue(action(State s, TURN_NOTHING), q);

 			time++;
 		}



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