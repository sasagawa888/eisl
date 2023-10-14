#ifndef COMPAT_CURSES_STUBS_H
#define COMPAT_CURSES_STUBS_H

#define _XOPEN_SOURCE 700
#define _XOPEN_SOURCE_EXTENDED 
#ifdef WITHOUT_CURSES
#else
# ifdef __linux__
#  include <ncurses.h>
# else
#  include <curses.h>
# endif
#endif
#undef _XOPEN_SOURCE
#undef _XOPEN_SOURCE_EXTENDED

#endif
