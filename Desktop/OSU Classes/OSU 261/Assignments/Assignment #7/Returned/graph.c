/* CS261- Assignment 7 - graph.c*/
/* Name: Shaun Stapleton
 * Date: 09/27/14
 * Solution description: File to create graphs with a depth first search and a breadth first search.
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#ifndef __TYPE_H
#define __TYPE_H



# ifndef TYPE
# define TYPE      Vertex*
# define TYPE_SIZE sizeof(Vertex*)
# endif

# ifndef LT
# define LT(A, B) ((A) < (B))
# endif

# ifndef EQ
# define EQ(A, B) ((A) == (B))
# endif

#endif


struct Vertex {
	char label;
	int isVisited; /* Use this boolean to remember where you have been */

	int numNeighbors;
	struct Vertex** neighbors; /* array of pointers to Vertex which are adjacent to THIS */
};
typedef struct Vertex Vertex;

struct Graph {
	int numEdges;
	int numVertices;
	Vertex* vertexSet; /* Array of Vertex which store the structure of the graph*/
};
typedef struct Graph Graph;

struct DLink {
  TYPE value;			/* value of the link */
  struct DLink * next;	/* pointer to the next link */
  struct DLink * prev;	/* pointer to the previous link */
};

/* Deque Structure based on Circularly-Doubly-Linked List */
struct cirListDeque {
  int size;				/* number of links in the deque */
  struct DLink *last; 	/* pointer to the last link */
};
typedef struct cirListDeque cirListDeque;

#ifndef GRAPH_DEFINED
#define GRAPH_DEFINED 1

void initCirListDeque(struct cirListDeque *q);

int isEmptyCirListDeque(struct cirListDeque *q);
void addBackCirListDeque(struct cirListDeque *q, TYPE val);
void addFrontCirListDeque(struct cirListDeque *q, TYPE val);
TYPE frontCirListDeque(struct cirListDeque *q);
TYPE backCirListDeque(struct cirListDeque *q);
void removeFrontCirListDeque(struct cirListDeque *q);
void removeBackCirListDeque(struct cirListDeque *q);
void removeAllCirListDeque(struct cirListDeque *q);

void printCirListDeque(struct cirListDeque *q);

#endif



/* some functions to create various graphs for testing */
void createGraph1(Graph* g);
void createGraph2(Graph* g);
void createGraph3(Graph* g);
void createGraph4(Graph* g);
void createGraph5(Graph* g);

/* utilities to construct and view graphs */
void setupVertices(Graph* g);
void setupEdge(Graph *g, Vertex* first, Vertex* second);
void printGraph(Graph* g);

/* utilities to help analyze graph structure*/
int isAdjacent(Vertex* firstVert, Vertex* secondVert);

/* search related functions */
void clearVisited(Graph* g);
int DFS(Graph* g, Vertex* source, Vertex* destination);
int DFSRecursive(Graph* g, Vertex* source, Vertex* destination);
int BFS(Graph* g, Vertex* source, Vertex* destination);




#include <assert.h>
void initCirListDeque (struct cirListDeque *q)
{
	q->size = 0;
	q->last = 0;
}

/* Create a link for a value.

	param: 	val		the value to create a link for
	pre:	none
	post:	a link to store the value
*/
struct DLink * _createLink (TYPE val)
{
	/* allocate memory for the new link */
	struct DLink * lnk = (struct DLink *) malloc(sizeof(struct DLink));
   	assert(lnk != 0);

	lnk->value = val;
	return lnk;
}

/* Adds a link after another link

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the existing link in the deque
	param: 	newLnk	pointer to the new link to add after the existing link
	pre:	q is not null and q is not empty
	pre: 	lnk and newLnk are not null
	pre:	lnk is in the deque
	post:	the new link is added into the deque after the existing link
*/
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, struct DLink *newLnk)
{
	assert(!isEmptyCirListDeque(q));

	/* re-allocate pointers */
  	newLnk->next = lnk->next;
	newLnk->prev = lnk;
	lnk->next->prev = newLnk;
	lnk->next = newLnk;

	/* increase the size of the deque */
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
	/* create a link for the value */
	struct DLink * lnk = _createLink(val);
  	if (isEmptyCirListDeque(q))
	{
		/* if q is currently empty, the added link becomes the only link in the deque */
	  	lnk->next = lnk;
		lnk->prev = lnk;
		q->size++;
	}
	else
	  	_addLinkAfter(q, q->last, lnk);

	/* change last to the newly added link */
	q->last = lnk;
}

/* Adds a link to the front of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the front of the deque
*/
void addFrontCirListDeque(struct cirListDeque *q, TYPE val)
{
	struct DLink * lnk = _createLink(val);
	if (isEmptyCirListDeque(q))
	{
		/* if q is currently empty, the added link becomes the only link in the deque */
	  	lnk->next = lnk;
		lnk->prev = lnk;
		q->size++;
		/* change last to the newly added link */
		q->last = lnk;
	}
	else
		_addLinkAfter(q, q->last, lnk);
}

/* Get the value of the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the front of the deque
*/
TYPE frontCirListDeque (struct cirListDeque *q)
{
   assert(!isEmptyCirListDeque(q));
   return q->last->next->value;
}

/* Get the value of the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the back of the deque
*/
TYPE backCirListDeque(struct cirListDeque *q)
{
	assert(!isEmptyCirListDeque(q));
	return q->last->value;
}

/* Remove a link from the deque

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the link to be removed
	pre:	q is not null and q is not empty
	pre:	lnk is in the deque
	post:	the link is removed from the deque
*/
void _removeLink(struct cirListDeque *q, struct DLink *lnk)
{
	assert(!isEmptyCirListDeque(q));
  	if (EQ(lnk, lnk->next))
	{
		/* if lnk is the only link in the deque, set last to null */
	  	q->last = 0;
	}
	else
	{
		lnk->next->prev = lnk->prev;
		lnk->prev->next = lnk->next;
		/* if lnk is the last link, change last to the previous of lnk */
		if (EQ(lnk, q->last))
			q->last = lnk->prev;
	}

	free(lnk);
	q->size--;
}

/* Remove the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the front is removed from the deque
*/
void removeFrontCirListDeque (struct cirListDeque *q) {
   assert(!isEmptyCirListDeque(q));
   _removeLink(q, q->last->next);
}


/* Remove the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the back is removed from the deque
*/
void removeBackCirListDeque(struct cirListDeque *q)
{
	assert(!isEmptyCirListDeque(q));
	_removeLink(q, q->last);
}

/* Remove all links of the deque

	param: 	q		pointer to the deque
	pre:	q is not null
	post:	q is empty
*/
void removeAllCirListDeque(struct cirListDeque *q)
{
	while(!isEmptyCirListDeque(q))
		removeBackCirListDeque(q);
}

/* Check whether the deque is empty

	param: 	q		pointer to the deque
	pre:	q is not null
	ret: 	1 if the deque is empty. Otherwise, 0.
*/
int isEmptyCirListDeque(struct cirListDeque *q) {
	return EQ(q->size, 0);
}

/* Print the links in the deque from front to back

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the links in the deque are printed from front to back
*/
void printCirListDeque(struct cirListDeque *q)
{
	struct DLink *lnk;
	assert(!isEmptyCirListDeque(q));
	lnk = q->last->next;
	do
	{
		printf("%f\n", lnk->value);
		lnk = lnk->next;
	}
	while(!EQ(lnk, q->last->next));

	printf("+++++++++++\n");
}


void createGraph1(Graph* g)
{
	Vertex* firstVert;
	Vertex* secondVert;
	int i;
	srand(3);

	g->numVertices = 3;
	setupVertices(g);

	g->numEdges = 3;
	for(i = 0; i < g->numEdges; ++i)
	{
		firstVert = &g->vertexSet[i];
		secondVert = &g->vertexSet[(i+1) % g->numVertices];
		setupEdge(g, firstVert, secondVert);
	}
}

void createGraph2(Graph* g)
{
	Vertex* firstVert;
	Vertex* secondVert;
	int i;
	srand(57);

	g->numVertices = 8;
	setupVertices(g);

	g->numEdges = 10;
	for(i = 0; i < g->numEdges; ++i)
	{
		firstVert = &g->vertexSet[rand() % g->numVertices];
		secondVert = firstVert;
		while(firstVert == secondVert || isAdjacent(firstVert, secondVert))
			secondVert = &g->vertexSet[rand() % g->numVertices];

		setupEdge(g, firstVert, secondVert);
	}
}

void createGraph3(Graph* g)
{
	Vertex* firstVert;
	Vertex* secondVert;
	int i;
	srand(33);

	g->numVertices = 26;
	setupVertices(g);

	g->numEdges = 10;
	for(i = 0; i < g->numEdges; ++i)
	{
		firstVert = &g->vertexSet[rand() % g->numVertices];
		secondVert = firstVert;
		while(firstVert == secondVert || isAdjacent(firstVert, secondVert))
			secondVert = &g->vertexSet[rand() % g->numVertices];

		setupEdge(g, firstVert, secondVert);
	}
}

void createGraph4(Graph* g)
{
	Vertex* firstVert;
	Vertex* secondVert;
	int i;
	srand(9875);

	g->numVertices = 26;
	setupVertices(g);

	g->numEdges = 100;
	for(i = 0; i < g->numEdges; ++i)
	{
		firstVert = &g->vertexSet[rand() % g->numVertices];
		secondVert = firstVert;
		while(firstVert == secondVert || isAdjacent(firstVert, secondVert))
			secondVert = &g->vertexSet[rand() % g->numVertices];

		setupEdge(g, firstVert, secondVert);
	}
}

void createGraph5(Graph* g)
{
	int i, j;
	srand(9875);

	g->numVertices = 20;
	setupVertices(g);

	g->numEdges = 400;
	for(i = 0; i < g->numVertices; ++i)
		for(j = i + 1; j < g->numVertices; ++j)
			setupEdge(g, &g->vertexSet[i], &g->vertexSet[j]);
}

/* Initializes all information for the vertices in the graph
 * param: g		Graph whose vertices will be initialized
 * pre: numVertices has been initialized
 */
void setupVertices(Graph* g)
{
	int i;
	g->vertexSet = (Vertex*) malloc(g->numVertices * sizeof(Vertex));
	for(i = 0; i < g->numVertices; ++i)
	{
		g->vertexSet[i].label = 'A' + i;
		g->vertexSet[i].isVisited = 0;
		g->vertexSet[i].neighbors = (Vertex**)malloc(sizeof(Vertex*));
		g->vertexSet[i].numNeighbors = 0;
	}
}

/* Creates all the links necessary to form an edge between the two argument vertices.
 * param: g		Graph in which the vertices reside
 * param: first	Vertex from which the edge will originate
 * param: second	Vertex at which the edge terminates
 * post: all links necessary to form an edge between first and second have been completed.
 */
void setupEdge(Graph* g, Vertex* first, Vertex* second)
{
	first->numNeighbors++;
	second->numNeighbors++;
	first->neighbors = (Vertex**)realloc(first->neighbors, first->numNeighbors * sizeof(Vertex*));
	second->neighbors = (Vertex**)realloc(second->neighbors, second->numNeighbors * sizeof(Vertex*));

	first->neighbors[first->numNeighbors - 1] = second;
	second->neighbors[second->numNeighbors - 1] = first;
}

/* This function prints the graph
 * param: g		Graph to print
 */
void printGraph(Graph* g)
{
	int i, j;
	Vertex* currVert;
	printf("*****\t\t This graph has %d Vertices and %d Edges\n", g->numVertices, g->numEdges);

	/* print the vertex set */
	for(i = 0; i < g->numVertices; ++i)
	{
		currVert = &g->vertexSet[i];
		printf("%c: ", currVert->label);
		for(j = 0; j < currVert->numNeighbors - 1; ++j)
			printf("%c, ", currVert->neighbors[j]->label);
		if(currVert->numNeighbors > 0)
			printf("%c\n", currVert->neighbors[j]->label);
		else printf("\n");
	}
}

/* This function can be used to determine if two vertices are adjacent
 * param: firstVert		Vertex to check neighbors from
 * param: secondVert	Vertex to check neighbors to
 * ret:	boolean (encoded as int) indicating whether or not the vertices
 *		are adjacent (an edge exists between them)
 */
int isAdjacent(Vertex* firstVert, Vertex* secondVert)
{
	int i;
	for(i = 0; i < firstVert->numNeighbors; ++i)
		if(	firstVert->neighbors[i] == secondVert)
			return 1;
	return 0;
}

/* This function clears all the search flags in the graph
 * param: g		Graph to have its flags cleared
 * post: All vertices in the graph should have their search flags turned off
 */
void clearVisited(Graph* g)
{
	int i;
	for(i = 0; i < g->numVertices; ++i)
		g->vertexSet[i].isVisited = 0;
}

/* these two functions provide a recursive version of the depth first search.
 * feel free to use this to check your answers
 * param: g			Graph to perform the search in
 * param: source	Vertex to originate the search from
 * param: destination Vertex to stop the search from (if it is found)
 * ret: boolean indicating whether or not a path exists
 */
int DFSRecursiveHelper(Graph* g, Vertex* currVert, Vertex* destination)
{
	int i;

	currVert->isVisited = 1;
	if(currVert == destination)
		return 1;
	for(i = 0; i < currVert->numNeighbors; ++i)
		if(!currVert->neighbors[i]->isVisited)
			if(DFSRecursiveHelper(g, currVert->neighbors[i], destination))
				return 1;
	return 0;
}
int DFSRecursive(Graph* g, Vertex* source, Vertex* destination)
{
	clearVisited(g);
	return DFSRecursiveHelper(g, source, destination);
}

/* This function should return a boolean (encoded as an int) indicating
 * whether or not a path exists between the argument vertices.
 * param: g			Graph to perform the search in
 * param: source	Vertex to originate the search from
 * param: destination Vertex to stop the search from (if it is found)
 * ret: boolean indicating whether or not a path exists
 */
int DFS(Graph* g, Vertex* source, Vertex* destination)
{
     int i;
    cirListDeque *stackSearch;
     /*struct cirListDeque *reachable;*/
     /*initialize        //Worked on */   /* FIXME you will write this */
    clearVisited(g);

    //initCirListDeque(stackSearch);
    /*initCirListDeque(reachable);*/

    /*list source as visited*/
    source->isVisited = 1;
    /*add source to stack*/
    addFrontCirListDeque(stackSearch, source);

    /*while stack is not empty*/
    while(!isEmptyCirListDeque(stackSearch))
    {
        struct Vertex *reached;
        /*get value from front of stack*/
        reached = frontCirListDeque(stackSearch);
        /*Remove value from front of stack*/
        removeFrontCirListDeque(stackSearch);

        if(!reached->isVisited)
        {
         /*add to reachable*/
       /*  addBackCirListDeque (reachable, reached);*/
        /*list source as visited*/
        reached->isVisited = 1;

        if(reached == destination)
        {
           /* removeAllCirListDeque(reachable);*/
            removeAllCirListDeque(stackSearch);
            return 1;
        }

         for(i = 0; i < source->numNeighbors; ++i)
         {
             /*see if neighbor has been visited*/
            if(!reached->neighbors[i]->isVisited)
            {       /*see if neighbor is adjacent*/
                if(isAdjacent(reached, reached->neighbors[i]))
                {
                    /*add source to stack*/
                    addFrontCirListDeque(stackSearch, reached->neighbors[i]);
                }

            }
         }
        }
    }
    /*removeAllCirListDeque(reachable);*/
    removeAllCirListDeque(stackSearch);
	return 0;
}

/* This function should return a boolean (encoded as an int) indicating
 * whether or not a path exists between the argument vertices.
 * param: g			Graph to perform the search in
 * param: source	Vertex to originate the search from
 * param: destination Vertex to stop the search from (if it is found)
 * ret: boolean indicating whether or not a path exists
 */
int BFS(Graph* g, Vertex* source, Vertex* destination)
{
                                                                                                /* FIXME you will write this */
    clearVisited(g);



	return 0;
}






int main ()
{
	/* change this number to generate different graphs */
	int graphTestNumber = 3; /* permissible values are 1-5 */
	/* switch this to 0 to use BFS */
	int useDFS = 1;

	int i, j;
	Graph g;

	/* set up the graph */
	if(graphTestNumber == 1)
		createGraph1(&g);
	else if(graphTestNumber == 2)
		createGraph2(&g);
	else if(graphTestNumber == 3)
		createGraph3(&g);
	else if(graphTestNumber == 4)
		createGraph4(&g);
	else if(graphTestNumber == 5)
		createGraph5(&g);
	else
	{
		printf("Invalid test number... Quitting");
		return 1;
	}
	printGraph(&g);

	if(useDFS)
		printf("\nComputing reachability using DFS\n");
	else
		printf("\nComputing reachability using BFS\n");

	for(i = 0; i < g.numVertices; ++i)
		for(j = i+1; j < g.numVertices; ++j)
		{
			printf("%c to %c\t\t\t", g.vertexSet[i].label, g.vertexSet[j].label);
			if(useDFS)
				if(DFS(&g, &g.vertexSet[i], &g.vertexSet[j]))
					printf("reachable!\n");
				else
					printf("***UNREACHABLE***\n");
			else
				if(BFS(&g, &g.vertexSet[i], &g.vertexSet[j]))
					printf("reachable!\n");
				else
					printf("***UNREACHABLE***\n");
		}

	return 0;
}
