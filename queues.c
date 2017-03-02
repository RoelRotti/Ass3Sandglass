/* file: queues.c                                 		*/
/* author: 	A.M van Maurik (email: mathew9753@gmail.com) 	*/
/*			Roel Rotteveel									*/
/* date: 1-03-2017                                     		*/
/* version:                                        			*/
/* Description: 											*/

/* 2. First we split this file in several files: queues.c for
 * all functions related to the queue and sandglasses.c for 
 * the other functions.
 */

/* 3. Create a file queues.h and put all type definitions from the 
 * file queues.c in it. Add the type definitions of the functions 
 * in queues.c. Do not forget the inclusion guard around the header.
 */

/* 4. Add include-statements in queues.c and sandglasses.c, 
 * so that you will be able to compile your program with 
 * gcc -ansi -Wall *.c
*/ 
#include gcc -ansi -Wall *.c

/* Add the type definitions of the functions 
 * in queues.c. Do not forget the inclusion guard around the header.
 */
#include inclusion guard

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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
