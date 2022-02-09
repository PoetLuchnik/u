#include"ystring.h"

size_t cs_len(const YCHAR* s) {
	size_t i = 0;
	while (s[i]) i++;
	return i;
}

YS     ys_init(size_t length) {
	YS t;
	t.length = length;
	t.size = ++length * sizeof(YCHAR);
	t.c_str = malloc(t.size);
	if (t.c_str) t.c_str[t.length] = 0;
	return t;
}

YS     ys_init_copy(size_t length, void* data) {
	YS t = ys_init(length);
	if (t.c_str && data) memcpy(t.c_str, data, t.size - sizeof(YCHAR));
	return t;
}

YS     ys_from_cs(const YCHAR* s) {
	return s ? ys_init_copy(cs_len(s), s) : ys_from_nothing();
}

YS     ys_from_nothing() {
	return ys_init(0);
}

YS     ys_from_ys(const YS* ys) {
	return ys ? ys_init_copy(ys->length, ys->c_str) : ys_from_nothing();
}

YS     ys_from_char(YCHAR c) {
	return ys_init_copy(1, &c);
}

int    ys_free(const YS* ys) {
	if (ys == 0)		return 0;
	if (ys->c_str == 0) return 0;
	free(ys->c_str);
	return 1;
}

size_t ys_free_array(const YS* ysarr, size_t arrsz) {
	size_t t = 0;

	if (ysarr && ysarr->c_str)
		for (size_t i = 0; i < arrsz; i++)
			if (ys_free(&ysarr[i])) t++;

	return t;
}

int    ys_foreach(const YS* ys, YCHAR(*function)(YCHAR)) {
	if (ys == 0 || ys->c_str == 0) return 0;

	for (size_t i = 0; i < ys->length; i++)
		ys->c_str[i] = function(ys->c_str[i]);

	return 1;
}


int    ys_indexOf_from(const YS* ys, size_t i, YCHAR c) {
	if (ys == 0 || ys->c_str == 0) return -2;

	for (size_t i = 0; i < ys->length; i++)
		if (ys->c_str[i] == c) return i;

	return -1;
}

int    ys_indexOf(const YS* ys, YCHAR c) {
	return ys_indexOf_from(ys, 0, c);
}

size_t ys_countOf_from(const YS* ys, size_t i, YCHAR c) {
	size_t n = 0;

	for (int i = -1; (i = ys_indexOf_from(ys, ++i, c)) >= 0; n++);

	return n;
}

size_t ys_countOf(const YS* ys, YCHAR c) {
	return ys_countOf_from(ys, 0, c);
}