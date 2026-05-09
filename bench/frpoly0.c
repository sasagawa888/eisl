#include "fast.h"
static int f_PCOEFADD(int arglist, int th);static int PCOEFADD(int E,int C,int X, int th);
static int f_PCPLUS(int arglist, int th);static int PCPLUS(int C,int P, int th);
static int f_PCPLUS1(int arglist, int th);static int PCPLUS1(int C,int X, int th);
static int f_PCTIMES(int arglist, int th);static int PCTIMES(int C,int P, int th);
static int f_PCTIMES1(int arglist, int th);static int PCTIMES1(int C,int X, int th);
static int f_PPLUS(int arglist, int th);static int PPLUS(int X,int Y, int th);
static int f_PPLUS1(int arglist, int th);static int PPLUS1(int X,int Y, int th);
static int f_PSIMP(int arglist, int th);static int PSIMP(int VAR,int X, int th);
static int f_PTIMES(int arglist, int th);static int PTIMES(int X,int Y, int th);
static int f_PTIMES1(int arglist, int th);static int PTIMES1(int X,int Y, int th);
static int f_PTIMES2(int arglist, int th);static int PTIMES2(int Y, int th);
static int f_PTIMES3(int arglist, int th);static int PTIMES3(int Y, int th);
static int f_PEXPTSQ(int arglist, int th);static int PEXPTSQ(int P,int X, int th);
