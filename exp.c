/*
 * Exp(x) computes the natural exponontial function to the limits of
 *        machine accuracy for x real.
 *
 * by R.K.Owen,Ph.D.  08/21/92
 *
 * calls: Exp0, Npow, E
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

PRECISION Exp(PRECISION x) {
	const PRECISION zero = 0.0, one = 1.0;
	static PRECISION e;
	static char FIRST = (0 == 0);
	PRECISION frac, pow;
	INTEGER n;
	signed char sign = 1;

	if (FIRST) {
		FIRST = !FIRST;
#ifdef TEST
		printf("Initializing Exp\n");
#endif
		e = E();
	}

/* special case */
	if (x == zero) return one;

/* find sign of x and take absolute value & fractional part only */
	n = x;
	frac = x - n;
	if (frac < zero) {
		sign = -1;
		frac = -frac;
	}

/* compute exp of fraction */
	frac = Exp0(frac);
	if (sign < 0) frac = one/frac;
/* compute e^n */
	pow = Npow(e,n);
/* final result */
	return frac*pow;
}

#ifdef TEST

#include <math.h>

void main(void) {
	PRECISION x, ex, Ex, dx, scale;
	int i;
	scale = .1;

	for (i = -100; i <= 100; i += 10) {
		x = scale * i;
		ex = (PRECISION) exp(x);
		Ex = (PRECISION) Exp(x);
		dx = 1.0 - Ex/ex;
		printf("% 5.1f %15.8f %15.8f % 15.8e\n", x, ex, Ex, dx);
	}
	return;
}
#endif /* TEST */
