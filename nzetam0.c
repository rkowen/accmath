/*
 * Nzetam0(x) computes x + the Rieman Zeta function - 1 for integer N = 3
 *        to machine accuracy.
 *
 * by R.K.Owen,Ph.D.  10/03/93
 */

#ifdef TEST
#  define _PRECISION_
typedef double PRECISION;
#endif

#include "accmath.h"

#ifdef TEST
#  include <stdio.h>
#endif

/* use Euler's transformation to accelarate convergence
 *
 *                      1    [                   ( 1    1    1       )]
 * x + zeta(n) - 1 = --------[    1-n      1-n   ( -- - -- + -- - ...)]
 *                       1-n [(1-2   )x + 2    - (  n    n    n      )]
 *                   (1-2   )[                   ( 2    3    4       )]
 *
 */
PRECISION Nzetam0(PRECISION x) {
	PRECISION sum = 0.0, newsum = 0.25, coef, scoef = 1.0,
		inc, jterm, bincoef;
	const PRECISION zero = 0.0, half = 0.5, one = 1.0, none = -1.0,
		two = 2.0;
	register PRECISION t;
	int s,j;

	coef = one - newsum;
	newsum += (coef * x);
	coef = one/coef;

	s = 0;
	while (sum != newsum) {
		sum = newsum;
		scoef *= half;
                inc = two;
		bincoef = none;
		jterm = zero;
		j = 0;
		do  {
			t = one/inc;
			t = t*t*t;
			jterm += (bincoef * t);
			bincoef *= (((PRECISION)(j - s))/((PRECISION)(j + 1)));
			inc++;
			j++;
		} while (j <= s);
		newsum += (scoef * jterm);
		s++;
	}
	return (coef * sum);
}

#ifdef TEST

#include <stdio.h>
#include <math.h>

void main(void) {
	PRECISION Zx;

	Zx = (PRECISION) Nzetam0(1.0);
	printf("%3.d %15.8f\n", 3, Zx);
	return;
}
#endif /* TEST */
