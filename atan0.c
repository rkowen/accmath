/*
 * Atan0(x) computes the Arc Tangent trigonometric function to the limits of
 *        machine accuracy for |x| < 1. Use for range 0 <= x < 1
 *
 * by R.K.Owen,Ph.D.  08/11/92
 */

#ifdef TEST
#  define _PRECISION_
typedef double PRECISION;
#else
#  include "accmath.h"
#endif


PRECISION Atan0(PRECISION x) {
	const PRECISION two = 2.0;
	PRECISION sum = 0.0, newsum = x, x2 = x*x, term = x, inc = 1.0;

	while (sum != newsum) {
		inc += two;
		term *= (-x2);
		sum = newsum;
		newsum += term/inc;
	}
	return sum;
}

#ifdef TEST

#include <stdio.h>
#include <math.h>

void main(void) {
	PRECISION x, ax, Ax, dx, scale;
	int i;
	scale = 1./100.;

	for (i = 0; i < 100; i += 10) {
		x = scale * i;
		ax = (PRECISION) atan(x);
		Ax = (PRECISION) Atan0(x);
		dx = ax - Ax;
		printf("% 5.1f %15.8f %15.8f % 15.8e\n", x, ax, Ax, dx);
	}
	return;
}
#endif /* TEST */
