#ifndef WHY_STRING_H_INCLUDED
#define WHY_STRING_H_INCLUDED

#include<stdlib.h>
#include<string.h>

#ifndef YCHAR
#define YCHAR char
#endif

typedef struct {
	size_t length;
	size_t size;
	YCHAR* c_str;
} YS;

YS  yst;

size_t cs_len(const YCHAR* s);
YS     ys_init(size_t length);
YS     ys_init_copy(size_t length, void* data);
YS     ys_from_cs(const YCHAR* s);
YS     ys_from_nothing();
YS     ys_from_ys(const YS* ys);
YS     ys_from_char(YCHAR c);
//YS  ys_from_num_dec(int n);
//YS  ys_from_num_hex(int n);
//YS  ys_from_num_bin(int n);
//YS  ys_from_boolean(int n);
int    ys_free(const YS* ys);
size_t ys_free_array(const YS* ys, size_t arrsz);
int    ys__premem(YS* ys, size_t newsz);
int    ys_foreach(const YS* ys, YCHAR(*function)(YCHAR));
int    ys_insert_cs(YS* ys, int i, const YCHAR* s);
int    ys_insert_ys(YS* ys, int i, const YS* s);
int    ys_insert_char(YS* ys, int i, YCHAR c);
int    ys_add_cs(YS* ys, int i, const YCHAR* s);
int    ys_add_ys(YS* ys, int i, const YS* s);
int    ys_add_char(YS* ys, int i, YCHAR c);
int    ys_indexOf_from(const YS* ys, size_t i, YCHAR c);
int    ys_indexOf(const YS* ys, YCHAR c);
size_t ys_countOf_from(const YS* ys, size_t i, YCHAR c);
size_t ys_countOf(const YS* ys, YCHAR c);
YS     ys_substring(const YS* ys, size_t i, size_t len);
YS*    ys_split(const YS* ys, YCHAR c, size_t* arrsz);

#endif