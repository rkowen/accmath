/*
 * Cubrt(x) computes the cubic root function to the limits of
 *        machine accuracy for x real.
 * 
 *
 * by R.K.Owen,Ph.D.  08/15/92
 */

#ifdef TEST
#  define _PRECISION_
typedef double PRECISION;
#endif

#include "accmath.h"

#ifdef TEST
#  include <stdio.h>
#endif

/* Use the Newton method for quadratic convergence to the zero
 * of f(x) = x^3 - N
 */
PRECISION Cubrt(PRECISION x) {
	PRECISION xn = x, xn1 = 0.0, t;
	const PRECISION zero = 0.0, one = 1.0, two = 2.0, three = 3.0;
	static PRECISION eps, third = 0.0, twothird = 0.0;
	static char FIRST = (char) (0 == 0);

	if (FIRST) {
		FIRST = !FIRST;
#ifdef TEST
		printf("Initializing Cubrt\n");
#endif
		eps = Eps();
		third = one / three;
		twothird = two * third;
	}

	if (x <= zero) return zero;
	while ((t=xn - xn1,Abs(t)) > eps) {
		xn1 = xn;
		xn = twothird*xn + third*((x/xn)/xn);
	}
	return xn;
}

#ifdef TEST

void main(void) {
	PRECISION x, Dx, Cx, dx, scale;
	int i;
	scale = 1./2.;

	for (i = -3; i <= 8; i++) {
		x = scale * i + 1.0;
		Cx = (PRECISION) Cubrt(x);
		Dx = Cx*Cx*Cx;
		dx = x - Dx;
		printf("%10.4f %15.8f %15.8f %15.8e\n", x, Cx, Dx, dx);
	}
	return;
}
#endif /* TEST */
