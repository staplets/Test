/* CS261- Assignment 6 - hashMap.c*/
/* Name: Shaun Stapleton
 * Date: 08/18/14
 * Solution description: File holds the implementation of the hash map functions.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hashMap.h"



/*the first hashing function you can use*/
int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

/*the second hashing function you can use*/
int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between stringHash1 and stringHash2 is on this line*/
	return r;
}

/* initialize the supplied hashMap struct*/
void _initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

/* allocate memory and initialize a hash map*/
hashMap *createMap(int tableSize) {
	assert(tableSize > 0);
	hashMap *ht;
	ht = malloc(sizeof(hashMap));
	assert(ht != 0);
	_initMap(ht, tableSize);
	return ht;
}

/*
 Free all memory used by the buckets.
 Note: Before freeing up a hashLink, free the memory occupied by key and value
 */
void _freeMap (struct hashMap * ht)
{
                                                                                                                        //Worked On    /*write this*/

    int i;
    //free up memory in table
    for(i = 0; i < ht->tableSize; i++)
    {
	hashLink *freedom = ht->table[i];

        while(freedom !=NULL)
        {
           //free(freedom->key);
	 
            //free(freedom->value);
       
	    free(freedom);
            freedom = freedom->next;
        }
    }
}

/* Deallocate buckets and the hash map.*/
void deleteMap(hashMap *ht) {
	assert(ht!= 0);
	/* Free all memory used by the buckets */
	_freeMap(ht);
	/* free the hashMap struct */
	free(ht);
}

/*
Resizes the hash table to be the size newTableSize
*/
void _setTableSize(struct hashMap *ht, int newTableSize)
{
                                                                                                        //Worked On /*write this*/
    struct hashMap *newHashMap = createMap(newTableSize);


    int i = 0;
    //fill temp table with values
    for(i= 0; i< ht->tableSize; i++)
    {

        hashLink *temp = ht->table[i];

        while(temp != NULL)
        {
         
            insertMap(newHashMap,temp->key,temp->value);
 	
           temp = temp->next;

        }

    }
 	      
    //free old table
    _freeMap(ht);

    //assign new values back to ht
     ht->table = newHashMap->table;
     ht->tableSize = newHashMap->tableSize;
     ht->count = newHashMap->count; 	
 
}

/*
 insert the following values into a hashLink, you must create this hashLink but
 only after you confirm that this key does not already exist in the table. For example, you
 cannot have two hashLinks for the word "taco".

 if a hashLink already exists in the table for the key provided you should
 replace that hashLink--this requires freeing up the old memory pointed by hashLink->value
 and then pointing hashLink->value to value v.

 also, you must monitor the load factor and resize when the load factor is greater than
 or equal LOAD_FACTOR_THRESHOLD (defined in hashMap.h).
 */
void insertMap (struct hashMap *ht, KeyType k, ValueType v)
{
                                                                                                                //Worked On/*write this*/
    int idx = 0;
 


	if(HASHING_FUNCTION == 1) //if hashing function equals one, use stringHash1
    {
        idx = stringHash1(k) % ht->tableSize;
        if(idx < 0)
        {
            idx += ht->tableSize;
        }
    }
    else if(HASHING_FUNCTION ==2) //if hashing function equals two, use stringHash2
    {
        idx = stringHash2(k) % ht->tableSize;
        if(idx < 0)
        {
            idx += ht->tableSize;
        }
    }

    hashLink *newLink = (struct hashLink *) malloc(sizeof(struct hashLink));
    assert(newLink);

   if(ht->table[idx] == NULL)
   {
       newLink->value = v;
       newLink->key = k;	
       newLink->next = NULL;
       ht->table[idx] = newLink; 
       ht->count++;
   }
   else
   {
   

    hashLink *newHash = ht->table[idx];
       while(newHash->next != NULL && (strcmp(newHash->key, k) != 0))

       {
           newHash = newHash->next;
       }
       if(strcmp(newHash->key, k) == 0)
       {
           newHash->value += v;
       }
       else
       {
           newLink->value = v;
	   newLink->key = k;
           newLink->next = NULL;
           newHash->next = newLink;
           ht->count++;
       }
   }
    //if table load is larger than load factor resize
    if(tableLoad(ht) > LOAD_FACTOR_THRESHOLD)
    {
        _setTableSize(ht,(ht->tableSize *2) );
    }

}

/*
 this returns the value  stored in a hashLink specified by the key k.

 if the user supplies the key "taco" you should find taco in the hashTable, then
 return the value member of the hashLink that represents taco.

 if the supplied key is not in the hashtable return NULL.
 */
ValueType* atMap (struct hashMap * ht, KeyType k)
{
                                                                                                        //Worked On /*write this*/
   
    int idx = 0;

    if(HASHING_FUNCTION == 1) //if hashing function equals one, use stringHash1
    {
        idx = stringHash1(k) % ht->tableSize;
        if(idx < 0)
        {
            idx += ht->tableSize;
        }
    }
    else if(HASHING_FUNCTION ==2) //if hashing function equals two, use stringHash2
    {
        idx = stringHash2(k) % ht->tableSize;
        if(idx < 0)
        {
            idx += ht->tableSize;
        }
    }
    //Look for value and return if found
    hashLink *find = ht->table[idx];

   // while(find->next != NULL && find->key != k)
    while(find->next != NULL &&(strcmp(find->key, k) != 0))
    {
        find = find->next;
    }
    if(strcmp(find->key, k) == 0 )
    {
        return &find->value;
    }
    else
     {
         return NULL;
     }


}

/*
 a simple yes/no if the key is in the hashtable.
 0 is no, all other values are yes.
 */
int containsKey (struct hashMap * ht, KeyType k)
{
                                                                                                                    //Worked on /*write this*/
    
    int idx = 0;

    if(HASHING_FUNCTION == 1) //if hashing function equals one, use stringHash1
    {
        idx = stringHash1(k) % ht->tableSize;
        if(idx < 0)
        {
            idx += ht->tableSize;
        }
    }
    else if(HASHING_FUNCTION ==2) //if hashing function equals two, use stringHash2
    {
        idx = stringHash2(k) % ht->tableSize;
        if(idx < 0)
        {
            idx += ht->tableSize;
        }
    }

    hashLink *find = ht->table[idx];

    while(find->next != NULL &&(strcmp(find->key, k)== 0))
    {
        find = find->next;
    }
    if(strcmp(find->key, k)== 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*
 find the hashlink for the supplied key and remove it, also freeing the memory
 for that hashlink. it is not an error to be unable to find the hashlink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program.
 */
void removeKey (struct hashMap * ht, KeyType k)
{
                                                                                                               //Worked On /*write this*/
   
    int idx = 0;

    if(HASHING_FUNCTION == 1) //if hashing function equals one, use stringHash1
    {
        idx = stringHash1(k) % ht->tableSize;
        if(idx < 0)
        {
            idx += ht->tableSize;
        }
    }
    else if(HASHING_FUNCTION ==2) //if hashing function equals two, use stringHash2
    {
        idx = stringHash2(k) % ht->tableSize;
        if(idx < 0)
        {
            idx += ht->tableSize;
        }
    }
	//creat a previous and current pointer	
	hashLink *previous = NULL;
	hashLink *current = ht->table[idx];
	//while talbe is not NULL cycle through
	if(ht->table[idx] != NULL)
	{
		while(current->next != NULL && (strcmp(current->key, k) != 0))
		{
			previous = current;
			current = current->next;
		}
	} //if key equals link remove
	if(strcmp(current->key, k) == 0)
	{
		if(previous == NULL)
		{
			hashLink *next = current->next;
			free(current);
			ht->table[idx] = next;
		}
		else
		{
			hashLink *another = current->next;
			free(current);
			previous->next = another; 
		}
	}	

}


/*
 returns the number of hashLinks in the table
 */
int size (struct hashMap *ht)
{
                                                                                                            //Worked On  /*write this*/
	return ht->count;

}

/*
 returns the number of buckets in the table
 */
int capacity(struct hashMap *ht)
{
                                                                                                            //Worked On /*write this*/
	return ht->tableSize;
}

/*
 returns the number of empty buckets in the table, these are buckets which have
 no hashlinks hanging off of them.
 */
int emptyBuckets(struct hashMap *ht)
{
                                                                                                    //Worked On /*write this*/
	int i;
	int count = 0;

	//go through table to check for number of null buckets
	for(i = 0; i < ht->tableSize; i++)
    {
        if(ht->table[i] == NULL)
        {
            count++;
        }
    }
    /*
    hashLink *entry = ht->table[hashIndex];

    while(entry->next != NULL && entry->key != k)
    {
        entry = entry->next;
    }
    if(entry->key == k)
    {
        return 1;
    }*/

	return count;
}

/*
 returns the ratio of: (number of hashlinks) / (number of buckets)

 this value can range anywhere from zero (an empty table) to more then 1, which
 would mean that there are more hashlinks then buckets (but remember hashlinks
 are like linked list nodes so they can hang from each other)
 */
float tableLoad(struct hashMap *ht)
{
                                                                                                            //Worked On /*write this*/

	return (float)ht->count/ht->tableSize;
	//return 0;
}
void printMap (struct hashMap * ht)
{
	int i;
	struct hashLink *temp;
	for(i = 0;i < capacity(ht); i++){
		temp = ht->table[i];
		if(temp != 0) {
			printf("\nBucket Index %d -> ", i);
		}
		while(temp != 0){
			printf("Key:%s|", temp->key);
			printValue(temp->value);
			printf(" -> ");
			temp=temp->next;
		}
	}
}


