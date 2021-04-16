/* Portable wrapper around locale header file */

#ifndef LOCALE_H
#define LOCALE_H

#if __APPLE__
#include <xlocale.h>
#else
#include <locale.h>
#endif

#endif
