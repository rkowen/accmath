/* Header file for the accurate math library */
/*
 * by R.K.Owen,Ph.D.  08/92
 */

#ifndef _ACCMATH

#  define _ACCMATH

/* to change the precision of the library just change the following */
#  ifndef _PRECISION_
#    define _PRECISION_
typedef double PRECISION;
#  endif

#  ifndef _INTEGER_
#    define _INTEGER_
typedef int INTEGER;
#  endif

/* ANSI-C prototypes */
/* special constants */
PRECISION        E(void);
PRECISION      Eps(void);
PRECISION    Euler(void);
PRECISION      Phi(void);
PRECISION       Pi(void);

PRECISION      Sin(PRECISION x);
PRECISION     Sin0(PRECISION x);
PRECISION      Cos(PRECISION x);
PRECISION     Cos0(PRECISION x);
PRECISION     Asin(PRECISION x);
PRECISION    Asin0(PRECISION x);
PRECISION     Acos(PRECISION x);
PRECISION     Atan(PRECISION x);
PRECISION    Atan0(PRECISION x);
PRECISION    Atan1(PRECISION x);
PRECISION      Exp(PRECISION x);
PRECISION     Exp0(PRECISION x);
PRECISION      Log(PRECISION x);
PRECISION     Log0(PRECISION x);

PRECISION     Sqrt(PRECISION x);
PRECISION    Cubrt(PRECISION x);
PRECISION     Npow(PRECISION x, INTEGER N);
PRECISION    Npow0(PRECISION x, INTEGER N);
PRECISION    Npow1(INTEGER   x, INTEGER N);

PRECISION    Nzeta(INTEGER   N);
PRECISION   Nzetam(INTEGER   N);
PRECISION  Nzetam0(PRECISION x);
PRECISION  Nzetam1(PRECISION x, INTEGER N);

PRECISION      Erf(PRECISION x);
PRECISION     Erf0(PRECISION x);
PRECISION     Erfc(PRECISION x);
PRECISION    Erfc0(PRECISION x);

/* MIN_MAX
 * set of macros for returning the min,max of 2 or 3 numbers
 */
/* 2 arguments */
#  define Min2(a,b) (((a)<(b))?(a):(b))
#  define Max2(a,b) (((a)>(b))?(a):(b))
/* 3 arguments */
#  define Min3(a,b,c) Min2(Min2(a,b),Min2(b,c))
#  define Mid3(a,b,c) Min3(Max2(a,b),Max2(b,c),Max2(a,c))
#  define Max3(a,b,c) Max2(Max2(a,b),Max2(b,c))

/* Macro for returning the absolute value */
#  define Abs(a) (((a)<0)?-(a):(a))

#endif /* _ACCMATH */
