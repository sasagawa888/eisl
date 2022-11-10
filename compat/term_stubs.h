#ifndef COMPAT_TERM_STUBS_H
#define COMPAT_TERM_STUBS_H

#ifdef WITHOUT_CURSES
#define COLOR_RED 0
#define COLOR_CYAN 0
#define COLOR_MAGENTA 0
#define COLOR_YELLOW 0
#define COLOR_BLUE 0
#define ERR 0
#define tputs(x, y, z)
#define putp(x)
#define setupterm(x, y, z) (ERR)
static const char *key_up = NULL;
static const char *key_down = NULL;
static const char *key_right = NULL;
static const char *key_left = NULL;
#else
#include <term.h>
#endif

#endif
