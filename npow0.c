/*
 * Npow0(x,N) computes the integer N power of x to the limits of
 *        machine accuracy for x real.
 *        Npow0( ) will save previously computed powers of x and reuse
 *        if possible (only if x remains unchanged).  If using ever
 *        changing values of x, then it will be better to use Npow( )
 *        instead.
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
#  define MAXNPOW 32
#endif

PRECISION Npow0(PRECISION x, INTEGER N) {
	static PRECISION oldx = 0.0, xtable[MAXNPOW];
	static char xfirst[MAXNPOW];
	const PRECISION zero = 0.0, one = 1.0;
	int i;

	if (N == 0) return one;		/* 0^0 == 1 */
	if (x == zero) return zero;

	if (x != oldx) {
#ifdef TEST
		printf("initializing Npow0\n");
#endif
		oldx = x;
		for (i = 0; i < MAXNPOW; ++i) {
			xfirst[i] = (0 == 0);	/* true */
		}
	}
	if (N < 0) {
		N = -N;
		if (N < (MAXNPOW + 1)) {
			if (xfirst[N - 1]) {
#ifdef TEST
				printf("initializing Npow0(-N = %d)\n",N);
#endif
				xfirst[N - 1] = ! xfirst[N - 1];
				xtable[N - 1] = Npow(x,N);
			}
			return one/xtable[N - 1];
		} else {
#ifdef TEST
			printf("evaluating   Npow0(-N = %d)\n",N);
#endif
			return Npow(x,-N);
		}
	} else {
		if (N < (MAXNPOW + 1)) {
			if (xfirst[N - 1]) {
#ifdef TEST
				printf("initializing Npow0( N = %d)\n",N);
#endif
				xfirst[N - 1] = ! xfirst[N - 1];
				xtable[N - 1] = Npow(x,N);
			}
			return xtable[N - 1];
		} else {
#ifdef TEST
			printf("evaluating   Npow0( N = %d)\n",N);
#endif
			return Npow(x,N);
		}
	}
}

#ifdef TEST

#include <stdio.h>
#include <math.h>

void main(void) {
	PRECISION x, px, Px, dx;
	const PRECISION two = 2.0, three = 3.0;
	int i;

	printf("should have a  initialization message here:\n");
	for (i = -10; i <= 10; i++) {
		x = (PRECISION) i;
		px = (PRECISION) pow(two,x);
		Px = (PRECISION) Npow0(two,i);
		dx = px - Px;
		printf("%3.d %15.8f %15.8f %15.8e\n", i, px, Px, dx);
	}
	printf("should have no initialization message here:\n");
	for (i = -10; i <= 10; i++) {
		x = (PRECISION) i;
		px = (PRECISION) pow(two,x);
		Px = (PRECISION) Npow0(two,i);
		dx = px - Px;
		printf("%3.d %15.8f %15.8f %15.8e\n", i, px, Px, dx);
	}

	printf("should have a  initialization message here:\n");
	for (i = -10; i <= 10; i++) {
		x = (PRECISION) i;
		px = (PRECISION) pow(three,x);
		Px = (PRECISION) Npow0(three,i);
		dx = px - Px;
		printf("%3.d %15.8f %15.8f %15.8e\n", i, px, Px, dx);
	}
	printf("should have no initialization message here:\n");
	for (i = -10; i <= 10; i++) {
		x = (PRECISION) i;
		px = (PRECISION) pow(three,x);
		Px = (PRECISION) Npow0(three,i);
		dx = px - Px;
		printf("%3.d %15.8f %15.8f %15.8e\n", i, px, Px, dx);
	}
	return;
}
#endif /* TEST */
