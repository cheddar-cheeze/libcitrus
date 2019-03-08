#ifndef VECTOR_H
#define VECTOR_H

typedef struct
{
	size_t nmemb;
	size_t alloc;
	void **items;
} vec_t;

int vec_init(vec_t *vec, size_t nmemb);
static int vec_resize(vec_t *vec, size_t nmemb);
int vec_push(vec_t *vec, void *item);
int vec_pop(vec_t *vec, size_t item);
void vec_free(vec_t *vec);
#endif
