#ifndef WHY_VECTOR_H_INCLUDED
#define WHY_VECTOR_H_INCLUDED

#include<stdlib.h>
#include<string.h>

typedef struct {
	size_t e_sz;
	size_t e_count;
	size_t size;
	size_t real_size;
	void* data;
} YV;

YV    yv_init(size_t e_sz, size_t e_count);
YV    yv_init_empty(size_t e_sz);
void  yv_free(YV yv);
void* yv__at(YV yv, int i);
int   yv__realoc(YV * yv);
int   yv_set_at(YV yv, int i, void* src);
int   yv_get_at(YV yv, int i, void* dst);
int   yv_push(YV * yv, void* src);
int   yv_pop(YV * yv);
int   yv__insert(YV * yv, int i, void * src, size_t src_ecount);
int   yv_insert(YV * yv, int i, void * src);
int   yv_insert_yv(YV * yv, int i, YV * yv2);
int   yv__premem(YV * yv, size_t off);

#endif