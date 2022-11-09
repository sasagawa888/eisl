#ifndef COMPAT_CURSES_STUBS_H
#define COMPAT_CURSES_STUBS_H

#ifdef WITHOUT_CURSES
#else
#ifdef __linux__
#include <ncurses.h>
#else
#include <curses.h>
#endif
#endif

#endif
