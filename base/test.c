/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */

#include "newzpost.h"

int main(int argc, char ** argv){
	boolean error = FALSE;

	if(sizeof(n_uint8) != 1){
		error = TRUE;
		fprintf(stderr, "\nYour unsigned chars are not 1 byte.");
	}
	if(sizeof(n_uint16) != 2){
		error = TRUE;
		fprintf(stderr, "\nYour unsigned short ints are not 2 bytes.");
	}
	if(sizeof(n_uint32) != 4){
		error = TRUE;
		fprintf(stderr, "\nYour unsigned ints are not 4 bytes.");
	}
	if(sizeof(n_int64) != 8){
		error = TRUE;
		fprintf(stderr, "\nYour long longs are not 8 bytes.");
	}
	if(error == TRUE){
		fprintf(stderr, "\nPlease edit base/newzpost.h");
                fprintf(stderr, "\nThen run \"make clean\" and \"make\" again");
                fprintf(stderr, "\n\n");
		return -1;
	}
	else{
		return 0;
	}
}

