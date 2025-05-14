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
	
	if(sscanf(bufp, "%lf", d) == 1)
	{
		bufp = findnxtstart(bufp);
		return NUMBER;
	}
	else if(sscanf(bufp, "%s", op) == 1)
	{
		bufp = findnxtstart(bufp);
		int l = strlen(op);
		if(l == 1)
		{
			/* test if math / general calculator operator and if so
			 * return it */
			char *oploc;
			/* will be null pointer if not found */
			oploc = strchr("+-*/%?!@", (int)op[0]);
			if(oploc != NULL)
				return op[0];
			else if(op[0] >= 'a' && op[0] <= 'z')
			{
				char var = op[0];
				if(sscanf(bufp, "%s %lf", op, d) == 2 &&
						strlen(op) == 1 &&
						op[0] == '=')
				{
					cust_var[var - 'a'] = *d;
					/* run twice to get over '=' and num */
					bufp = findnxtstart(bufp);
					bufp = findnxtstart(bufp);
					return NUMBER;
				}
				else
					return var;
			}
			else
			{
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
	}
	else if(bufp[0] == '\n')
	{
		/* we've reached the end. This will make getline run next time */
		buf[0] = '\0';
		bufp = buf; /* reset buffer pointer to beginning of buf */
		return '\n';
	}
	else if(bufp[0] == '\0')
	{
		if(getaline(buf, MXBUF) == EOF)
			return EOF;
	}
	else
	{
		printf("Error: invalid input!\n");
		return EOF;
	}
	return UNKNOWN;
}

/* findnxtstart: finds next start position of a func/num/operator */
static char *findnxtstart(char *pos)
{
	while(isspace(*pos) && *pos != '\n')
		pos++;
	while(!isspace(*pos) && *pos != '\n')
		pos++;
	while(isspace(*pos) && *pos != '\n')
		pos++;
	return pos;
}
