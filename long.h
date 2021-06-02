#ifndef LONG_H
#define LONG_H

#include "fmt.h"

void            cvt_D(int code, va_list_box * box,
                      int put(int c, void *cl), void *cl,
                      unsigned char flags[], int width, int precision);

#endif
