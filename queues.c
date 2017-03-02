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

typedef struct Queue { /* a queue is a list and a pointer to the last node */
		  List list;
		  List lastNode;
} Queue;

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
