/*
 * Nzetam1(x,N) computes x + the Rieman Zeta function - 1 for integer N
 *        to machine accuracy.
 *
 * by R.K.Owen,Ph.D.  10/04/93
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
PRECISION Nzetam1(PRECISION x, INTEGER N) {
	PRECISION sum = 0.0, newsum = 0.5, coef, scoef = 1.0,
		jterm, bincoef;
	INTEGER inc;
	const PRECISION zero = 0.0, half = 0.5, one = 1.0, none = -1.0;
	int s,j;

	newsum = Npow(newsum,N - 1);
	coef = one - newsum;
	newsum += (coef * x);
	coef = one/coef;

	s = 0;
	while (sum != newsum) {
		sum = newsum;
		scoef *= half;
                inc = 2;
		bincoef = none;
		jterm = zero;
		j = 0;
		do  {
			jterm += (bincoef * Npow1(inc,-N));
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
	PRECISION Tx[] = {
/*  0  */    0.00000000,
/*  1  */    0.00000000,
/*  2  */    1.64493407,
/*  3  */    1.20205690,
/*  4  */    1.08232323,
/*  5  */    1.03692776,
/*  6  */    1.01734306,
/*  7  */    1.00834928,
/*  8  */    1.00407736,
/*  9  */    1.00200839,
/* 10  */    1.00099458 };
	int i;

	for (i = 2; i < sizeof(Tx)/sizeof(Tx[0]); i++) {
		Zx = (PRECISION) Nzetam1(1.0,i);
		printf("%3.d %15.8f %15.8f\n", i, Zx, Tx[i]);
	}
	return;
}
#endif /* TEST */
