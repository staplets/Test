/* CS261- Assignment 3 - cirListDeque.c*/
/* Name: Shaun Stapleton
 * Date: 07/17/14
 * Solution description: Program will
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include "cirListDeque.h"

/* Double Link Structure */
struct DLink {
	TYPE value;/* value of the link */
	struct DLink * next;/* pointer to the next link */
	struct DLink * prev;/* pointer to the previous link */
};

# define TYPE_SENTINEL_VALUE DBL_MAX


/* ************************************************************************
 Deque ADT based on Circularly-Doubly-Linked List WITH Sentinel
 ************************************************************************ */

struct cirListDeque {
	int size;/* number of links in the deque */
	struct DLink *Sentinel;	/* pointer to the sentinel */
};
/* internal functions prototypes */
struct DLink* _createLink (TYPE val);
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v);
void _removeLink(struct cirListDeque *q, struct DLink *lnk);



/* ************************************************************************
	Deque Functions
************************************************************************ */

/* Initialize deque.

	param: 	q		pointer to the deque
	pre:	q is not null
	post:	q->Sentinel is allocated and q->size equals zero
*/
void _initCirListDeque (struct cirListDeque *q)     //Worked On
{
  	/* FIXME: you must write this */
    q->Sentinel = malloc(sizeof(struct DLink));

    assert(q->Sentinel != 0);

    q->Sentinel->next = q->Sentinel ->prev = q->Sentinel;

    q->size = 0;
}

/*
 create a new circular list deque

 */

struct cirListDeque *createCirListDeque()
{
	struct cirListDeque *newCL = malloc(sizeof(struct cirListDeque));
	_initCirListDeque(newCL);
	return(newCL);
}


/* Create a link for a value.

	param: 	val		the value to create a link for
	pre:	none
	post:	a link to store the value
*/
struct DLink * _createLink (TYPE val)
{
	/* FIXME: you must write this */
    //create link
    struct DLink *link = malloc(sizeof(struct DLink));

    assert(link != 0);

    //Assign value
    link->value = val;

    //return value
    return link;

	/*temporary return value..you may need to change it*/
	//return(0);

}


/* Check whether the deque is empty

	param: 	q		pointer to the deque
	pre:	q is not null
	ret: 	1 if the deque is empty. Otherwise, 0.
*/
int isEmptyCirListDeque(struct cirListDeque *q) {
  	/* FIXME: you must write this */
  	assert(q != 0);

  	if(q->size ==0)
    {
        return 1;
    }

    return 0;
}


/* Adds a link after another link

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the existing link in the deque
	param: 	v		value of the new link to be added after the existing link
	pre:	q is not null
	pre: 	lnk is not null
	pre:	lnk is in the deque
	post:	the new link is added into the deque after the existing link
*/
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v)
{
	/* FIXME: you must write this */
	struct DLink *after =	_createLink(v);

    //assign after's links
	after->next = lnk->next;
	after->prev = lnk;

    //assign lnk and the link after after.
	lnk->next = after;
	after->next->prev = after;

	q->size++;

}

/* Adds a link to the back of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the back of the deque
*/
void addBackCirListDeque (struct cirListDeque *q, TYPE val)
{
	/* FIXME: you must write this */
	assert(q != 0);

	_addLinkAfter(q, q->Sentinel->prev, val);

}

/* Adds a link to the front of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the front of the deque
*/
void addFrontCirListDeque(struct cirListDeque *q, TYPE val)
{
	/* FIXME: you must write this */
	assert(q != 0);

	_addLinkAfter(q, q->Sentinel, val);

}

/* Get the value of the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the front of the deque
*/
TYPE frontCirListDeque(struct cirListDeque *q)
{
	/* FIXME: you must write this */
	assert(q != 0);
	assert(!isEmptyCirListDeque(q));

	return q->Sentinel->next->value;

}

/* Get the value of the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the back of the deque
*/
TYPE backCirListDeque(struct cirListDeque *q)
{
	/* FIXME: you must write this */
	assert(q != 0);
	assert(!isEmptyCirListDeque(q));

	return q->Sentinel->prev->value;
}

/* Remove a link from the deque

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the link to be removed
	pre:	q is not null and q is not empty
	post:	the link is removed from the deque
*/
void _removeLink(struct cirListDeque *q, struct DLink *lnk)
{
	/* FIXME: you must write this */
	assert(q != 0);
	assert(!isEmptyCirListDeque(q));


	lnk->prev->next = lnk->next;

    lnk->next->prev = lnk->prev;

    free(lnk);

    q->size -= 1;

}

/* Remove the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the front is removed from the deque
*/
void removeFrontCirListDeque (struct cirListDeque *q) {
	/* FIXME: you must write this */
	assert(q != 0);
	assert(!isEmptyCirListDeque(q));

    //Remove link from front
	_removeLink(q, q->Sentinel->next);

}


/* Remove the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the back is removed from the deque
*/
void removeBackCirListDeque(struct cirListDeque *q)
{
  	/* FIXME: you must write this */
    assert(q != 0);
	assert(!isEmptyCirListDeque(q));

    //Remove link from front
	_removeLink(q, q->Sentinel->prev);
}

/* De-allocate all links of the deque

	param: 	q		pointer to the deque
	pre:	none
	post:	All links (including Sentinel) are de-allocated
*/
void freeCirListDeque(struct cirListDeque *q)
{
	/* FIXME: you must write this */
	//While list is not empty remove from front.
	while (q->size > 0)
    {
        removeFrontCirListDeque(q);
    }

    //Free sentinel
     free (q->Sentinel);

    //Set sentinel to null
     q->Sentinel = NULL;

}

/* Print the links in the deque from front to back

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the links in the deque are printed from front to back
*/
void printCirListDeque(struct cirListDeque *q)
{
	/* FIXME: you must write this */
	assert(q != 0);
	assert(!isEmptyCirListDeque(q));

    struct DLink *temp;

    temp = q->Sentinel->next;

    while(temp != q->Sentinel)
    {
        printf("Value is %f\n", temp->value);
        temp = temp->next;
    }
    printf("\n\n");

}

/* Reverse the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the deque is reversed
*/
void reverseCirListDeque(struct cirListDeque *q)
{
	/* FIXME: you must write this */
	assert(q != 0);
	assert(!isEmptyCirListDeque(q));

	struct DLink *temp, *current;

    //Assign current to last value.
	current = q->Sentinel->prev;

    //Run through list in reverse order to
    //redirect arrows.
	do
    {
        temp = current->next;
        current->next = current->prev;
        current->prev = temp;
        current = temp;

    }while(current != q->Sentinel->next);

	//q->Sentinel->next = q->Sentinel->prev;

	/*//This also works but creates extra deque.
	struct cirListDeque* tempList = createCirListDeque();
    while(!isEmptyCirListDeque(q)){
        addBackCirListDeque(tempList, backCirListDeque(q));
        removeBackCirListDeque(q);
    }
    q->Sentinel = tempList->Sentinel;
    q->size = tempList->size;
    free(tempList);
*/
}

