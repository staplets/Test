/* testLinkedList.c
 * This file is used for testing Linked List.
 */
//#include "linkedList.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>


# ifndef TYPE
# define TYPE      int
# define TYPE_SIZE sizeof(int)
# endif
# ifndef LT
# define LT(A, B) ((A) < (B))
# endif

# ifndef EQ
# define EQ(A, B) ((A) == (B))
# endif




/* 	VISUAL STUDIO (VS) USERS: COMMENT OUT THE LINE BELOW
	TO EXCLUDE THE MEMORY TEST CODE.
*/
//***  CHECK BACK  #define MEMORY_TEST_INCLUDED

#ifdef MEMORY_TEST_INCLUDED
/* This header is needed for memory usage calculation. */
#include <sys/resource.h>

# ifndef TYPE
# define TYPE      int
# define TYPE_SIZE sizeof(int)
# endif
# ifndef LT
# define LT(A, B) ((A) < (B))
# endif

# ifndef EQ
# define EQ(A, B) ((A) == (B))
# endif


/* Function to get current memory usage in KB (Max Resident Set Size) */
long getMemoryUsage() {
	int who = RUSAGE_SELF;
	struct rusage usage;
	int ret;
	ret = getrusage(who, &usage);
	return usage.ru_maxrss;
}
#endif


/* Double Link*/
struct DLink {
	TYPE value;
	struct DLink *next;
	struct DLink *prev;
};

/* Double Linked List with Head and Tail Sentinels  */

struct linkedList{
	int size;
	struct DLink *firstLink;
	struct DLink *lastLink;
};

/*
	initList
	param lst the linkedList
	pre: lst is not null
	post: lst size is 0
*/

void _initList (struct linkedList *lst) {
  /* FIXME: you must write this */              // --- Worked on
    //assert check
	assert(lst!= 0);

   lst->firstLink = malloc(sizeof(struct DLink));
   assert(lst->firstLink != 0);
   lst->lastLink = malloc(sizeof(struct DLink));
   assert(lst->lastLink);
   lst->firstLink->next = lst->lastLink;
   lst->lastLink->prev = lst->firstLink;
   lst->size = 0;
}

/*
 createList
 param: none
 pre: none
 post: firstLink and lastLink reference sentinels
 */

struct linkedList *createLinkedList()
{
	struct linkedList *newList = malloc(sizeof(struct linkedList));
	_initList(newList);
	return(newList);
}

/*
	_addLinkBeforeBefore
	param: lst the linkedList
	param: l the  link to add before
	param: v the value to add
	pre: lst is not null
	pre: l is not null
	post: lst is not empty
*/

/* Adds Before the provided link, l */

void _addLinkBefore(struct linkedList *lst, struct DLink *lnk, TYPE v)
{
	/* FIXME: you must write this */                                //Worked On
	struct DLink * newLink = malloc(sizeof(struct DLink));

    newLink->value = v;
    newLink->next = lnk;
    newLink->prev = lnk->prev;

    lnk->prev->next = newLink;
    lnk->prev = newLink;

    lst->size += 1;

}


/*
	addFrontList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/

void addFrontList(struct linkedList *lst, TYPE e)
{

	/* FIXME: you must write this */                    //Worked On
	assert(lst != 0); //Not null

    //Call to add link before front sentinel
	_addLinkBefore(lst, lst->firstLink->next, e);

}

/*
	addBackList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/

void addBackList(struct linkedList *lst, TYPE e) {

	/* FIXME: you must write this */                //Worked On
	assert(lst != 0); //Not null

    //Call to add link before back sentinel
	_addLinkBefore(lst, lst->lastLink, e);


}

/*
	frontList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: none
*/

TYPE frontList (struct linkedList *lst) {
	/* FIXME: you must write this */
	/*temporary return value...you may need to change this */ ////Worked On
	return lst->firstLink->next->value;
}

/*
	backList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: lst is not empty
*/

TYPE backList(struct linkedList *lst)
{
	/* FIXME: you must write this */
	/*temporary return value...you may need to change this */ //Worked On
	return lst->lastLink->prev->value;
}

/*
	_removeLink
	param: lst the linkedList
	param: l the linke to be removed
	pre: lst is not null
	pre: lnk is not null
	post: lst size is reduced by 1
*/

void _removeLink(struct linkedList *lst, struct DLink *lnk)
{

	/* FIXME: you must write this */        //Worked On
	assert(lst != 0); //Not null

	lnk->prev->next = lnk->next;
    lnk->next->prev = lnk->prev;
    free(lnk);

    lst->size -= 1;

}

/*
	removeFrontList
	param: lst the linkedList
	pre:lst is not null
	pre: lst is not empty
	post: size is reduced by 1
*/

void removeFrontList(struct linkedList *lst) {
   	/* FIXME: you must write this */        //Worked On
    assert(lst != 0); //Not null

    //call to remove link after front sentinel
   _removeLink (lst, lst->firstLink->next);

}

/*
	removeBackList
	param: lst the linkedList
	pre: lst is not null
	pre:lst is not empty
	post: size reduced by 1
*/

void removeBackList(struct linkedList *lst)
{
	/* FIXME: you must write this */        //Worked On
	assert(lst != 0); //Not null

	 //call to remove link after front sentinel
   _removeLink (lst, lst->lastLink->prev);

}

/*
	isEmptyList
	param: lst the linkedList
	pre: lst is not null
	post: none
*/

int isEmptyList(struct linkedList *lst) {
 	/* FIXME: you must write this */
	/*temporary return value...you may need to change this */       //Worked On

     return lst->size == 0;

   /* if(lst->firstLink->next == NULL)
    {

        return 1;
    }

     return 0;*/

}


/* Function to print list
 Pre: lst is not null
 */
void _printList(struct linkedList* lst)
{
	/* FIXME: you must write this */
	assert(! isEmptyList(lst));

	struct DLink *current;

    current = lst->firstLink->next; /*Initialize current*/

    while(current != lst->lastLink)
        {

        printf(" %p ", current);

        current = current->next;

        }

}

/*
	Add an item to the bag
	param: 	lst		pointer to the bag
	param: 	v		value to be added
	pre:	lst is not null
	post:	a link storing val is added to the bag
 */
void addList(struct linkedList *lst, TYPE v)
{
	/* FIXME: you must write this */
	assert(lst != 0); //Not null

    //Call to add link before front sentinel
	_addLinkBefore(lst, lst->firstLink->next, v);

}

/*	Returns boolean (encoded as an int) demonstrating whether or not
	the specified value is in the collection
	true = 1
	false = 0

	param:	lst		pointer to the bag
	param:	e		the value to look for in the bag
	pre:	lst is not null
	pre:	lst is not empty
	post:	no changes to the bag
*/
int containsList (struct linkedList *lst, TYPE e) {
	/* FIXME: you must write this */
	/*temporary return value...you may need to change this */
	struct DLink *current;

    assert(lst != 0); //Not null

    assert(!isEmptyList(lst)); //Not empty .. Looks redundant but saw it in the demo?

    current = lst->firstLink->next; /*Initialize current*/

    while(current != lst->lastLink)
        {
            if(EQ(current->value, e))
            {
                return 1;
            }

        current = current->next;

        }

    return 0;

}

/*	Removes the first occurrence of the specified value from the collection
	if it occurs

	param:	lst		pointer to the bag
	param:	e		the value to be removed from the bag
	pre:	lst is not null
	pre:	lst is not empty
	post:	e has been removed
	post:	size of the bag is reduced by 1
*/
void removeList (struct linkedList *lst, TYPE e) {
	/* FIXME: you must write this */
    assert(lst != 0); //Not null
    assert(!isEmptyList(lst)); //Not empty .. Looks redundant but saw it in the demo?

    struct DLink *current;

    current = lst->firstLink->next; /*Initialize current*/

    while(current != lst->lastLink)
        {
            if(EQ(current->value, e))
            {
                _removeLink(lst, current);
                break; //Only remove one copy
            }

        current = current->next;

       }
}


/*Function to get number of milliseconds elapsed since program started execution*/
double getMilliseconds() {
   return 1000.0 * clock() / CLOCKS_PER_SEC;
}

int main(int argc, char* argv[]){
	struct linkedList* b;
	int n, i;
	double t1, t2;

	#ifdef MEMORY_TEST_INCLUDED
	/* variables to hold memory used before and after creating LinkedList */
	long m1, m2;
	/* memory used BEFORE creating LinkedList */
	m1 = getMemoryUsage();
	#endif

	if( argc != 2 ) return 0;

	b = createLinkedList();
	n = atoi(argv[1]);/*number of elements to add*/
	for( i = 0 ; i < n; i++) {
		addList(b, (TYPE)i);/*Add elements*/
	}

	#ifdef MEMORY_TEST_INCLUDED
	/* memory used AFTER creating LinkedList */
	m2 = getMemoryUsage();
	printf("Memory used by LinkedList: %ld KB \n", m2-m1);
	#endif

	t1 = getMilliseconds();/*Time before contains()*/

	for(i=0; i<n; i++) {
		containsList(b, i);
	}

	t2 = getMilliseconds();/*Time after contains()*/
	printf("Time for running contains() on %d elements: %g ms\n", n, t2-t1);

	/* delete the linked list */
	//deleteLinkedList(b);

	return 0;
}
