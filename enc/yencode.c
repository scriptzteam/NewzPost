/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */

#include "../base/newzpost.h"
#include "../cksfv/sfv.h"
#include "../ui/ui.h"
#include "yencode.h"

/**
*** Public Routines
**/

long yencode(FILE *infile, char *outbuf, long psize, n_uint32 *crc)
{
	long counter;
	int n, ylinepos;
	unsigned char *p, *ch, c;
	unsigned char inbuf[YENC_LINE_LENGTH];

	ylinepos = 0;
	n = 0;
	counter = 0;

	ch = (unsigned char *) outbuf;
	p = inbuf;

	while (counter < psize) {

		if (n == 0) {
			n = fread(inbuf, 1, YENC_LINE_LENGTH, infile);
			p = inbuf;
			*crc = crc32((char *) inbuf, n, *crc);
		}

		if (ylinepos >= YENC_LINE_LENGTH) {
			*ch++ = '\r';
			*ch++ = '\n';
			ylinepos = 0;
		}

		c = *p + 42;

		switch (c) {
		case '.':
			if (ylinepos > 0)
				break;
		case '\0':
		case 9:
		case '\n':
		case '\r':
		case '=':
			*ch++ = '=';
			c += 64;
			ylinepos++;
		}

		*ch++ = c;

		counter++;
		ylinepos++;
		n--;
		p++;
	}

	*ch++ = '\r';
	*ch++ = '\n';
	*ch = '\0';

	if (ferror(infile)) {
		ui_generic_error(errno);
		return 0;
	}

	return ch - (unsigned char *) outbuf;
}
