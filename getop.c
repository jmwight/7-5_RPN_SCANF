#include "calc.h" // project header
#include "readwritelines/getaline.h"
#include <ctype.h>
#include <string.h> // for strcmp which is required to see if typed letters matches a function (i.e. sin, cos, log, etc)
#include <stdio.h>

#define MXBUF	120
#define MXOP	5

/* getop: get next operator or numeric operand */
int getop(double *d)
{
	static char buf[MXBUF] = "\0";
       	static char op[MXOP] = "\0";
	static char *bufp = buf;
	if(buf[0] == '\0')
		getaline(buf, MXBUF);
	
	if(sscanf("%lf", d))
		getnxtstart(bufp);
		return NUMBER;
	else if(sscanf("%s", op))
	{
		getnxtstart(bufp);
		/* TODO: do comparisons like to check for operators,
		 * functions, setting a variable, recalling, etc. and return
		 * appropriate */
	}
	else if(bufp[-1] == '\n')
	{
		/* we've reaced the end time for next one */
		getaline(buf, MXBUF);
		return '\n';
	}
	else if(bufp[0] == '\0')
		if(getaline(buf, MXBUF) == EOF)
			return EOF;
	else
	{
		/* TODO: some error handling */
		printf("Error");
	}
	
	/* code for detecting and triggering '\n' feed back to main */
	int i;
	for(i = 0; isspace(buf[i]) && buf[i] != '\0'; i++)
		;
	if(buf[i-1] == '\n')
		return '\n';

	//if(sscanf("%c", c)
}

/* findnxtstart: finds next start position of a func/num/operator */
char *findnxtstart(char *pos)
{
	while(isspace(*pos) && *pos != '\0')
		pos++;
	while(!isspace(*pos) && *pos != '\0')
		pos++;
	while(isspace(*pos) && *pos != '\0')
		pos++;
	return pos;
}
