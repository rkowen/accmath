/*
 * Cos(x) computes the Cosine trigonometric function to the limits of
 *        machine accuracy for x real.
 *
 * by R.K.Owen,Ph.D.  08/21/92
 *
 * calls: Pi, Cos0, Sin0
 */

#ifdef TEST
#  define _PRECISION_
typedef double PRECISION;
#endif

#include "accmath.h"

#ifdef TEST
#  include <stdio.h>
#endif

PRECISION Cos(PRECISION x) {
	const PRECISION zero = 0.0, one = 1.0, two = 2.0, half = 0.5;
	static PRECISION pi, twopi, twopii, hpi, qpi;
	static char FIRST = (0 == 0);
	int n;

	if (FIRST) {
		FIRST = !FIRST;
#ifdef TEST
		printf("Initializing Cos\n");
#endif
		pi = Pi();
		twopi = two*pi;
		twopii = one/twopi;
		hpi = half*pi;
		qpi = half*hpi;
	}

/* reduce x by integer factors of 2pi */
	n = x*twopii;
	if (n) x -= (n*twopi);
/* take absolute value of x */
	x = Abs(x);
/* if x > pi then reflect about x=pi */
	if (x > pi) {
		x = twopi - x;
	}
/* if x > pi/2 then reflect about x=pi/2 */
	if (x > hpi) {
		x = pi - x;
		n = -1;
	} else {
		n =  1;
	}
/* if pi/4 < x < pi then call Sine */
	if (x > qpi) {
		x = hpi - x;
		return n*Sin0(x);
	} else {
		return n*Cos0(x);
	}
}

#ifdef TEST

#include <math.h>

#define hpi 1.57079632679490

void main(void) {
	PRECISION x, cx, Cx, dx, deg2rad;
	int i;
	deg2rad = hpi/90.;

	for (i = -360; i <= 1080; i += 10) {
		x = deg2rad * i;
		cx = (PRECISION) cos(x);
		Cx = (PRECISION) Cos(x);
		dx = cx - Cx;
		printf("% 5.0d % 15.8f % 15.8f % 15.8e\n", i, cx, Cx, dx);
	}
	return;
}
#endif /* TEST */
