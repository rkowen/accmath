/*
 * Sin0(x) computes the Sine trigonometric function to the limits of
 *         machine accuracy for x real -pi/2 < x < pi/2.
 *
 * by R.K.Owen,Ph.D.  08/11/92
 */

#ifdef TEST
#  define _PRECISION_
typedef double PRECISION;
#endif

#include "accmath.h"

PRECISION Sin0(PRECISION x) {
	PRECISION sum = 0.0, newsum = x, x2 = x*x, term = x,
		inc = 1.0;
	const PRECISION one = 1.0, two = 2.0;

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
	PRECISION x, sx, Sx, dx, deg2rad;
	int i;
	deg2rad = hpi/90.;

	for (i = 0; i <= 90; i += 10) {
		x = deg2rad * i;
		sx = (PRECISION) sin(x);
		Sx = (PRECISION) Sin0(x);
		dx = sx - Sx;
		printf("%3.d %15.8f %15.8f %15.8e\n", i, sx, Sx, dx);
	}
	return;
}
#endif /* TEST */
