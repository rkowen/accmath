/*
 * Sqrt(x) computes the square root function to the limits of
 *        machine accuracy for x real.
 * 
 *
 * by R.K.Owen,Ph.D.  08/15/92
 */

#ifdef TEST
typedef double PRECISION;
#else
#  include "accmath.h"
#endif


/* Use the Newton method for quadratic convergence to the zero
 * of f(x) = x*x - N
 */
PRECISION Sqrt(PRECISION x) {
	PRECISION xn = x, xn1 = 0.0;
	const PRECISION zero = 0.0, half = 0.5;

	if (x <= zero) return zero;
	while (xn != xn1) {
		xn1 = xn;
		xn = half*(xn + x/xn);
	}
	return xn;
}

#ifdef TEST

#include <stdio.h>
#include <math.h>

void main(void) {
	PRECISION x, sx, Sx, dx, scale;
	int i;
	scale = 1./2.;

	for (i = -3; i <= 8; i++) {
		x = scale * i + 1.0;
		sx = (PRECISION) sqrt(x);
		Sx = (PRECISION) Sqrt(x);
		dx = sx - Sx;
		printf("%10.4f %15.8f %15.8f %15.8e\n", x, sx, Sx, dx);
	}
	return;
}
#endif /* TEST */
