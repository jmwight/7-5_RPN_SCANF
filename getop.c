#include "calc.h" // project header
#include <ctype.h>
#include <string.h> // for strcmp which is required to see if typed letters matches a function (i.e. sin, cos, log, etc)
#include <stdio.h>

#define MXBUF	120

/* getop: get next operator or numeric operand */
int getop(double *d)
{
	static buf[MXBUF];
	static *bufp = buf;
	int l, c;
	l = getaline(buf, MXBUF);
	
	int i;
	for(i = bufp; isspace(buf[i]) && buf[i] != '\0'; i++)
		;
	if(buf[i-1] == '\n')
		return '\n';

	//if(sscanf("%c", c)
}
