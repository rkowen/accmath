/*
 * Euler() computes Euler's constant lim_m->inf 1/m - log(m)
 *     to machine precision
 *
 * by R.K.Owen,Ph.D.  08/30/92
 *
 * Calls:
 */

#ifdef TEST
#  define _PRECISION_
typedef double PRECISION;
#endif

#include "accmath.h"

#ifdef TEST
#  include <stdio.h>
#endif

PRECISION Euler(void) {
	static char FIRST = (char) (0 == 0);
	static PRECISION euler = 1.0;
	const PRECISION zero = 0.0, one = 1.0, two = 2.0, four = 4.0;
	const PRECISION half = 0.5;
	PRECISION neweuler = 0.0, sum = 1.0;
	PRECISION numer, denom, coef, term, newsum;
	if (FIRST) {
		FIRST = !FIRST;
#ifdef TEST
		printf("Initializing Euler\n");
#endif
#if 0
/* direct evaluation is too slowly converging */
	long int i, ilo, ihi = 1, inc = 1;
		eps = Eps();
		while (Abs(euler - neweuler) > eps) {
			euler = neweuler;
			ilo = ihi + 1;
			inc++;
			ihi = inc*inc;
			for (i = ilo; i <= ihi; i++) sum += one/((PRECISION) i);
			neweuler = sum - Log((PRECISION) ihi);
#  ifdef TEST
			printf("%15.15ld %20.15f\r", ihi, neweuler);
#  endif
		}
#else
/* use Euler's transformation of series method */
		coef = four;
		while (euler != neweuler) {
			euler = neweuler;
			numer = one;
			denom = half*coef + one;
			term = one/coef;
			newsum = zero;
			while (sum != newsum) {
				sum = newsum;
				newsum += term;
				term *= half*numer/denom;
				numer += one;
				denom += one;
			}
			coef *= two;
			neweuler += sum;
#  ifdef TEST0
			printf("%20.15f\r", neweuler);
#  endif
		}
#endif
#ifdef TEST0
		printf("\n");
#endif
	}
	return euler;
}

#ifdef TEST

#define EULER 0.577215664901532860606512

void main(void) {
	PRECISION Ex, ex = EULER, dx;

	printf("should have a  initialization message here:\n");
	Ex = (PRECISION) Euler();
	dx = ex - Ex;
	printf("%15.8f %15.8f %15.8e\n", ex, Ex, dx);
	printf("should have no initialization message here:\n");
	Ex = (PRECISION) Euler();
	printf("%15.8f %15.8f %15.8e\n", ex, Ex, dx);
	return;
}
#endif /* TEST */
