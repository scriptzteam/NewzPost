/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
#include "../base/newzpost.h"
#include "../ui/ui.h"


const char trans_ptr[64] =
{
	'`', '!', '"', '#', '$', '%', '&', '\'',
	'(', ')', '*', '+', ',', '-', '.', '/',
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', ':', ';', '<', '=', '>', '?',
	'@', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
	'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
	'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
	'X', 'Y', 'Z', '[', '\\', ']', '^', '_'
};

/* ENC is the basic 1 character encoding function to make a char printing.  */
#define ENC(Char) (trans_ptr[(Char)])

/**
*** Public Routines
**/

long uu_encode(FILE *infile, char *outbuf, int maxlines)
{
	int counter = 0;
	int n;
	char *p, *ch;
	char inbuf[80];
	
	ch = outbuf;
	while (counter < maxlines) {
		counter++;
		n = fread(inbuf, 1, 45, infile);
		
		if (n == 0)
			break;
		
		*ch = ENC(n);
		if (*ch == '.') { 
			ch++;
			*ch++ = '.';
		}
		else
			ch++;
		
		for (p = inbuf; n > 0; n -= 3, p += 3) {
			if (n < 3) {
				p[2] = '\0';
				if (n < 2)
					p[1] = '\0';
			}
			
			*ch++ = ENC( (*p >> 2) & 077 );
			*ch++ = ENC( ((*p << 4) & 060) | ((p[1] >> 4) & 017) );
			*ch++ = ENC( ((p[1] << 2) & 074) | ((p[2] >> 6) & 03) );
			*ch++ = ENC( p[2] & 077 );
		}
		*ch++ = '\r';
		*ch++ = '\n';
	}
	
	if (feof(infile) != 0) {
		*ch++ = ENC('\0');
		*ch++ = '\r';
		*ch++ = '\n';
	}
	else if (ferror(infile)) {
		ui_generic_error(errno);
		return 0;
	}
	
	*ch = '\0';
	
	return ch - outbuf;
}

