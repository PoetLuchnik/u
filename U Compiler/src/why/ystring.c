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
	return t;
}

YS     ys_from_cs(const YCHAR* s) {
	YS t = ys_init(cs_len(s));
	if (t.c_str) memcpy(t.c_str, s, t.size);
	return t;
}

YS     ys_from_nothing() {
	YS t = ys_init(0);
	if (t.c_str) t.c_str[0] = 0;
	return t;
}

YS     ys_from_ys(const YS* ys) {
	YS t = ys_init(ys->length);
	if (t.c_str) memcpy(t.c_str, ys->c_str, t.size);
	return t;
}

YS     ys_from_char(YCHAR c) {
	YS t = ys_init(1);
	if (t.c_str) {
		t.c_str[0] = c;
		t.c_str[1] = 0;
	}
	return t;
}