/*
 * Asin(x) computes the ArcSine trigonometric function to the limits of
 *        machine accuracy for x.
 *
 * by R.K.Owen,Ph.D.  10/07/93
 *
 * calls: Sqrt, Atan
 */

#ifdef TEST
#  define _PRECISION_
typedef double PRECISION;
#endif

#include "accmath.h"

#ifdef TEST
#  include <stdio.h>
#endif

PRECISION Asin(PRECISION x) {
	const PRECISION zero = 0.0, one = 1.0, half = 0.5;
	static PRECISION cut;
	static char FIRST = (0 == 0);
	int sign;

	if (FIRST) {
		FIRST = !FIRST;
#ifdef TEST
		printf("Initializing Asin\n");
#endif
		cut = Sqrt(half);
	}

/* special case */
	if (x == zero) return zero;

/* get sign & use absolute value */
	if (x < zero) {
		sign = -1;
		x = -x;
	} else {
		sign = 1;
	}
/* break into ranges */
	if (x < cut) {
		return sign*Asin0(x);
	} else if (x <= one) {
		x /= Sqrt(one - x*x);
		return sign*Atan(x);
	} else {
		return zero;	/* illegal value x > 1 */
	}
}

#ifdef TEST

#include <math.h>

void main(void) {
	PRECISION x, ax, Ax, dx, scale;
	int i;
	scale = 0.1;

	for (i = -11; i <= 11; i++) {
		x = scale * i;
		ax = (PRECISION) asin(x);
		Ax = (PRECISION) Asin(x);
		dx = ax - Ax;
		printf("% 5.1f % 15.8f % 15.8f % 15.8e\n", x, ax, Ax, dx);
	}
	return;
}
#endif /* TEST */
