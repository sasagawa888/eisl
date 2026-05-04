#include "fast.h"
static int f_TEST_BOUNDARY1(int arglist, int th);static int TEST_BOUNDARY1(int th);
static int f_TEST_BOUNDARY2(int arglist, int th);static int TEST_BOUNDARY2(int X, int th);
static int f_FOO(int arglist, int th);static int FOO(int th);
#include "bug1.c"
#include "bug5.c"
#include "bug6.c"
#include "bug7.c"
#include "bug2.c"
#include "bug3.c"
#include "bug4.c"
