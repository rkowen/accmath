/*
 * Npow1(x,N) computes the integer N power of integer x to the limits of
 *        machine accuracy for INTEGER x.
 *        Npow1( ) will save previously computed powers of x for constant N
 *        and reuse if possible (only if N remains unchanged).
 *
 *        Npow1( ) is a special function to Nzeta( ).
 *
 * calls: Npow
 *
 * by R.K.Owen,Ph.D.  10/04/93
 */

#ifdef TEST
#  define _PRECISION_
typedef double PRECISION;
#  define _INTEGER_
typedef int INTEGER;
#endif

#include "accmath.h"

#ifdef TEST
#  include <stdio.h>
#  define MAXNPOW 9
#else
#  define MAXNPOW 64
#endif

PRECISION Npow1(INTEGER x, INTEGER N) {
	static INTEGER oldN = 0;
	static PRECISION xtable[MAXNPOW];
	static char xfirst[MAXNPOW];
	const PRECISION zero = 0.0, one = 1.0;
	PRECISION tx = (PRECISION) x;
	int i;

	if (N == 0) return one;		/* 0^0 == 1 */
	if (x == 0) return zero;

	if (Abs(N) != oldN) {
#ifdef TEST
		printf("initializing Npow1\n");
#endif
		oldN = Abs(N);
		for (i = 0; i < MAXNPOW; ++i) {
			xfirst[i] = (0 == 0);	/* true */
		}
	}
	if (N < 0) {
		N = -N;
		if (x < (MAXNPOW + 1)) {
			if (xfirst[x - 1]) {
#ifdef TEST
				printf("initializing Npow1(x = %d)\n",x);
#endif
				xfirst[x - 1] = !(xfirst[x - 1]);
				xtable[x - 1] = Npow(tx,-N);
			}
			return xtable[x - 1];
		} else {
#ifdef TEST
			printf("evaluating   Npow1(x = %d)\n",x);
#endif
			return Npow(tx,-N);
		}
	} else {
		if (x < (MAXNPOW + 1)) {
			if (xfirst[x - 1]) {
#ifdef TEST
				printf("initializing Npow1(x = %d)\n",x);
#endif
				xfirst[x - 1] = !(xfirst[x - 1]);
				xtable[x - 1] = Npow(tx,-N);
			}
			return (one/xtable[x - 1]);
		} else {
#ifdef TEST
			printf("evaluating   Npow1(x = %d)\n",x);
#endif
			return Npow(tx,N);
		}
	}
}

#ifdef TEST

#include <stdio.h>
#include <math.h>

void main(void) {
	PRECISION px, Px, dx;
	int i;

	printf("should have a  initialization message here:\n");
	for (i = 1; i <= 10; i++) {
		px = (PRECISION) pow((double) i, -2);
		Px = (PRECISION) Npow1((INTEGER) i, (INTEGER) -2);
		dx = px - Px;
		printf("%3.d %15.8f %15.8f %15.8e\n", i, px, Px, dx);
	}
	printf("should have no initialization message here:\n");
	for (i = 1; i <= 10; i++) {
		px = (PRECISION) pow((double) i, -2);
		Px = (PRECISION) Npow1((INTEGER) i, (INTEGER) -2);
		dx = px - Px;
		printf("%3.d %15.8f %15.8f %15.8e\n", i, px, Px, dx);
	}
	printf("should have no initialization message here:\n");
	for (i = 1; i <= 10; i++) {
		px = (PRECISION) pow((double) i, 2);
		Px = (PRECISION) Npow1((INTEGER) i, (INTEGER) 2);
		dx = px - Px;
		printf("%3.d %15.8f %15.8f %15.8e\n", i, px, Px, dx);
	}

	printf("should have a  initialization message here:\n");
	for (i = 1; i <= 10; i++) {
		px = (PRECISION) pow((double) i, -3);
		Px = (PRECISION) Npow1((INTEGER) i, (INTEGER) -3);
		dx = px - Px;
		printf("%3.d %15.8f %15.8f %15.8e\n", i, px, Px, dx);
	}
	printf("should have no initialization message here:\n");
	for (i = 1; i <= 10; i++) {
		px = (PRECISION) pow((double) i, -3);
		Px = (PRECISION) Npow1((INTEGER) i, (INTEGER) -3);
		dx = px - Px;
		printf("%3.d %15.8f %15.8f %15.8e\n", i, px, Px, dx);
	}
	printf("should have no initialization message here:\n");
	for (i = 1; i <= 10; i++) {
		px = (PRECISION) pow((double) i, 3);
		Px = (PRECISION) Npow1((INTEGER) i, (INTEGER) 3);
		dx = px - Px;
		printf("%3.d %15.8f %15.8f %15.8e\n", i, px, Px, dx);
	}

	return;
}
#endif /* TEST */
