#include "fast.h"
static int f_FOO(int arglist, int th);static int FOO(int N, int th);
static int f_PFIB(int arglist, int th);static int PFIB(int N, int th);
static int f_FIB1(int arglist, int th);static int FIB1(int N, int th);
static int f_FIB(int arglist, int th);static int FIB(int N, int th);
#include "bug1.c"
#include "bug5.c"
#include "bug6.c"
#include "bug7.c"
#include "bug2.c"
#include "bug3.c"
#include "bug4.c"
