/*
 * Acos(x) computes the ArcCosine trigonometric function to the limits of
 *        machine accuracy for x.
 *
 * by R.K.Owen,Ph.D.  10/07/93
 *
 * calls: Pi, Asin
 */

#ifdef TEST
#  define _PRECISION_
typedef double PRECISION;
#endif

#include "accmath.h"

#ifdef TEST
#  include <stdio.h>
#endif

PRECISION Acos(PRECISION x) {
	const PRECISION zero = 0.0, one = 1.0, half = 0.5;
	static PRECISION hpi;
	static char FIRST = (0 == 0);
	int sign;

	if (FIRST) {
		FIRST = !FIRST;
#ifdef TEST
		printf("Initializing Acos\n");
#endif
		hpi = half * Pi();
	}

/* special case */
	if (x == zero) return hpi;
/* check range */
	if (Abs(x) > one) return zero;
/* pass off to Asin( ) */
	return (hpi - Asin(x));
}

#ifdef TEST

#include <math.h>

void main(void) {
	PRECISION x, ax, Ax, dx, scale;
	int i;
	scale = 0.1;

	for (i = -11; i <= 11; i++) {
		x = scale * i;
		ax = (PRECISION) acos(x);
		Ax = (PRECISION) Acos(x);
		dx = ax - Ax;
		printf("% 5.1f % 15.8f % 15.8f % 15.8e\n", x, ax, Ax, dx);
	}
	return;
}
#endif /* TEST */
