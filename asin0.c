/*
 * Asin0(x) computes the ArcSine trigonometric function to the limits of
 *         machine accuracy for x real |x| < 1.
 *
 * by R.K.Owen,Ph.D.  10/07/93
 */

#ifdef TEST
#  define _PRECISION_
typedef double PRECISION;
#endif

#include "accmath.h"

PRECISION Asin0(PRECISION x) {
	PRECISION sum = 0.0, newsum = x, x2 = x*x, term = x, inc = 1.0;
	const PRECISION one = 1.0, two = 2.0;

	while (sum != newsum) {
		term *= ((inc/(inc + one))* x2);
		inc += two;
		sum = newsum;
		newsum += term/inc;
	}
	return sum;
}

#ifdef TEST

#include <stdio.h>
#include <math.h>

void main(void) {
	PRECISION x, sx, Sx, dx;
	int i;

	for (i = 0; i < 10; ++i) {
		x = .1 * i;
		sx = (PRECISION) asin(x);
		Sx = (PRECISION) Asin0(x);
		dx = sx - Sx;
		printf("%3.1f %15.8f %15.8f %15.8e\n", x, sx, Sx, dx);
	}
	return;
}
#endif /* TEST */
