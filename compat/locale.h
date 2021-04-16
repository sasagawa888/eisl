/* Portable wrapper around locale header file */

#ifndef LOCALE_H
#define LOCALE_H

#include <locale.h>
#if __APPLE__
#include <xlocale.h>
#endif

#endif
