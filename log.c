/*
 * Log(x) computes the natural or napierian logarithm function to the limits of
 *        machine accuracy for x.
 *
 * by R.K.Owen,Ph.D.  08/29/92
 *
 * calls: E, Log0
 */

#ifdef TEST
#  define _PRECISION_
typedef double PRECISION;
#  define _INTEGER_
typedef int INTEGER;
#endif

#include "accmath.h"

#ifdef TEST
#  include <stdio.h>
#endif

/* keep array of binary powers of e */
#ifndef Log_Arr
#  define Log_Arr 31
#endif

PRECISION Log(PRECISION x) {
	const PRECISION zero = 0.0, one = 1.0;
	static PRECISION e[Log_Arr], ei[Log_Arr];
	static int Max_Log_Arr;
	static char FIRST = (0 == 0);
	int sign, inc;
	INTEGER pow;

	if (FIRST) {
		FIRST = !FIRST;
#ifdef TEST
		printf("Initializing Log\n");
#endif
/* fill e[], ei[] with binary powers of e & 1/e respectively */
		e[0] = E();
		ei[0] = one/e[0];
		ei[1] = ei[0]*ei[0];
		inc  = 1;
		Max_Log_Arr   = 0;
/* assume graceful underflow and balanced high & low ranges */
		while (ei[inc] > zero) {
			e[inc] = e[Max_Log_Arr]*e[Max_Log_Arr];
			inc++;
			Max_Log_Arr++;
			if (inc >= Log_Arr) {
				printf("Inadequate Log_Arr = %d\n",Log_Arr);
				break;
			}
			ei[inc] = ei[Max_Log_Arr]*ei[Max_Log_Arr];
		}
	}

/* special case */
	if (x == one) return zero;

/* if nonpositive -- error -- return 0 */
	if (x <= zero) return zero;

/* if less than one then invert & keep sign */
	if (x < one) {
		sign = -1;
		x = one/x;
	} else {
		sign = 1;
	}
/* find max power of e */
	inc = 0;
	pow = 0;
	while (x > e[inc]) inc++;
/* whittle down x */
	while (--inc >= 0) {
		pow <<= 1;
		if (x > e[inc]) {
			x *= ei[inc];
			pow |= 1;
		}
	}
	x = Log0(x);
	return sign*(x + (PRECISION) pow);
}

#ifdef TEST

#include <math.h>

void main(void) {
	PRECISION x, lx, Lx, dx, scale, term = 1.0;
	int i;
	scale = 0.5;

	for (i = 0; i <= 15; i++) {
		x = scale * i * term - 1.0;
		lx = (PRECISION) log(x);
		Lx = (PRECISION) Log(x);
		dx = lx - Lx;
		printf("% 20.2f % 15.8f % 15.8f % 15.8e\n", x, lx, Lx, dx);
		term *= 3.0;
	}
	return;
}
#endif /* TEST */
