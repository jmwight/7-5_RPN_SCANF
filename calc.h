#ifndef CALC_H
#define CALC_H  1

/* defined constants */
#define MAXOP   100     /* max size of operand or operator */
/* start at 256 to ensure not conflicting with ascii or ascii extended
 * character set */
enum OpType { NONE = 256, NUMBER, VAR, SIN, COS, TAN, ASIN, ACOS, ATAN, EXP,
	LOG, SQRT, CEIL, FLOOR, ABS, CUSTVARMAX };

/* function definitions */
extern int getop(char []);
extern void push(double);
extern double pop(void);
extern double ptop(void);
extern void swaptop(void);
extern void clrstack(void);
extern int stacksize(void);
extern int getch(void);
extern void ungetch(int);
extern void ungets(char*);

/* global custom variables a-z user can set */
extern int cust_var[/*CUSTVARMAX*/];

#endif // CALC_H
