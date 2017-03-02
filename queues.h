/* file: queues.h                                 		*/
/* author: 	A.M van Maurik (email: mathew9753@gmail.com) 	*/
/*			Roel Rotteveel									*/
/* date: 1-03-2017                                     		*/
/* version:                                        			*/
/* Description: 											*/


/* 3. Create a file queues.h and put all type definitions from the 
 * file queues.c in it. Add the type definitions of the functions 
 * in queues.c. Do not forget the inclusion guard around the header.
 */

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