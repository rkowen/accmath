/*
 * Atan(x) computes the inverse tangent trigonometric function to the limits of
 *        machine accuracy for x.
 *
 * by R.K.Owen,Ph.D.  08/28/92
 *
 * calls: Pi, Atan0, Atan1
 */

#ifdef TEST
#  define _PRECISION_
typedef double PRECISION;
#endif

#include "accmath.h"

#ifdef TEST
#  include <stdio.h>
#endif

PRECISION Atan(PRECISION x) {
	const PRECISION zero = 0.0, one = 1.0, half = 0.5, threehalf = 1.5;
	static PRECISION hpi;
	static char FIRST = (0 == 0);
	int sign;

	if (FIRST) {
		FIRST = !FIRST;
#ifdef TEST
		printf("Initializing Atan\n");
#endif
		hpi = Pi()*half;
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
	if (x < half) {
		return sign*Atan0(x);
	} else if (x < threehalf) {
		return sign*Atan1(x);
	} else {
		x = one/x;
		return sign*(hpi - Atan0(x));
	}
}

#ifdef TEST

#include <math.h>

void main(void) {
	PRECISION x, ax, Ax, dx, scale;
	int i;
	scale = 0.2;

	for (i = -20; i <= 40; i++) {
		x = 1.0 + scale * i;
		ax = (PRECISION) atan(x);
		Ax = (PRECISION) Atan(x);
		dx = ax - Ax;
		printf("% 5.1f % 15.8f % 15.8f % 15.8e\n", x, ax, Ax, dx);
	}
	return;
}
#endif /* TEST */
