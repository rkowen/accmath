#
# ACCMATH - dependencies
#

# extensions
O	= o
X	= x
RM	= rm
AR	= ar
ARFLAGS	= r
CC	= cc
CFLAGS	= -g
# options
LIB	= -lm
DBG	= -g
ACCMATH	= libaccmath.a
#
LIBS	= -L. -laccmath -lm

SRCS	= \
		e.c euler.c eps.c pi.c phi.c \
		sin.c sin0.c cos.c cos0.c \
		asin.c asin0.c acos.c \
		atan.c atan0.c atan1.c \
		exp.c exp0.c log.c log0.c \
		sqrt.c cubrt.c npow.c npow0.c npow1.c \
		nzeta.c nzetam.c nzetam0.c nzetam1.c \
		erf.c erfc.c erf0.c erfc0.c

# requires a GNU "make" for the following:
OBJS	= $(SRCS:.c=.$O)
EXES	= $(SRCS:.c=.$X)
LIBOBJS	= $(SRCS:%.c=$(ACCMATH)(%.o))

.SUFFIXES:
.SUFFIXES: .o .c .x .a

.c.a:
	$(CC) -c $(CFLAGS) $<
	$(AR) $(ARFLAGS) $@ $*.o
	-$(RM) -f $*.o

.o.a:
	$(AR) $(ARFLAGS) $@ $*.o
	-$(RM) -f $*.o

.c.x:
	$(CC) $(CFLAGS) -DTEST -o $*.$X $< $(LIBS)

all : $(ACCMATH)

$(ACCMATH) : $(LIBOBJS)
	@echo lib is now up-to-date

test : $(EXES)
	-for f in $(EXES) ; do echo ===$$f===; ./$$f ; done 2>&1 | more

### constants ###
# Napier's constant "e"
E=e.$O
# Euler's constant "lambda"
EULER=euler.$O
# Machine epsilon
EPS=eps.$O
# trig constant "pi"
PI=pi.$O atan0.$O
# golden ratio "phi"
PHI=phi.$O sqrt.$O

### Trigonmetry functions
SIN=sin.$O sin0.$O cos0.$O $(PI)
COS=cos.$O sin0.$O cos0.$O $(PI)
ASIN=asin.$O asin0.$O $(ATAN) $(SQRT)
ACOS=acos.$O $(ASIN)
ATAN=atan.$O atan0.$O atan1.$O pi.$O
EXP=exp.$O exp0.$O npow.$O $(E)
LOG=log.$O log0.$O $(E)

# powers & roots
SQRT=sqrt.$O
CUBRT=cubrt.$O $(EPS)
NPOW=npow.$O
NZETA=nzeta.$O nzetam0.$O nzetam1.$O $(NPOW) npow1.$O $(PI)
NZETAM=nzetam.$O nzetam0.$O nzetam1.$O $(NPOW) npow1.$O $(PI)

# special functions
ERF=erf.$O erf0.$O erfc0.$O $(EXP) $(SQRT) $(PI)
ERFC=erfc.$O erf0.$O erfc0.$O $(EXP) $(SQRT) $(PI)

### test section ###
te.$X : e.$O
	$(CC) $(DBG) -DTEST -o te.$X $(E) $(LIB)

teuler.$X : $(EULER)
	$(CC) $(DBG) -DTEST -o teuler.$X $(EULER) $(LIB)

teps.$X : $(EPS)
	$(CC) $(DBG) -DTEST -o teps.$X eps.c $(LIB)

tpi.$X : $(PI)
	$(CC) $(DBG) -DTEST -o tpi.$X pi.c atan0.$O $(LIB)

tphi.$X : $(PHI)
	$(CC) $(DBG) -DTEST -o tphi.$X phi.c $(SQRT) $(LIB)

tsin.$X : $(SIN)
	$(CC) $(DBG) -DTEST -o tsin.$X sin.c sin0.$O cos0.$O $(PI) $(LIB)

tcos.$X : $(COS)
	$(CC) $(DBG) -DTEST -o tcos.$X cos.c sin0.$O cos0.$O $(PI) $(LIB)

tsin0.$X : sin0.c
	$(CC) $(DBG) -DTEST -o tsin0.$X sin0.c $(LIB)

tcos0.$X : cos0.c
	$(CC) $(DBG) -DTEST -o tcos0.$X cos0.c $(LIB)

tasin.$X : $(ASIN)
	$(CC) $(DBG) -DTEST -o tasin.$X asin.c asin0.$O $(ATAN) $(SQRT) $(LIB)

tasin0.$X : asin0.c
	$(CC) $(DBG) -DTEST -o tasin0.$X asin0.c $(LIB)

tacos.$X : $(ACOS)
	$(CC) $(DBG) -DTEST -o tacos.$X acos.c $(ASIN) $(LIB)

tatan.$X : $(ATAN)
	$(CC) $(DBG) -DTEST -o tatan.$X atan.c atan1.$O $(PI) $(LIB)

tatan0.$X : atan0.$O
	$(CC) $(DBG) -DTEST -o tatan0.$X atan0.c $(LIB)

tatan1.$X : atan1.$O
	$(CC) $(DBG) -DTEST -o tatan1.$X atan1.c $(LIB)

texp.$X : $(EXP)
	$(CC) $(DBG) -DTEST -o texp.$X exp.c exp0.$O $(NPOW) $(E) $(LIB)

texp0.$X : exp0.$O
	$(CC) $(DBG) -DTEST -o texp0.$X exp0.c $(LIB)

tlog.$X : $(LOG)
	$(CC) $(DBG) -DTEST -o tlog.$X log.c log0.$O $(E) $(LIB)

tlog0.$X : log0.$O
	$(CC) $(DBG) -DTEST -o tlog0.$X log0.c $(LIB)

tsqrt.$X : $(SQRT)
	$(CC) $(DBG) -DTEST -o tsqrt.$X sqrt.c $(LIB)

tcubrt.$X : $(CUBRT)
	$(CC) $(DBG) -DTEST -o tcubrt.$X cubrt.c $(EPS) $(LIB)

tnpow.$X : $(NPOW)
	$(CC) $(DBG) -DTEST -o tnpow.$X npow.c $(LIB)

tnpow0.$X : $(NPOW)
	$(CC) $(DBG) -DTEST -o tnpow0.$X npow0.c $(NPOW) $(LIB)

tnpow1.$X : $(NPOW)
	$(CC) $(DBG) -DTEST -o tnpow1.$X npow1.c $(NPOW) $(LIB)

tnzeta.$X : $(NZETA)
	$(CC) $(DBG) -DTEST -o tnzeta.$X nzeta.c nzetam0.$O nzetam1.$O \
		$(NPOW) npow1.$O $(PI) $(LIB)

tnzetam.$X : $(NZETAM)
	$(CC) $(DBG) -DTEST -o tnzetam.$X nzetam.c nzetam0.$O nzetam1.$O \
		$(NPOW) npow1.$O $(PI) $(LIB)

tnzetam0.$X : nzetam0.$O
	$(CC) $(DBG) -DTEST -o tnzetam0.$X nzetam0.c $(LIB)

tnzetam1.$X : nzetam1.$O $(NPOW)
	$(CC) $(DBG) -DTEST -o tnzetam1.$X nzetam1.c $(NPOW) npow1.$O $(LIB)

terf.$X : $(ERF)
	$(CC) $(DBG) -DTEST -o terf.$X erf.c erf0.$O erfc0.$O \
		$(EXP) $(SQRT) $(PI) $(LIB)

terfc.$X : $(ERFC)
	$(CC) $(DBG) -DTEST -o terfc.$X erfc.c erf0.$O erfc0.$O \
		$(EXP) $(SQRT) $(PI) $(LIB)

terf0.$X : erf0.$O $(EXP) $(SQRT) $(PI)
	$(CC) $(DBG) -DTEST -o terf0.$X erf0.c $(EXP) $(SQRT) $(PI) $(LIB)

terfc0.$X : erfc0.$O $(SQRT) $(PI)
	$(CC) $(DBG) -DTEST -o terfc0.$X erfc0.c $(SQRT) $(PI) $(LIB)

### clean up ###
clean :
	-$(RM) *.$O

tclean :
	-$(RM) t*.$X

clobber : clean tclean
	-$(RM) *.$X

wipe : clobber
	-$(RM) $(ACCMATH)

