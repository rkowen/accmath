/*
 * Log0(x) computes the nateral logarithm function to the limits of
 *         machine accuracy for x real 1 < x < inf.
 *
 * by R.K.Owen,Ph.D.  08/28/92
 */

#ifdef TEST
#  define _PRECISION_
typedef double PRECISION;
#endif

#include "accmath.h"

PRECISION Log0(PRECISION x) {
	PRECISION sum = 0.0, newsum, y, term, inc = 1.0;
	const PRECISION one = 1.0, two = 2.0;

	y = (x - one)/(x + one);
	newsum = term = y;
	y *= y;
	while (sum != newsum) {
		inc += two;
		term *= y;
		sum = newsum;
		newsum += (term/inc);
	}
	return sum*two;
}

#ifdef TEST

#include <stdio.h>
#include <math.h>

void main(void) {
	PRECISION x, lx, Lx, dx, scale;
	int i;
	scale = 0.5;

	for (i = 0; i <= 10; i++) {
		x = scale * i * i + 1.0;
		lx = (PRECISION) log(x);
		Lx = (PRECISION) Log0(x);
		dx = lx - Lx;
		printf("% 8.2f % 15.8f % 15.8f % 15.8e\n", x, lx, Lx, dx);
	}
	return;
}
#endif /* TEST */
