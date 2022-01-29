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

int   yv_free(YV yv) {
	if (yv.data) free(yv.data);
}

void* yv__at(YV yv, int i) {
	size_t j = i < 0 ? yv.e_count - i : i;
	return (char*)yv.data + j * yv.e_sz;
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
	if (yv->real_size < yv->size + yv->e_sz)
		if (!yv__realoc(yv))
			return 0;

	yv->e_count++;

	if (yv_set_at(*yv, -1, src)) return 1;

	yv->e_count--;
	return 0;
}

int   yv_pop(YV* yv) {
	if (yv->e_count == 0) return 0;

	yv->e_count--;
	yv->size -= yv->e_sz;
	return 1;
}