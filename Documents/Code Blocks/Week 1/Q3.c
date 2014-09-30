
void _dequeSetCapacity (struct deque *d, int newCap) {
	int i;

	/* Create a new underlying array*/
	TYPE *newData = (TYPE*)malloc(sizeof(TYPE)*newCap);
	assert(newData != 0);

	/* copy elements to it */
	int j = d->beg;
	for(i = 0; i <  d->size; i++)
	{
		newData[i] = d->data[j];
		j = j + 1;
		if(j >= d->capacity)
			j = 0;
	}

	/* Delete the oldunderlying array*/
	free(d->data);
	/* update capacity and size and data*/
	d->data = newData;
	d->capacity = newCap;
	d->beg = 0;
}

void dequeFree (struct deque *d) {
   free(d->data); d->size = 0; d->capacity = 0;
}struct deque {
   TYPE * data;
   int capacity;
   int size;
   int start;
};

void dequeInit (struct deque *d, int initCapacity) {
   d->size = d->beg = 0;
   d->capacity = initCapacity; assert(initCapacity > 0);
   d->data = (TYPE *) malloc(initCapacity * sizeof(TYPE));
   assert(d->data != 0);
}

int dequeSize (struct deque *d) { return d->size; }


void dequeAddFront (struct deque *d, TYPE newValue) {
   if (d->size >= d->capacity) _dequeSetCapacity(d, 2*d->capacity);

	if(d->beg == 0)
	{
		d->beg = capacity;
	}
else
d->beg --;
	d->size++;
	d->data[d->beg] = newValue;

	//-Shaun
}

void dequeAddBack (struct deque *d, TYPE newValue) {
   if (d->size >= d->capacity) _dequeSetcapacity(d, 2* d->capacity);

int index;

	index = d->beg + d->size;
	if(index >= d->capacity)
	{
		index -=d->capacity
	}

	d->data[index] = newValue;
	d->size++;

	//-Shaun

}


TYPE dequeFront (struct deque *d) {



return d->data[d->beg];

//-Shaun
}

TYPE dequeBack (struct deque *d) {

	int index = d->beg + d->size - 1;
	if (index > d-> capacity)
	{
		index -= d-> capacity;
	}
	return d-> data [index];


//-Shaun

}



void dequeRemoveFront (struct deque *d) {


assert(d-> size > 0);
d-> beg++;
d->size--;

	//-Shaun

}

void dequeRemoveBack (struct deque *d) {


assert(d-> size > 0);
d-> size--;

	//-Shaun
}
