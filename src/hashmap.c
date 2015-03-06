#include "hashmap.h"
#include <malloc.h>

HashMap_p newHashMap()
{
	HashMap_p hm = calloc(1, sizeof(struct HashMap));

	hm->capacity = INITIAL_CAPACITY;
	hm->load = LOAD_FACTOR;
	hm->size = 0;

	return hm;

}

int containsKey(HashMap_p hm, void * key, CompareFuncT cf)
{
	int hash = hash(key);

	return 0;
}

int put(HashMap_p hm, void * key, void * value)
{
	hm->size++;
	if (hm->size >= MAX_CAPACITY)
	{

		fprintf(stderr, "Attempted to add entry to hashmap of max capacity\n");
		return -1;
	}


	return 0;
}

int hash(void * key)
{
	return 0;
}
void * get(HashMap_p hm, void* key)
{

	return 0;
}
