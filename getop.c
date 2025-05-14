#include "calc.h" // project header
#include "readwritelines/getaline.h"
#include <ctype.h>
#include <string.h> // for strcmp which is required to see if typed letters matches a function (i.e. sin, cos, log, etc)
#include <stdio.h>

#define MXBUF	120

static char *findnxtstart(char *pos);

/* getop: get next operator or numeric operand */
int getop(double *d)
{
	static char buf[MXBUF] = "\0";
       	static char op[MXOP] = "\0";
	static char *bufp = buf;
	if(buf[0] == '\0')
		getaline(buf, MXBUF);
	
	if(sscanf("%lf", d))
	{
		getnxtstart(bufp);
		return NUMBER;
	}
	else if(sscanf("%s", op))
	{
		getnxtstart(bufp);
		int l = strlen(op);
		bufp += l; /* speed optimization to save */
		if(l == 1)
		{
			switch(op[0])
			{
			case '+':
			case '-':
			case '*':
			case '/':
			case '%':
			case '?':
			case '!':
			case '@':
				return op[0];
				break;
			default:
				printf("Error: invalid operator\n");
				return EOF;
			}
		}
		else if(strcmp(op, "sin"))
			return SIN;
		else if(strcmp(op, "cos"))
			return COS;
		else if(strcmp(op, "tan"))
			return TAN;
		else if(strcmp(op, "asin"))
			return ASIN;
		else if(strcmp(op, "acos"))
			return ACOS;
		else if(strcmp(op, "atan"))
			return ATAN;
		else if(strcmp(op, "exp"))
			return EXP;
		else if(strcmp(op, "log"))
			return LOG;
		else if(strcmp(op, "sqrt"))
			return SQRT;
		else if(strcmp(op, "ceil"))
			return CEIL;
		else if(strcmp(op, "flr"))
			return FLOOR;
		else if(strcmp(op, "abs"))
			return ABS;
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
	{
		if(getaline(buf, MXBUF) == EOF)
			return EOF;
	}
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
static char *findnxtstart(char *pos)
{
	while(isspace(*pos) && *pos != '\0')
		pos++;
	while(!isspace(*pos) && *pos != '\0')
		pos++;
	while(isspace(*pos) && *pos != '\0')
		pos++;
	return pos;
}
