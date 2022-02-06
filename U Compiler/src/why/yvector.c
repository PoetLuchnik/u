#include"yvector.h"

YV    yv_init(size_t e_sz, size_t e_count) {
	YV yv;
	yv.e_count = e_count;
	yv.e_sz = e_sz;
	yv.size = e_count * e_sz;
	yv.real_size = yv.size ? yv.size : e_sz;
	yv.data = malloc(yv.real_size);
	return yv;
}

YV    yv_init_empty(size_t e_sz) {
	yv_init(e_sz, 0);
}

void  yv_free(YV yv) {
	if (yv.data) free(yv.data);
}

void* yv__at(YV yv, int i) {
	if (i >= (int)yv.e_count) return yv__at(yv, i - yv.e_count);
	if (i < 0)                return yv__at(yv, yv.e_count + i);
	return (char*)yv.data + i * yv.e_sz;
}

int   yv__realoc(YV* yv) {
	size_t new_sz = yv->real_size * 2;
	void* ptr = realloc(yv->data, new_sz);
	if (ptr == 0) return 0;
	yv->data = ptr;
	yv->real_size = new_sz;
	return 1;
}

int   yv_set_at(YV yv, int i, void* src) {
	if (!src) return 0;
	return memcpy(yv__at(yv, i), src, yv.e_sz) != 0;
}

int   yv_get_at(YV yv, int i, void* dst) {
	if (!dst) return 0;
	return memcpy(dst, yv__at(yv, i), yv.e_sz) != 0;
}

int   yv_push(YV* yv, void* src) {
	if (!yv__premem(yv, yv->e_sz)) return 0;

	yv->e_count++;
	yv->size += yv->e_sz;

	if (yv_set_at(*yv, -1, src)) return 1;

	yv->e_count--;
	yv->size -= yv->e_sz;

	return 0;
}

int   yv_pop(YV* yv) {
	if (yv->e_count == 0) return 0;

	yv->e_count--;
	yv->size -= yv->e_sz;
	return 1;
}

int   yv__insert(YV* yv, int i, void* src, size_t src_ecount) {
	void* beg = yv__at(*yv, i);
	size_t sz = src_ecount * yv->e_sz;
	void* end = (char*)beg + sz;

	if (!yv__premem(yv, sz))   return 0;
	if (!memcpy(end, beg, sz)) return 0;
	if (!memcpy(beg, src, sz)) return 0;

	yv->e_count += src_ecount;
	yv->size += sz;

	return 1;
}

int   yv_insert(YV* yv, int i, void* src) {
	return yv__insert(yv, i, src, 1);
}

int   yv_insert_yv(YV* yv, int i, YV* yv2) {
	return yv->e_sz == yv2->e_sz ? yv__insert(yv, i, yv->data, yv->e_count) : 0;
}

int   yv__premem(YV* yv, size_t off) {
	if (yv->real_size < yv->size + off)
		return yv__realoc(yv) ? yv__premem(yv, off) : 0;
		
	return 1;
}