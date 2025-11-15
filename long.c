#include <limits.h>
#include "compat/cdefs.h"

#include "long.h"

void
cvt_D(int code __unused, va_list_box *box,
      int put(int c, void *cl), void *cl,
      unsigned char flags[], int width, int precision)
{
    long val = va_arg(box->ap, long);
    unsigned long m;
    char buf[43];
    char *p = buf + sizeof buf;
    if (val == LONG_MIN)
	m = LONG_MAX + 1UL;
    else if (val < 0)
	m = -val;
    else
	m = val;
    do
	*--p = m % 10 + '0';
    while ((m /= 10) > 0);
    if (val < 0)
	*--p = '-';
    Fmt_putd(p, (buf + sizeof buf) - p, put, cl, flags, width, precision);
}
