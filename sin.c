/*
 * Sin(x) computes the Sine trigonometric function to the limits of
 *        machine accuracy for x real.
 *
 * by R.K.Owen,Ph.D.  08/11/92
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

PRECISION Sin(PRECISION x) {
	const PRECISION zero = 0.0, one = 1.0, two = 2.0, half = 0.5;
	static PRECISION pi, twopi, twopii, hpi, qpi;
	static char FIRST = (0 == 0);
	int n;

	if (FIRST) {
		FIRST = !FIRST;
#ifdef TEST
		printf("Initializing Sin\n");
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
/* if < 0 then take negative */
	if (x < zero) {
		n = -1;
		x = -x;
	} else {
		n = 1;
	}
/* if x > pi then reflect about x=pi */
	if (x > pi) {
		x = twopi - x;
		n *= -1;
	}
/* if x > pi/2 then reflect about x=pi/2 */
	if (x > hpi) {
		x = pi - x;
	}
/* if pi/4 < x < pi then call Cosine */
	if (x > qpi) {
		x = hpi - x;
		return n*Cos0(x);
	} else {
		return n*Sin0(x);
	}
}

#ifdef TEST

#include <math.h>

#define hpi 1.57079632679490

void main(void) {
	PRECISION x, sx, Sx, dx, deg2rad;
	int i;
	deg2rad = hpi/90.;

	for (i = -360; i <= 1080; i += 10) {
		x = deg2rad * i;
		sx = (PRECISION) sin(x);
		Sx = (PRECISION) Sin(x);
		dx = sx - Sx;
		printf("%3.0d %15.8f %15.8f %15.8e\n", i, sx, Sx, dx);
	}
	return;
}
#endif /* TEST */
