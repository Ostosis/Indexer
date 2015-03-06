/*
 * hashmap.h
 *
 *  Created on: Mar 4, 2015
 *      Author: as1705
 */

#ifndef HASHMAP_H_
#define HASHMAP_H_

#define INITIAL_CAPACITY 16
#define LOAD_FACTOR 0.75f
#define MAX_CAPACITY 1<<30


struct Entry{

	void * key;
	void * value;
	struct Entry * next;


};
typedef struct Entry Entry_p;

struct HashMap
{

	int capacity;
	int load;
	int size;
	Entry_p map;

};
typedef struct HashMap * HashMap_p;

typedef int (*CompareFuncT)(void *, void *);

int containsKey(HashMap_p hm, void * key, CompareFuncT);
HashMap_p newHashMap();

int hash(void * key);
int put(HashMap_p hm,  void * key, void * value);
void * get(HashMap_p hm, void* key);

#endif /* HASHMAP_H_ */
