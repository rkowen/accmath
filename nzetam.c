/*
 * Nzetam(N) computes the Rieman Zeta function - 1 for integer N >= 2 to
 *        machine accuracy.
 * 
 * by R.K.Owen,Ph.D.  10/06/93
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
#  define MAXZETA 8
#else
#  define MAXZETA 32
#endif

PRECISION Nzetam(INTEGER N) {
	static PRECISION ztable[MAXZETA];
	static char FIRST = (char) (0 == 0), zfirst[MAXZETA];
	const PRECISION zero = 0.0, one = 1.0;
	const PRECISION six = 6.0, ninety = 90.0, n945 = 945.0;
	PRECISION tpi, sum = 1.0, newsum = 0.0, inc = 2.0;
	int i;

	if (FIRST) {
		FIRST = !FIRST;
#ifdef TEST
		printf("initializing Nzetam\n");
#endif
		for (i = 0; i < MAXZETA; ++i) {
			ztable[i] = zero;
			zfirst[i] = (0 == 1); /* all false */
		}
	}
	if (N < 2) return zero;
/* return from table if available */
	if (N < (MAXZETA + 2) && zfirst[N - 2]) return ztable[N - 2];
/* compute Nzetam(N) as necessary */
	if (N == 2) {
#ifdef TEST
		printf("initializing Nzetam(2)\n");
#endif
		tpi = Pi();
		tpi *= tpi;
		zfirst[0] = !zfirst[0];
		ztable[0] = tpi/six - one;
		return ztable[0];
	}
	if (N == 3) {
#ifdef TEST
		printf("initializing Nzetam(3)\n");
#endif
		zfirst[1] = !zfirst[1];
		ztable[1] = Nzetam0(zero);
		return ztable[1];
	}
	if (N == 4) {
#ifdef TEST
		printf("initializing Nzetam(4)\n");
#endif
		tpi = Pi();
		tpi *= tpi;
		tpi *= tpi;
		zfirst[2] = !zfirst[2];
		ztable[2] = tpi/ninety - one;
		return ztable[2];
	}
	if (N == 5) {
#ifdef TEST
		printf("initializing Nzetam(5)\n");
#endif
		zfirst[N - 2] = !zfirst[N - 2];
		ztable[N - 2] = Nzetam1(zero,N);
		return ztable[N - 2];
	}
	if (N == 6) {
#ifdef TEST
		printf("initializing Nzetam(6)\n");
#endif
		tpi = Pi();
		tpi *= tpi;
		tpi *= tpi*tpi;
		zfirst[4] = !zfirst[4];
		ztable[4] = tpi/n945 - one;
		return ztable[4];
	}
	if (N == 7) {
#ifdef TEST
		printf("initializing Nzetam(7)\n");
#endif
		zfirst[N - 2] = !zfirst[N - 2];
		ztable[N - 2] = Nzetam1(zero,N);
		return ztable[N - 2];
	}
/* general saveable case */
	if (N < (MAXZETA + 2)) {
#ifdef TEST
		printf("initializing Nzetam(N<MAXZETA)\n");
#endif
		zfirst[N - 2] = !zfirst[N - 2];
		while (sum != newsum) {
			sum = newsum;
			newsum += Npow(inc,-N);
			inc++;
		}
		ztable[N - 2] = sum;
		return ztable[N - 2];
	} else {
/* general case */
#ifdef TEST
		printf("evaluating   Nzetam(N>MAXZETA)\n");
#endif
		while (sum != newsum) {
			sum = newsum;
			newsum += Npow(inc,-N);
			inc++;
		}
		return sum;
	}
}

#ifdef TEST

void main(void) {
	PRECISION Zx;
	PRECISION Tx[] = {
/*  0  */    0.00000000,
/*  1  */    0.00000000,
/*  2  */    0.64493407,
/*  3  */    0.20205690,
/*  4  */    0.08232323,
/*  5  */    0.03692776,
/*  6  */    0.01734306,
/*  7  */    0.00834928,
/*  8  */    0.00407736,
/*  9  */    0.00200839,
/* 10  */    0.00099458 };
	int i;

	printf("should have a  initialization message here:\n");
	for (i = 1; i < sizeof(Tx)/sizeof(Tx[0]); i++) {
		Zx = (PRECISION) Nzetam(i);
		printf("%3.d %15.8f %15.8f\n", i, Zx, Tx[i]);
	}
	printf("should have no initialization message here:\n");
	for (i = 1; i < sizeof(Tx)/sizeof(Tx[0]); i++) {
		Zx = (PRECISION) Nzetam(i);
		printf("%3.d %15.8f %15.8f\n", i, Zx, Tx[i]);
	}
	return;
}
#endif /* TEST */
