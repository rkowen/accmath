/*
 * Atan1(x) computes the Arc Tangent trigonometric function to the limits of
 *        machine accuracy for all x. Use for range 1/2 <= x < 3/2
 *
 * by R.K.Owen,Ph.D.  08/28/92
 */

#ifdef TEST
#  define _PRECISION_
typedef double PRECISION;
#else
#  include "accmath.h"
#endif


PRECISION Atan1(PRECISION x) {
	const PRECISION one = 1.0, two = 2.0;
	PRECISION sum = 0.0, newsum = 1.0, y, term, inc = 1.0;

	y = x*x;
	term = one/(y + one);
	y *= term;
	x *= term;
	term = one;

	while (sum != newsum) {
		inc += two;
		term *= ((inc - one)/inc) * y;
		sum = newsum;
		newsum += term;
	}
	return x*sum;
}

#ifdef TEST

#include <stdio.h>
#include <math.h>

void main(void) {
	PRECISION x, ax, Ax, dx, scale;
	int i;
	scale = 0.1;

	for (i = -9; i <= 9; i++) {
		x = 1.0 + scale * i;
		ax = (PRECISION) atan(x);
		Ax = (PRECISION) Atan1(x);
		dx = ax - Ax;
		printf("% 5.1f %15.8f %15.8f % 15.8e\n", x, ax, Ax, dx);
	}
	return;
}
#endif /* TEST */
