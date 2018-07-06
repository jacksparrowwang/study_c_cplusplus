#pragma once

enum
{
	NULLSET,
	CSET,
	CPPSET,
	EOFSET
};

#include<stdlib.h>
#define INPUT "input.txt"
#define OUTPUT "output.txt"

void converter_mian();
void converter_null(FILE *ipf,FILE *opf);
void converter_cpp(FILE *ipf,FILE *opf);
void converter_c(FILE *ipf,FILE *opf);