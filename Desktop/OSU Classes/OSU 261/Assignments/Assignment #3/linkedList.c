/* CS261- Assignment 3 - linkedlist.c*/
/* Name: Shaun Stapleton
 * Date: 07/16/14
 * Solution description: Program will take a command line integer
 * for the number of elements in a bag and print out the memory used
 * then calls the contains function and outputs the time taken by it.
 */


#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


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
