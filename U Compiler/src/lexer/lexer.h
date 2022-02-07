#ifndef U_LEXER_H_INCLUDED
#define U_LEXER_H_INCLUDED

#include"../why/yvector.h"
#include"token.h"

typedef struct {
	char* dirname;
	char* filename;
	char* data;
	YV    tokens;
} LexerData;



#endif