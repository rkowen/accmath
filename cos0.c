/*
 * Cos0(x) computes the Cosine trigonometric function to the limits of
 *         machine accuracy for x real -pi < x < pi
 *
 * by R.K.Owen,Ph.D.  08/11/92
 */

#ifdef TEST
#  define _PRECISION_
typedef double PRECISION;
#endif

#include "accmath.h"

PRECISION Cos0(PRECISION x) {
	PRECISION sum = 1.0, newsum, x2 = x*x, term, inc = 2.0;
	const PRECISION one = 1.0, two = 2.0, half = 0.5;
	term = -half*x2;
	newsum = one - half*x2;

	while (sum != newsum) {
		inc += two;
		term *= (-x2/(inc*(inc - one)));
		sum = newsum;
		newsum += term;
	}
	return sum;
}

#ifdef TEST

#include <stdio.h>
#include <math.h>

#define hpi 1.57079632679490

void main(void) {
	PRECISION x, cx, Cx, dx, deg2rad;
	int i;
	deg2rad = hpi/90.;

	for (i = 0; i <= 90; i += 10) {
		x = deg2rad * i;
		cx = (PRECISION) cos(x);
		Cx = (PRECISION) Cos0(x);
		dx = cx - Cx;
		printf("%3.d %15.8f %15.8f %15.8e\n", i, cx, Cx, dx);
	}
	return;
}
#endif /* TEST */
