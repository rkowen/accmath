/*
 * Exp0(x) computes the natural exponential function to the limits of
 *         machine accuracy for x real 0 <= x <= 1.
 *
 * by R.K.Owen,Ph.D.  08/20/92
 */

#ifdef TEST
#  define _PRECISION_
typedef double PRECISION;
#endif

#include "accmath.h"

PRECISION Exp0(PRECISION x) {
	PRECISION sum = 0.0, newsum = 1.0, term = 1.0, inc = 0.0;

	while (sum != newsum) {
		inc++;
		term *= (x/inc);
		sum = newsum;
		newsum += term;
	}
	return sum;
}

#ifdef TEST

#include <stdio.h>
#include <math.h>

void main(void) {
	PRECISION x, ex, Ex, dx, scale;
	int i;
	scale = 0.01;

	for (i = 0; i <= 100; i += 10) {
		x = scale * i;
		ex = (PRECISION) exp(x);
		Ex = (PRECISION) Exp0(x);
		dx = ex - Ex;
		printf("%3.d %15.8f %15.8f %15.8e\n", i, ex, Ex, dx);
	}
	return;
}
#endif /* TEST */
