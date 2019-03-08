#include <stdlib.h>
#include <stdint.h>
#include "vector.h"

int vec_init(vec_t *vec, size_t nmemb)
{

	void **buff = calloc(nmemb, sizeof(void *));
	if(!buff)
	{
		return 1;
	}
	else
	{
		vec->items = buff;
		vec->alloc = nmemb;
		return 0;
	}
}

static int vec_resize(vec_t *vec, size_t nmemb)
{
	if(vec->alloc >= nmemb)
	{
		return 0;
	}
	void **buff = reallocarray(vec->items, nmemb, sizeof(void*)); //fixed it :)
	if(!buff || buff == vec->items)
	{
		
		return 1;
	}
	else
	{
		vec->items = buff;
		vec->nmemb = nmemb;
		vec->alloc = nmemb;
		return 0;
	}
}

int vec_push(vec_t *vec, void *item)
{
	int result = vec_resize(vec, vec->nmemb++);
	if(!result)
	{
		vec->items[vec->nmemb-1] = item;
		return 0;
	}
	else
	{
		vec->nmemb--;
		return 1;
		
	}
}

int vec_pop(vec_t *vec, size_t item)
{
	int result = vec_resize(vec, vec->nmemb--);
	if(!result)
	{	
		return 0;	
	}
	else
	{
		vec->nmemb++;
		return 1;
	}
}

void vec_free(vec_t *vec)
{
	free(vec->items);
}
